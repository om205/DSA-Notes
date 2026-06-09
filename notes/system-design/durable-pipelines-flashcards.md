# Durable Pipelines & Orchestration — Flashcards

- Topic: System Design — durable workflows, job queues, idempotency
- Source: Automote teardown (mentor session)
- Date: 2026-06-08
- Real example: `F:\Programming\Automote\_Bounces\exportapollo` (n8n → Node rewrite)

> **How to use:** Read the question, answer it OUT LOUD from memory, *then* expand the answer. Don't peek first — the retrieval is what builds the memory. Revisit weekly.

---

## Core concept

<details>
<summary><b>Q1.</b> Automote replaced an n8n pipeline with Node. What was the single root-cause mistake?</summary>

I rebuilt n8n's **executor** (the step-running logic) but threw away its **durable per-step state**. The enriched data flowed through stages in an in-memory variable; only a lossy `progress` field hit the DB. So any crash lost all mid-job state and re-ran the whole job from step 1 — re-paying for every API call.
</details>

<details>
<summary><b>Q2.</b> What does a workflow engine (n8n, Azure Durable Functions) give you "for free" that a naive script doesn't?</summary>

**Per-step durability + resumability.** Every step's output is persisted before the next runs, so on failure it retries *that step*, not the whole job. The workflow is resumable at any point. Rebuild the executor without this and you've rebuilt the hard part wrong.
</details>

<details>
<summary><b>Q3.</b> What are the 4 pieces a managed orchestrator is really made of (so you can build one in any plain app)?</summary>

1. **Durable state** — a record of "where is each job right now"
2. **A queue** — hands work to workers (not cron + fire-and-forget HTTP)
3. **Idempotent workers** — each does ONE step, safe to run twice
4. **A re-driver / reaper** — requeues work that died mid-flight
</details>

---

## The key insight

<details>
<summary><b>Q4.</b> Where should the "current position in the pipeline" live, and why NOT in a for-loop?</summary>

**The queue message IS the program counter.** A `for` loop holds the position in process memory — it dies with the process. Instead, each step persists its output and *enqueues a message for the next step*. The pipeline position now lives in the durable queue. Crash → message un-acked → broker redelivers → resume exactly there.
</details>

<details>
<summary><b>Q5.</b> How do you model durable job state in a DB (vs a single boolean/progress field)?</summary>

An explicit **state machine** per job: `status` (PENDING/RUNNING/DONE/FAILED/DEAD) + `stage` + `batchCursor` + `outputs` map with a `{done, blobRef}` per completed stage. Big data → **blob storage**; DB holds only the small pointer. Now "where do I resume?" is a *lookup*, not a guess.
</details>

---

## Safety properties

<details>
<summary><b>Q6.</b> Queues deliver "at-least-once." What does that force every worker to be, and how?</summary>

**Idempotent** — safe to run twice (a redelivery happens if a crash lands after the work but before the ack). Rule: *before doing expensive work, check if the output already exists; if so, skip and just advance.* Idempotency key = `jobId + stage + batchId`. This makes retries cost $0 for already-done steps.
</details>

<details>
<summary><b>Q7.</b> Why did an in-memory mutex work in the monolith but break once split into Docker containers?</summary>

Each container has its **own** memory, so an in-process lock is invisible to other containers — two workers grab the same job. **Correctness depended on being a single process; scaling out broke it.** Fix: a *distributed* lock — the queue (one worker per message) or an atomic DB claim.
</details>

<details>
<summary><b>Q8.</b> How do you atomically claim a job straight from MongoDB so two workers can't grab it?</summary>

`findOneAndUpdate({ status:'PENDING', lockExpiresAt:{ $lt: now } }, { $set:{ status:'RUNNING', lockedBy, lockExpiresAt: now+60s } })`. It's atomic, so only one worker wins. The `lockExpiresAt` **lease** lets a reaper reclaim jobs whose worker died.
</details>

---

## Production hardening

<details>
<summary><b>Q9.</b> What's the CORRECT job for a cron in this design (vs "re-poke the pipeline")?</summary>

A **reaper / re-driver**: periodically find work whose lease expired (worker died holding it) and requeue it. Anything that fails past a max `attempts` → **dead-letter queue** for a human (poison messages), instead of silently re-burning credits in a retry loop.
</details>

<details>
<summary><b>Q10.</b> Concrete tools to build this in a plain Docker / App Service Node app? And which one fixes rate-limit blowups?</summary>

- **BullMQ (Redis)** — Node default: retries w/ backoff, dead-letter, concurrency cap, and a **rate limiter** (`limiter: { max: 15, duration: 1000 }`) → fixes firing 100 concurrent calls at a 15 req/s API.
- **Azure Service Bus** — queues w/ lock/visibility timeout, lock renewal, built-in DLQ.
</details>

<details>
<summary><b>Q11.</b> One-line summary: what should Automote have been?</summary>

A **Mongo job table (state machine) + BullMQ/Service Bus queue + small single-purpose workers that each persist output and enqueue the next step idempotently + a reaper for orphans.** Same boxes, coordinated by a durable queue instead of in-memory variables + a polling cron.
</details>

<details>
<summary><b>Q12.</b> Interview punchline — how does this connect to Azure Durable Functions?</summary>

Durable Functions implements *exactly* these 4 pieces internally (Storage queues for messages, a Table for state/history, replay from history per step). So: "I hand-built a durable orchestrator on a side project, hit every wall it exists to solve — lost state, expensive retries, rate-limit blowups — and that's why I reached for Durable Functions on the production pipeline at work." Turns a failure into a senior-level story.
</details>

---

## 30-second recall (cover the cards, recite these)

1. Mistake = executor without durable state → restart from zero on crash.
2. Orchestrator = **state + queue + idempotent workers + reaper**.
3. **The queue message is the program counter.**
4. At-least-once ⇒ **idempotency** (`jobId+stage+batch`, skip if output exists).
5. In-memory mutex dies across containers ⇒ **atomic claim + lease**.
6. Cron's real job = **reaper**; repeated failures ⇒ **dead-letter queue**.
7. Tools: **BullMQ/Redis** or **Service Bus**; rate limiter fixes throttling.
8. This is what **Durable Functions** does under the hood.
