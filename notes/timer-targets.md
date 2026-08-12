# Timer Targets — Quick Reference

> Open this before you start a problem. Set one alarm. Start a stopwatch.

---

## Budgets

| Difficulty | New problem | Re-solve | Interview target |
|---|---|---|---|
| **Easy** | 15 min | 8 min | 10–12 min |
| **Medium** | 25 min | 15 min | 20–25 min |
| **Hard** | 40 min | 25 min | 35–45 min |

Timer covers **solve only** — not the writeup, not the README.

**Stopwatch to measure, timer to decide.** Count up while you work so you collect real data; one alarm at the decision point. No countdown anxiety.

---

## At the buzzer — branch on *why* you're stuck

The buzzer is **not** pass/fail. It's a trigger to change strategy.

```
Do I have a working approach?
│
├─ YES, just implementing/debugging
│     → +15 min. You're on the productive path; the clock misjudged.
│
├─ NO viable approach
│     → STOP. Read ONLY the hint / editorial's first paragraph.
│       NOT the solution.
│       → Fresh 15-min timer. Solve it yourself.
│
└─ Still stuck after the hint
      → Read the full editorial. CLOSE IT. Implement from memory.
      → Re-solve from scratch in 2–3 days.  ← this re-solve is what teaches
```

---

## Hard ceilings

| | Ceiling (hint time included) |
|---|---|
| Medium | **60 min** |
| Hard | **90 min** |

Past this, marginal learning collapses. You're grinding, not training. Stop and move on — the re-solve in 2–3 days recovers more than another hour today.

---

## Before you submit — 60 seconds, non-negotiable

**Trace the first input where your tricky branch fires.** Not the whole input. Not the happy path. The one case where the special-case logic actually runs.

This is part of "done," not an optional act of willpower. It's how the tracing habit gets built.

*(Related: writing one-state-change-per-line makes this cheap. Dense lines are what make tracing feel like punishment.)*

---

## Why these numbers

A typical 45-minute interview slot holds **two problems** — and the coding is maybe half of it. The rest is clarifying questions (~2 min), talking through the approach (~5 min), dry-running aloud (~3 min), and complexity discussion (~2 min).

So "medium in 25 minutes" isn't 25 minutes of typing. It's ~12 minutes of actual coding wrapped in the conversation that gets you the point.

**Phase 1 note:** re-solves that blow past the re-solve column are your rust measurement — that's data, not failure. Expect them to drop fast.

---

## Time log

Track a few, mostly to watch re-solve times fall.

| Date | Problem | Diff | New/Re | Target | Actual | Outcome |
|---|---|---|---|---|---|---|
| | | | | | | |

Outcome codes: `S` solved unaided · `H` needed hint · `E` needed editorial · `T` hit ceiling

---

## Related

- [Prep roadmap](roadmap.md) — phases, cadence, coverage tracker
- [The optimization ladder](dsa-patterns/optimization-ladder.md) — the 5-minute squeeze pass after solving
