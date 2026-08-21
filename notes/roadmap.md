# Prep Roadmap — Coverage, Cadence, Goals

- Date written: 2026-07-28 (revised same day with Codeforces + local-archive data)
- Status: **NeetCode 150 — 14/150 solved** (Easy 4/28, Med 9/101, Hard 1/21). Following the NC150 topological order; Arrays & Hashing and Two Pointers in progress.
- CF `om382`: **1130 now, peak 1376 (pupil)** Sept 2023. 31 rated contests, last one **Jan 2024**.
- Purpose: close the one gap that causes both the CF plateau and the failed coding rounds.

---

## The honest diagnosis (evidence-based)

**Thinking is not the bottleneck.** Derived the domination lemma unprompted (Container With Most Water), wrote an original correct solution to a Hard (Trapping Rain Water), and spotted the O(1) reduction of that solution independently. Reaching pupil with almost no graph/tree practice (see below) means raw problem-solving is carrying well past what the toolkit should allow.

### The finding: CF solved-problems by tag (141 unique solved)

```
greedy 64 · math 60 · implementation 46 · constructive 44 · brute force 24 · sortings 20   → 234 hits
dp 15 · data structures 13 · binary search 10                                              →  38 hits
dfs and similar 3 · trees 2 · graphs 1                                                     →   6 hits  ← THE WALL
```

By problem rating: **69 of 141 solved are 800-rated** (49%); only 15 at 1400+.

**This is the textbook pupil profile and it explains both problems at once.** Rating climbed to 1376 on ad-hoc cleverness — the tags that carry problem A and sometimes B. The wall at ~1300 is where C/D start requiring DP, graphs, trees, and data structures, where contest-tested experience is *six tag-hits across 141 problems*.

- **Codeforces symptom:** stalls at ~1300.
- **Interview symptom:** passes the array/two-pointer question, loses on a routine tree or DP problem.

**One gap, two symptoms. NeetCode 150 closes exactly it — so one plan serves both goals.**

### ⚠️ REVISED with LeetCode data — the CF-only read was wrong

LeetCode `om382`: **326 solved** (Easy 102, Med 183, Hard 41), 561 total submissions, active 2022–2024 then near-dormant.

**POTD contamination, measured.** A 184-day run (2023-09-29 → 2024-03-30) at **1.38 submissions/day** is the coin-farming streak signature; genuine practice bursts run **3–6 submissions/day**. Cross-referencing active days against LeetCode's POTD history gives **204 POTD problems** on active days — the maximum possible contamination.

Even subtracting *all* of it (deliberately too harsh), the genuine floor is:

| Topic | LC says | POTD max | Floor |
|---|---|---|---|
| Dynamic Programming | 64 | 43 | **21** |
| Depth-First Search | 40 | 20 | **20** |
| Breadth-First Search | 27 | 11 | **16** |
| Backtracking | 15 | 3 | **12** |
| Tree / Binary Tree | 27 / 26 | 16 / 15 | **11 / 11** |
| Binary Search | 23 | 14 | **9** |
| Union-Find | 9 | 3 | **6** |
| Trie | 6 | 1 | **5** |
| Graph Theory | 12 | 7 | **5** |

**The floor is too harsh anyway:** there were 12 Heap POTDs in the window and the profile shows **0** Heap solved — proof that many POTDs were skipped. True numbers sit above the floor.

**Conclusion: trees, DP, graphs, backtracking, and tries are NOT first-time learning. They are recovery.** The earlier "learn from scratch" framing is retracted.

### Why Codeforces looked so different

CF tags (`dfs 3, trees 2, graphs 1`) vs LeetCode (`DFS 40, Tree 27, BFS 27`) — same person, both true. **CF was used for contests** (solve A/B on greedy/math/implementation, stop); **LeetCode was used for topic practice** (where the trees and DP happened).

So the CF plateau is not a knowledge gap — it is an **application-under-time-pressure gap**: recognizing that problem C is secretly a BFS, in 20 minutes, with a clock running. Different skill, more tractable.

### The genuine holes (survive every optimistic reading)

1. **Heap / Priority Queue — literally 0**, with 12 passive chances missed. The one true void; heavily interview-tested.
2. **Shortest Path — 3 / floor 1.** Dijkstra, Bellman-Ford effectively absent.
3. **Topological Sort — 3 / floor 2.**
4. **Monotonic Stack — 8 / floor 4.** Common in interviews.
5. **Trie — 6 / floor 5.** Genuine but shallow.
6. **Hard problems — 41 reported, 32 Hard POTDs in window → ~9 genuine.**

### So the real diagnosis is: RUST + CONSISTENCY, not coverage

326 LeetCode solves with real breadth, then **stopped in early 2024**: 3 active days in 2025, 13 in 2026. Last CF contest Jan 2024. The knowledge exists and is decaying from disuse — that is a far better position than "never learned it," and it means recall speed returns fast.

### Secondary constraints

1. **Pace.** 136 NC150 problems remain. At the current per-problem cost (full writeup, proofs, deep review ≈ 1hr+) the timeline doesn't close. See writeup tiering below.
2. **Speed / implementation.** Syntax errors under pressure, dead code shipped, defensive `abs()` instead of stated invariants. Reps failures, not thinking failures — and on CF this is what caps rating.
3. **Consistency.** Self-reported as intermittent; last CF contest Jan 2024. Compounds more than any technique here.

---

## Two goals, decoupled

| Goal | Cost from here | Job-critical? |
|---|---|---|
| **Clear FAANG-tier coding rounds** | ~150 problems across 15 buckets — **3–4 months** at 1–2/day | ✅ **Yes** |
| **CF Specialist → Expert (1400–1900)** | 6–12 months of weekly contests + upsolving | Helpful (speed, breadth) |
| **CF Candidate Master (1900+)** | Typically **1.5–3 years** sustained from pupil | ❌ No company requires it |

Above roughly **1600 CF the skills diverge**: contest rating past that comes from speed, ad-hoc creativity, and math/DS depth that interviews never test. Interviews test pattern recognition on *known* problems, clean implementation, and communication.

**Decision: interview track is primary. CF is the speed/breadth trainer up to Expert.** CM is legitimate as a personal goal — pursue it *after* job security, knowing it's 1–2 years for something no employer asks about.

---

## Two layers decay at different rates — train the right one

**Schema layer: INTACT.** Trapping Rain Water — knew the shape before justifying it, transferred the decomposition from Container deliberately. Container — derived the domination lemma cold. Years to build, survived the 2-year gap.

**Fluency layer: GONE.** `fast++, continue` and mixed-type declarations failing to compile. Dead `max_pos` loop shipped. Four defensive `abs()` on provably-signed differences. No reduction pass. The automatic layer only exists through recent frequent use.

> "Not even 10%" is accurate about **fluency** and wrong about **knowledge**. The expensive layer survived; the cheap layer rebuilds cheaply — relearning is far faster than first learning.

**The trap:** deep-analysis practice (proofs, long writeups, detailed reviews, flashcards) builds *schema* — the layer already owned. Rebuilding *fluency* needs **reps, not depth per rep**. At 1hr+/problem, fluency cannot recover.

---

## Phases

### Phase 1 — Fluency rebuild (~6 weeks)
- **3–4 problems/day, 25-minute timer, three-line writeup.**
- Deliberately **re-solve problems already done** — the savings effect makes them fast and rebuilds speed specifically.
- March NC150 buckets 1–8 briskly. Goal is not insight; it is making the hands work again.
- **Mentor role changes:** fast checker only — correct/not, one flag, next. No long reviews; they actively slow this phase down. *(Say "stop reviewing, just check" if it drifts.)*

### Phase 2 — Growth (~10 weeks)
- Depth returns. Genuine gaps first: **Heap**, **Advanced Graphs**.
- Harder problems, weekly contests, full review treatment where it earns its cost.

### Phase 3 — Interview simulation
- Timed, spoken aloud, mock interviews.

---

## What "far above my old level" means, measurably

Old peak was CF 1376 + 326 LC solves — and it did **not** clear coding rounds. The data shows why:

- **69 of 141** CF problems solved were **800-rated**; only 15 at 1400+.
- **41 LC Hards, but ~32 were POTD → ~9 genuinely solved Hards.**

A large base at the easy end, a very thin tip. Interviews test the tip.

**Targets, countable:**
- Mediums solved in **under 25 minutes**, no hints.
- Genuinely-solved **Hards in the dozens**, not single digits.
- No bucket that causes a freeze.

Not more easies.

---

## Cadence

- **2 problems/day** — one in a *new* bucket, one timed review.
- **Timer protocol — see below.** No 3-hour grinds; they train stubbornness, not skill.
- **The squeeze pass — every problem, 5 minutes, before looking anything up.** Target O(1) space and one complexity class faster. See [optimization ladder](dsa-patterns/optimization-ladder.md). Non-negotiable: this is the exact skill flagged as missing, and it's already proven doable.
- **1 CF contest/week** (Div 3 to start) **+ upsolve everything not solved in-contest.** The upsolving is where rating comes from, not the contest.
- **CF practice targeting (from the tag data):** stop farming 800s — 49% of solved problems are already 800-rated and they teach nothing new now. Practice **1200–1500 rated problems tagged `dp`, `graphs`, `trees`, `data structures`, `binary search`.** That is precisely the gap; it is also exactly what NC150 buckets 7–14 cover, so contest practice and interview prep reinforce each other.

### Timer protocol

> **Quick reference: [timer-targets.md](timer-targets.md)** — open that before each problem. Full rationale below.

**Stopwatch to measure, timer to decide.** Count up while working (no countdown anxiety) so you get data on real solve times; set one alarm at the decision point.

**The buzzer is not pass/fail — it is a trigger to change strategy.**

| | New problem | Re-solve (Phase 1) |
|---|---|---|
| Easy | 15 min | 8 min |
| Medium | 25 min | 15 min |
| Hard | 40 min | 25 min |

Timer covers **solve only**, not the writeup.

**At the buzzer, branch on why you're stuck:**

1. **Working approach, just implementing/debugging** → add 15 min. Productive path; the clock misjudged.
2. **No viable approach** → stop. Read **only the hint** / editorial's first paragraph — not the solution. Fresh 15-min timer, solve it yourself.
3. **Still stuck after the hint** → read the full editorial, close it, implement from memory. **Re-solve from scratch in 2–3 days** — that re-solve is what actually teaches.

**Hard ceiling: 60 min for a medium, 90 for a hard**, hint time included. Past that, marginal learning collapses.

**Built-in dry-run step:** the last 60 seconds before submitting, trace the first input where the tricky branch fires. Part of "done", not an optional act of willpower — this is how the tracing habit gets built (see recurring pattern #12/#13).

### Theory triage — how much to study before practicing

**The test: can I derive this in 25 minutes under pressure?** Yes → practice first, theory adds nothing. No → theory first, because you will never invent Dijkstra at a whiteboard.

| Topic | Verdict | Budget | "Floor" from LC data |
|---|---|---|---|
| RPN / postfix evaluation | **Derivable — no tutorial** | 0 | — |
| Infix→postfix (shunting yard) | Only if it appears | 1 hr | — |
| Sorting algorithms | **Vocabulary only** — never implemented in interviews | 2 hrs | — |
| Binary search variants | Derivable but error-prone → memorize the template | 30 min | 9 |
| **Heap / priority queue** | 🔴 **Theory first — the one true void** | 90 min | **0** |
| Trees / BFS / DFS | Recovery, not learning | 45 min | 11–20 |
| **Graph algorithms** | 🔴 **Theory first** — Dijkstra, topo sort, union-find | 2–3 hrs | 5 |
| **DP patterns** | 🔴 **Theory first** — the classic recurrences | 3–4 hrs | 21 |
| AVL / red-black / B-trees | **Skip.** Conceptual only | 30 min | — |
| Segment tree / BIT | **Defer to the CF track** | later | — |

**Notes:**
- **Sorting: know the table, never the code.** Complexity, stability, in-place or not, when to pick which. Two mechanical exceptions worth knowing: **merge** (powers merge-k-lists, counting inversions) and **quickselect** (kth largest).
- **Balanced trees are a university topic, not an interview topic.** Know *what* a red-black tree is (self-balancing BST, O(log n) guaranteed, backs `std::map`) and *why* B-trees exist (disks read in blocks → database indexes). Implementing them is months of effort for zero interview return.
- **Segment trees are CF-relevant, not interview-relevant.** Two goals want different theory; the interview track is primary.

### The rule: thin, just-in-time theory

Both extremes fail. Theory-first-and-deep → three weeks on DP, understand everything, still can't solve a DP problem (passive learning doesn't transfer). Practice-only → four hours re-deriving what a twenty-minute video teaches.

> **30–60 minutes of theory per bucket, then straight into problems. Return to theory only when stuck.**

Theory's job is **vocabulary and the canonical shape**, not mastery. Mastery comes from the problems. Reading more theory before struggling with a problem is wasted — there are no hooks to hang it on yet.

**⚠️ Caution:** "prepare theory before practicing" held tightly becomes preparation-as-procrastination — the same shape as the logged habit of retreating into comfortable depth instead of uncomfortable reps. Reading about DP *feels* productive; failing at a DP problem *is* productive. **Hard cap: one hour of theory, then problems, however unready it feels.**

### Writeup tiering (the depth/breadth fix)

The full ritual (proofs, flashcards, mentor review) is valuable but costs ~1hr+/problem. Tier it:

- **New pattern, or something genuinely surprised me** → full ritual. Roughly 1 in 4.
- **Routine rep** → three lines: approach, complexity, one gotcha. Move on.

---

## Bucket coverage tracker — NeetCode 150 order

Following the NC150 topological order (correct — don't fight it). "Prior" = evidence from CF tags + local archive.

"Prior" = POTD-corrected LeetCode floor (see above), so these are *conservative*.

| # | Bucket | NC150 | Genuine prior (floor) | Mode |
|---|---|---|---|---|
| 1 | Arrays & Hashing | 🟡 in progress | Array 61 · Hash 30 | recovery |
| 2 | Two Pointers | 🟡 in progress | 11 | ✅ owned now |
| 3 | Stack | ⬜ | 6 (monotonic 4) | recovery, thin |
| 4 | **Sliding Window** | ⬜ **next** | 6 | recovery |
| 5 | Binary Search | ⬜ | 9 | recovery |
| 6 | Linked List | ⬜ | 4 | recovery, thin |
| 7 | Trees | ⬜ | Tree 11 · BinTree 11 · DFS 20 · BFS 16 | **recovery** |
| 8 | Tries | ⬜ | 5 | recovery, shallow |
| 9 | **Heap / Priority Queue** | ⬜ | **0** | 🔴 **TRUE GAP — learn** |
| 10 | Backtracking | ⬜ | 12 | recovery |
| 11 | Graphs | ⬜ | Graph 5 · Union-Find 6 | recovery, thin |
| 12 | **Advanced Graphs** | ⬜ | Shortest Path 1 · TopoSort 2 | 🔴 **near-gap — learn** |
| 13 | 1-D DP | ⬜ | DP 21 combined | recovery |
| 14 | 2-D DP | ⬜ | (part of DP 21) | recovery, thin |
| 15 | Greedy | ⬜ | 6 (CF greedy 64) | recovery |
| 16 | Intervals | ⬜ | — | thin |
| 17 | Math & Geometry | ⬜ | Math 14 (CF math 60) | recovery |
| 18 | Bit Manipulation | ⬜ | 6 (CF bitmasks 6) | recovery |

🔴 = genuine void, not rust. **Heap is the single clearest hole in the entire profile — prioritize bucket 9 and do not let the NC150 order defer it too long.**

**Next up:** Sliding Window (NC150 order). Most buckets are *recovery* — expect faster progress than the problem count suggests. Reserve real learning time for **Heap** and **Advanced Graphs** only.

---

## Related

- [Optimization ladder](dsa-patterns/optimization-ladder.md) — the "can you do better?" drill
- [Two pointers — the two variants](dsa-patterns/two-pointer-variants.md)
