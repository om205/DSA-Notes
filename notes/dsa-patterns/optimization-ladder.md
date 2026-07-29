# "Can You Do Better?" — The Optimization Ladder — Flashcards

- Topic: DSA Meta — how to improve a working solution on demand
- Source: Trapping Rain Water post-mortem (mentor session) — "switching to a completely different approach feels impossible"
- Date: 2026-07-28
- Real example: `problems/two-pointers/hard/Trapping Rain Water/` — my own O(n)-space solution reduced to O(1) *without changing approach*

> **How to use:** This is the drill for the moment an interviewer says "can you do better?" Read the question, answer OUT LOUD, then expand. Run **Q1–Q4 on every problem I solve**, before looking at any editorial.

---

## The core reframe

<details>
<summary><b>Q1. ⭐</b> Interviewer asks "can you do better?" What are the first two things I do — and what do I NOT do?</summary>

**Do NOT** start brainstorming a completely different algorithm. That is unreliable under pressure and usually unnecessary.

1. **Ask which resource and what target.** *"Better on time or space? Are you thinking O(1) space?"* This is what a senior engineer does — it converts an open-ended creative task into a constrained search.
2. **Squeeze my EXISTING solution first.** Most "optimal" solutions are one squeeze away from what I already wrote.

**Proof from my own history:** on Trapping Rain Water I wrote an original O(n)-time / O(n)-space solution and assumed the O(1) answer required the canonical two-pointer I hadn't thought of. Wrong — replacing my two prefix-sum arrays with one running scalar made *my own approach* O(1). The "creative leap" was worth zero asymptotic improvement. I just never asked.
</details>

<details>
<summary><b>Q2. ⭐</b> The three squeeze questions, in order.</summary>

1. **What am I storing that I don't need all of?** → array read only near my pointers = collapse to a scalar. *(This is the one I miss.)*
2. **What am I recomputing that I could carry forward?** → running sum/max/count instead of a rescan.
3. **What am I computing that never gets used?** → dead code. *(On Trapping I built `max_pos` with a full O(n) pass and never read it.)*

60 seconds. Run it every time.
</details>

---

## Reason backward from the target

<details>
<summary><b>Q3. ⭐</b> Why is reasoning BACKWARD from the target complexity so much easier than brainstorming forward?</summary>

Because the target **forbids** things, and what's forbidden eliminates most of the search space. Forward brainstorming is unbounded; backward reasoning is a short list.

| Target | Forbids | So what's left |
|---|---|---|
| **O(1) space** | arrays, maps, deep recursion | Which array do I read only near my pointers? → scalar. Rolling DP row. In-place / reuse output. Encode state in the input. |
| **O(n) time** (from O(n log n)) | sorting | Order without sorting: hashing, counting sort, monotone structure, heap |
| **O(n log n)** (from O(n²)) | nested scans | Sort → two pointers / greedy; heap; divide & conquer; binary search |
| **O(log n)** | touching every element | Binary search on a **monotone predicate** |
| **polynomial** (from exponential) | re-solving subproblems | Memoize → tabulate → rolling array |
</details>

---

## The ladder (only after squeezing fails)

<details>
<summary><b>Q4.</b> Standard TIME transformations — the ~10 that cover most interview follow-ups.</summary>

1. **Sort first** → unlocks two pointers / greedy / binary search. `O(n²) → O(n log n)`
2. **Hash map for lookup** → `O(n²) → O(n)`, trades space
3. **Prefix sums** → range query `O(n) → O(1)`
4. **Binary search on the ANSWER** → `O(n·range) → O(n log range)` (when a predicate is monotone in the answer)
5. **Monotonic stack / deque** → "next greater", "window max" `O(n²) → O(n)`
6. **Heap** → streaming top-k `O(n log k)`
7. **Memoize overlapping subproblems** → exponential → polynomial
8. **Two pointers replacing nested loops** → `O(n²) → O(n)` when sorted or monotone
9. **Counting / bit tricks** instead of comparison
10. **Meet in the middle** → `O(2^n) → O(2^(n/2))`
</details>

<details>
<summary><b>Q5.</b> Standard SPACE transformations.</summary>

1. **Running scalar instead of a prefix/suffix array** ← *my standing weak spot*
2. **Rolling array in DP** — keep only last 1–2 rows. `O(n²) → O(n)`
3. **In-place / reuse the output or input array**
4. **Encode state in the input** — negate values as "visited", `a[i] += n * flag`
5. **Two pointers instead of building a filtered copy**
6. **Iterative + explicit stack** instead of recursion; **Morris traversal** for O(1) tree walks
</details>

---

## Self-check

- [ ] Ask "which resource, what target?" before optimizing — reflex, not afterthought.
- [ ] Run the three squeeze questions on every solve before reading any editorial.
- [ ] Given a target complexity, name what it *forbids* within 10 seconds.
- [ ] Spot a prefix/suffix array that could be a scalar.

---

## Related

- [[two-pointer-variants]] — Q5f is the specific collapse I keep missing: *answer = min/max of a left-quantity and a right-quantity → two pointers, advance the shorter side, running scalar.*
