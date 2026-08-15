# Interview Explanation — The 7 Beats

> **Explanation has skeletons, exactly like code does.** You are not inventing an explanation under pressure — you are filling in a form you have used fifty times. Same principle as [loop skeletons](dsa-patterns/loop-skeletons.md): clean output is *recalled structure*, not in-the-moment brilliance.

Started 2026-08-15. Practise this on **every** solve — deliver the explanation before/alongside the code, not just the code.

---

## The 7 beats

| # | Beat | What it earns |
|---|---|---|
| 1 | **Restate the problem** in your own words | Confirms understanding; buys ~20 seconds of thinking time |
| 2 | **Brute force + its complexity**, and why it's too slow | Shows you know the baseline before optimising |
| 3 | **The key observation** — the single unlock | ⭐ This is what they are actually grading |
| 4 | **The approach**, high level, *before* writing code | Lets them course-correct you early, cheaply |
| 5 | **Trace one small example** | Proves it works *and* builds the verification habit |
| 6 | **Complexity** — time and space, justified | Non-negotiable |
| 7 | **Edge cases** you handled | Separates senior from junior |

---

## The golden rule: concrete before abstract

When a listener is confused, **do not add rigour — add a concrete instance.**

*Learned the hard way 2026-08-14:* mentor explained "why `maxFreq` never decreases" with algebra and a general argument. Incomprehensible. The same claim, re-explained as a 5-row trace of my own string `AABABABCAB`, landed immediately.

> A formal proof convinces someone who already believes the claim. A concrete trace convinces someone who doesn't.

Lead with the example. Generalise after.

---

## Phrases that buy time and score points

- *"Let me restate that to make sure I've got it…"* — beat 1, and 20 free seconds
- *"The brute force here is O(n²) — let me see if I can do better."* — beat 2, signals you know it's not the answer
- *"The key observation is…"* — flags beat 3 out loud so they can't miss it
- *"Let me trace `[small example]` before I code it."* — beat 5, and catches your own bugs
- *"Can I assume the input is non-empty?"* — clarifying questions are scored, not penalised
- **Silence instead of "um."** Feels long to you; reads as *thoughtful* to them. (English profile P6.)

---

## What to avoid

- Coding in silence, then explaining afterwards. **Narrate as you go.**
- Jumping straight to the optimal solution with no baseline — looks memorised, not reasoned.
- Hedging before you make a point (*"I don't know if this is right, but…"*). English profile P6 — cut it.
- Dense, clever code. An interviewer who can't follow you can't award the point, and can't help when you stall.

---

## Progression

1. **Now:** written explanation with every solve, hitting all 7 beats.
2. **Next:** narrate aloud while solving — think-out-loud, the accurate simulation.
3. **Later:** `/english` skill → `interview` mode, for spoken register under pressure.

---

## Self-check

- [ ] Can I list all 7 beats from memory?
- [ ] Did I state the key observation *explicitly*, out loud, as its own sentence?
- [ ] Did I trace an example before writing code — not after?
- [ ] Did I give complexity without being asked?
- [ ] Zero "um"/"like" fillers? Silence instead?
