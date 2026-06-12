# Notes — Index

Spaced-repetition flashcards and lessons collected from problems, projects, and mentor sessions. Organized by topic.

> **How to use:** These are flashcards, not docs. Read the question, answer OUT LOUD from memory, *then* expand the answer. Revisit weekly. Cards you ace go to monthly; cards you fumble stay weekly.

---

## C++ / Language

- [Signed vs. unsigned pitfalls](cpp/signed-unsigned-pitfalls.md) — `size_t` underflow, `int`-vs-`size_t` comparisons, and the `s.size() - 1` trap. *First hit: Valid Palindrome (2026-06-09).*

## System Design

- [Durable Pipelines & Orchestration](system-design/durable-pipelines-flashcards.md) — workflow engines, queues, idempotency, distributed locks. *Source: Automote teardown, 2026-06-08.*

---

## Conventions

- Filename: `<topic>-<kind>.md` (e.g. `signed-unsigned-pitfalls.md`, `durable-pipelines-flashcards.md`).
- Each file starts with: topic, source, date, and a "How to use" line.
- Q&A goes inside `<details><summary>` blocks so you can self-test before peeking.
- Link back to the problem or project that surfaced the lesson.
