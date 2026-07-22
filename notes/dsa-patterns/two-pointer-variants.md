# Two Pointers — The Two Variants — Flashcards

- Topic: DSA Patterns — two pointers, sliding window
- Source: Two Sum II solve (mentor session) — the "why is it safe to discard R?" question
- Date: 2026-06-11
- Real examples: `problems/two-pointers/medium/Two Sum II - Input Array Is Sorted/`, `problems/two-pointers/easy/Valid Palindrome/`

> **How to use:** Read the question, answer it OUT LOUD from memory, *then* expand the answer. Don't peek first — the retrieval is what builds the memory. Revisit weekly.

---

## The distinction

<details>
<summary><b>Q1.</b> "Two pointers" covers two structurally different patterns. What are they, and what question shape does each answer?</summary>

| | **Opposite ends** (converging) | **Same direction** (sliding window) |
|---|---|---|
| Question shape | Find a **pair / triple** satisfying X | Find a **contiguous segment** satisfying X |
| Needs sorted input? | **Yes** (or sortable) | Usually no |
| Start position | `l = 0`, `r = n-1` | both at `0` |
| Terminates when | pointers cross (`l >= r`) | `r` reaches the end |
| Mechanism | **Eliminates** candidates | **Maintains** an invariant |

**One-liner:** *Opposite ends narrows a search using sortedness. Same direction maintains an invariant using monotonicity.* Both O(n). Not the same thing.
</details>

<details>
<summary><b>Q2.</b> Give 3 canonical problems for each variant.</summary>

**Opposite ends:** Two Sum II, 3Sum, Container With Most Water, Trapping Rain Water, Valid Palindrome.

**Same direction:** Longest Substring Without Repeating Characters, Minimum Window Substring, Longest Repeating Character Replacement, Remove Duplicates from Sorted Array (in-place).
</details>

---

## The key insight (the part that was confusing)

<details>
<summary><b>Q3.</b> In Two Sum II, when <code>sum > target</code>, why is it safe to do <code>r--</code> and not <code>l++</code>?</summary>

Because `l` is **already pointing at the smallest live element**. If `arr[l] + arr[r]` already overshoots the target, then pairing `arr[r]` with anything *bigger* than `arr[l]` overshoots even harder.

Formally: for every `i` in `[l, r-1]`, we have `arr[i] >= arr[l]` (sorted), so

```
arr[i] + arr[r] >= arr[l] + arr[r] > target
```

So **`arr[r]` cannot be part of the answer with ANY remaining partner.** It's not "this pair failed" — it's "this *element* is dead." Discard it: `r--`.

One move eliminates an entire row of the O(n²) pair grid. That's why it's O(n).
</details>

<details>
<summary><b>Q4. ⭐ THE ONE I GOT STUCK ON.</b> "If I move <code>r</code> left now, and later move <code>l</code> right — wouldn't that new <code>l</code> have needed the <code>r</code> I already threw away?"</summary>

**No — and this is the whole trick.**

When we discarded `r`, we didn't prove "`r` fails against the *current* `l`." We proved "`r` fails against **every index in `[l, r-1]`**" — the entire remaining window.

And `l` only ever *increases*, always staying inside that window. So every future value of `l` was **already covered by the proof** at the moment we dropped `r`. The discarded `r` is dead for all time, not just for that one comparison.

> The elimination is **universally quantified over the future**, not a one-off check. That's why the algorithm never needs to backtrack.

Same argument mirrored when `sum < target`: `arr[l]` is too small to reach the target even with the *largest* live partner `arr[r]`, so `arr[l]` is dead against everything in `[l+1, r]`. `l++`.
</details>

<details>
<summary><b>Q5.</b> What's the mental image for opposite-ends?</summary>

**Two detectives working a lineup from both ends.** Each round, one of them proves the suspect in front of them is innocent *against every remaining suspect*, and steps inward. Nobody gets re-questioned.
</details>

---

## Same-direction / sliding window

<details>
<summary><b>Q6.</b> In a sliding window, why does <code>l</code> never move backwards?</summary>

Because any window ending at `r` with `l` further left would **contain** the current window plus extra elements — and that extra is exactly what broke the invariant (the duplicate char, the excess count, whatever). Backing `l` up can only re-introduce the violation, never fix it.

Both pointers are **monotonic**: each travels `0 → n` at most once. Total work `2n = O(n)`, even though the code *looks* like a nested loop.
</details>

<details>
<summary><b>Q7.</b> What's the mental image for same-direction?</summary>

**An inchworm.** The head (`r`) crawls forward greedily, expanding the window. The tail (`l`) only catches up when the worm gets stretched into an invalid state. Head and tail both only ever move forward.
</details>

<details>
<summary><b>Q8.</b> Sketch the skeleton of a sliding-window solution.</summary>

```cpp
int l = 0, best = 0;
for (int r = 0; r < n; ++r) {
    add(arr[r]);                       // expand
    while (!valid()) { remove(arr[l]); ++l; }   // shrink until valid again
    best = max(best, r - l + 1);       // record
}
```

Three beats every time: **expand → restore invariant → record.**
</details>

---

## The decision rule

<details>
<summary><b>Q9.</b> Cold-start a new problem. What do you ask, in order, to pick the variant?</summary>

1. **Pair/triple of elements, or a contiguous window?**
   - Pair → opposite ends. Window → same direction.
2. **If pair: is it sorted, or can I sort without losing what I need?**
   - Sorted → opposite ends.
   - Can't sort (need original indices of unsorted input) → **hash map**, not two pointers. *(This is plain Two Sum I.)*
3. **If window: does expanding `r` break something that shrinking `l` can repair?**
   - Yes → sliding window.
   - No, expanding is always safe → you don't need `l` at all, just walk `r`.
</details>

<details>
<summary><b>Q10.</b> There's a third variant. What is it and where does it show up?</summary>

**Fast/slow pointers** — both start at the head, but one moves 2 steps per 1 step of the other. Almost exclusively **linked lists**:

- **Cycle detection** (Floyd's) — if a loop exists, fast laps slow.
- **Find the middle** — when fast hits the end, slow is at the midpoint.
- **Remove Nth from end** — give fast an N-step head start, then walk both.

Trigger: problem is on a linked list and asks about *position / middle / cycle*.
</details>

---

## Self-check

After a week, can you:

- [ ] State the opposite-ends vs same-direction difference in one sentence?
- [ ] Prove *why* discarding `r` is safe, including the "future `l`" objection (Q4)?
- [ ] Write the sliding-window skeleton from memory without looking?
- [ ] Pick the right variant for a cold problem using the Q9 rule?

If yes — promote to monthly. If no — stay weekly.

---

## Related

- [[signed-unsigned-pitfalls]] — `r = v.size() - 1` is the standard opposite-ends initializer, and the standard place this C++ bug bites.
