# Notes — Index

Spaced-repetition flashcards and lessons collected from problems, projects, and mentor sessions. Organized by topic.

> **How to use:** These are flashcards, not docs. Read the question, answer OUT LOUD from memory, *then* expand the answer. Revisit weekly. Cards you ace go to monthly; cards you fumble stay weekly.

---

## Plan

- **[Weekly revision protocol](revision-protocol.md)** — 🔁 every Sunday, 45–60 min. **Retrieval, not re-reading.** *Notes you don't retrieve are notes you didn't write.*
- **[Interview explanation template](interview-explanation-template.md)** — 🎤 Axis 1, *what* you say: the 7 beats. Practise on every solve; concrete before abstract.
- **[Communication rubric](communication-rubric.md)** — 🗣️ Axis 2, *how* you say it: 6 dimensions /30. Terminology precision is the expensive one.
- **[Timer targets](timer-targets.md)** — ⏱️ target times by difficulty, what to do at the buzzer, hard ceilings. *Open this before starting a problem.*
- **[Prep roadmap](roadmap.md)** — coverage tracker, cadence, and the interview-vs-Codeforces goal split. *Start here when deciding what to solve next.*

## DSA Patterns

- **[Loop skeletons](dsa-patterns/loop-skeletons.md)** — 🔧 the 9 canonical loop shapes. **Type the skeleton BEFORE thinking about the problem.** Clean code is recalled, not derived. *First hit: Longest Repeating Character Replacement (2026-08-13).*
- [Two Pointers — the two variants](dsa-patterns/two-pointer-variants.md) — opposite-ends vs same-direction, why discarding a pointer is safe, the decision rule for picking a variant cold. *First hit: Two Sum II (2026-06-11).*
- [The optimization ladder](dsa-patterns/optimization-ladder.md) — what to do when asked "can you do better?": squeeze before switching, reason backward from the target, and the standard time/space transformations. *First hit: Trapping Rain Water post-mortem (2026-07-28).*

## C++ / Language

- [Signed vs. unsigned pitfalls](cpp/signed-unsigned-pitfalls.md) — `size_t` underflow, `int`-vs-`size_t` comparisons, and the `s.size() - 1` trap. *First hit: Valid Palindrome (2026-06-09).*
- [Declaration & comma-operator gotchas](cpp/declaration-comma-gotchas.md) — `fast++, continue` (statement vs expression), mixed-type declarations, macro vs type alias. *First hit: Trapping Rain Water (2026-07-27).*

## System Design

- [Durable Pipelines & Orchestration](system-design/durable-pipelines-flashcards.md) — workflow engines, queues, idempotency, distributed locks. *Source: Automote teardown, 2026-06-08.*

---

## Conventions

- Filename: `<topic>-<kind>.md` (e.g. `signed-unsigned-pitfalls.md`, `durable-pipelines-flashcards.md`).
- Each file starts with: topic, source, date, and a "How to use" line.
- Q&A goes inside `<details><summary>` blocks so you can self-test before peeking.
- Link back to the problem or project that surfaced the lesson.
