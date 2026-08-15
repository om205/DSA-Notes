# Loop Skeletons — Type These BEFORE Thinking About the Problem

- Topic: DSA Meta — canonical loop structures
- Source: Longest Repeating Character Replacement (mentor session) — *"there's a certain way for writing optimal code. How to reach that stage?"*
- Date: 2026-08-13

> **How to use:** This is not a flashcard file. It is a **copy-paste reference.** When you recognize the pattern, type the skeleton *first* — blank — then fill in the 2–3 problem-specific holes. You cannot drift into chaos if the shape is already on screen.

---

## The two principles

**1. Structure follows from the invariant.**

Every placement decision — expand at top or bottom, record before or after, `if` or `while` — is *forced* once you decide what must be true at the end of each iteration. A weak invariant ("the window may or may not be valid") forces branching, conditional recording, and sentinel iterations. A strong invariant ("the window IS valid here") makes the code straight-line.

> **If you need a sentinel iteration or a flag, your invariant is wrong.** Strengthen it; don't patch around it.

**2. Nobody derives these in the moment — they are recalled.**

Clean solutions are not produced by superior in-the-moment reasoning. Strong candidates pattern-match to a shape they have written 50 times and fill in the blanks. That is why good solutions look effortless: they *are* effortless. The skill is recall, not invention.

**Corollaries:**
- Separate **progress** (expand) from **repair** (shrink). Tangling them into one if/else is what produces branchy code.
- **One variable should advance unconditionally**, so loop progress and termination are obvious at a glance.

---

## ⭐ Invariants — the core idea (REVISIT THIS OFTEN)

> Flagged 2026-08-15 as a foundational concept to re-read repeatedly until automatic.

### What an invariant actually is

A property that holds **at a fixed point in every iteration** — usually the top or the bottom of the loop body. The variables absolutely change every pass; what stays constant is the **relationship between them**.

*Common misunderstanding:* "the thing that doesn't change." Wrong emphasis — `l` and `r` change constantly. What doesn't change is that *"`[l, r]` is valid"* remains true at the bottom of each iteration.

### Why it determines the whole structure

**You may only record where the invariant holds.** That single fact fixes where the `ans = max(...)` line goes, which fixes whether you expand before or after, which fixes whether shrinking is an `if` or a `while`. Structure is a *consequence*, not a choice.

### The 4-step procedure

1. Before writing anything, say out loud: **"At the end of each iteration, ___ is true."**
2. Pick the **strongest** thing you can maintain **cheaply**.
3. **If maintaining it requires a sentinel iteration, a flag, or a special case → wrong invariant.** Weaken it or pick a different one. Do not patch around it.
4. Structure the body as: **make progress → restore the invariant → use it.**

### Convention: `[l, r]` vs `[l, r)` — pick one, never mix

| Convention | Natural loop | Size expression |
|---|---|---|
| `[l, r]` **inclusive** ← default | `for (r = 0; r < n; ++r)` | `r - l + 1` |
| `[l, r)` half-open | `while (r < n)` | `r - l` |

This is a *convention*, not the invariant. **Mixing them is where off-by-ones breed** — the `r <= len` + `if (r < len)` sentinel in the first LRCR attempt came from exactly this.

### Invariant per skeleton

| Skeleton | Invariant |
|---|---|
| Sliding window | `[l, r]` is valid at the bottom of each iteration |
| Binary search | the answer lies in `[lo, hi]` |
| Two pointers (opposite) | the answer, if any, lies within `[l, r]` |
| BFS | the queue holds exactly the frontier at distance `d` |
| Monotonic stack | the stack is strictly increasing, bottom to top |
| Backtracking | `path` is a valid partial solution on entry **and** on exit |
| DP loop | `dp[i]` is finalized for every index `< i` |

### ⚠️ No invariant is universal — the LRCR counterexample

**Longest Repeating Character Replacement deliberately abandons "the window is valid."**

Its optimal solution never decreases `maxFreq`, so `maxFreq` goes stale and the window can be genuinely invalid. Trace `s="AAAABC"`, `k=0`: at `r=4` the window is `[1,4]="AAAB"` with `maxFreq` stale at 4 — true max is 3, so it needs 1 replacement and is invalid. The algorithm keeps it anyway.

It's still correct, under a **weaker** invariant:

> **The window size never exceeds the largest valid window seen so far.**

Why that's enough:
1. **The window never shrinks.** Before iteration `r`: `(r-l) - M_old ≤ k`. After expanding, `(r-l+1) - M_new ≤ (r-l+1) - M_old = (r-l-M_old) + 1 ≤ k+1`. The violation is at most 1 → one eviction fixes it → the `while` runs at most once → size goes +1 or stays, never down.
2. **Therefore `ans` is just the final window size** — the `max()` is cosmetic.
3. **A stale `maxFreq` makes the window coast, not grow.** Growth requires `maxFreq` to genuinely increase, which requires a real count to hit a new high in a real window. So an invalid window can never *inflate* the answer — only fail to shrink.

**The lesson:** the skill is not memorizing one invariant. It is asking *"what is the strongest thing I can keep true cheaply, and where does it hold?"* — and sometimes the answer is deliberately weaker than the obvious one.

---

## 1. Sliding window (variable size)

```cpp
int l = 0, ans = 0;
for (int r = 0; r < n; ++r) {
    add(a[r]);                                 // expand — may break the invariant
    while (invalid()) { remove(a[l]); ++l; }   // repair it
    ans = max(ans, r - l + 1);                 // invariant holds → record unconditionally
}
```
**Holes:** `add`, `invalid()`, `remove`.
**Invariant:** at the end of each iteration, `[l, r]` is valid.
*Problems: Longest Substring Without Repeating, Longest Repeating Char Replacement, Minimum Window Substring, Permutation in String.*

## 2. Sliding window (fixed size k)

```cpp
for (int r = 0; r < n; ++r) {
    add(a[r]);
    if (r >= k) remove(a[r - k]);              // evict exactly one
    if (r >= k - 1) ans = best(ans, current);
}
```

## 3. Two pointers — opposite ends

```cpp
int l = 0, r = n - 1;
while (l < r) {
    // evaluate the pair (l, r)
    if (cond) ++l;                             // discard l forever
    else --r;                                  // discard r forever
}
```
**Invariant:** the answer, if it exists, lies within `[l, r]`.
*Problems: Two Sum II, Container With Most Water, Valid Palindrome, 3Sum inner loop.*

## 4. Two pointers — skip/filter

```cpp
while (l < r) {
    while (l < r && !ok(a[l])) ++l;            // guard FIRST, then access
    while (l < r && !ok(a[r])) --r;
    // ... compare a[l], a[r]
    ++l; --r;
}
```

## 5. Binary search — lower bound (the only form worth memorizing)

```cpp
int lo = 0, hi = n;                            // [lo, hi) half-open
while (lo < hi) {
    int mid = lo + (hi - lo) / 2;              // no overflow
    if (pred(mid)) hi = mid;                   // pred is FALSE...FALSE,TRUE...TRUE
    else lo = mid + 1;
}
return lo;                                     // first index where pred is true
```
**Invariant:** answer is in `[lo, hi]`. Works for binary-search-on-answer too — just change `pred`.

## 6. BFS (shortest path / level order)

```cpp
queue<T> q; q.push(start);
seen.insert(start);                            // mark on PUSH, never on pop
int depth = 0;
while (!q.empty()) {
    int sz = q.size();                         // freeze the level
    while (sz--) {
        T cur = q.front(); q.pop();
        for (T nx : neighbors(cur))
            if (!seen.count(nx)) { seen.insert(nx); q.push(nx); }
    }
    ++depth;
}
```

## 7. DFS (recursive)

```cpp
void dfs(T cur) {
    if (base_case) return;
    seen.insert(cur);
    for (T nx : neighbors(cur))
        if (!seen.count(nx)) dfs(nx);
}
```

## 8. Backtracking

```cpp
void bt(int i, vector<int>& path) {
    if (done(i)) { out.push_back(path); return; }
    for (auto choice : choices(i)) {
        path.push_back(choice);                // choose
        bt(i + 1, path);                       // explore
        path.pop_back();                       // UN-choose  ← the whole pattern
    }
}
```

## 9. Monotonic stack (next greater / previous smaller)

```cpp
stack<int> st;                                 // holds INDICES
for (int i = 0; i < n; ++i) {
    while (!st.empty() && a[st.top()] < a[i]) {
        int j = st.top(); st.pop();
        // a[i] is the next-greater for j — resolve j here
    }
    st.push(i);
}
```

---

## Self-check

- [ ] Can I type skeleton #1 from memory, blank, in under 20 seconds?
- [ ] Given a problem, can I name the invariant *before* writing the loop?
- [ ] When I catch myself adding a sentinel iteration or a flag, do I stop and re-derive?
- [ ] Can I state, in one sentence, why an invariant determines *where I record*?
- [ ] Can I reproduce the two-line proof that the LRCR window never shrinks?
- [ ] Am I consistent about `[l, r]` inclusive — `for` loop, `r - l + 1` sizing — every single time?

## Revisit schedule

Invariants are foundational and slippery; re-read the ⭐ section on a spaced schedule rather than once.

| Pass | Target date | Focus |
|---|---|---|
| 1 | 2026-08-18 | Re-read ⭐ section; re-solve LRCR cold using skeleton #1 |
| 2 | 2026-08-25 | Name the invariant aloud before every problem for a week |
| 3 | 2026-09-08 | Self-check list above, from memory, no peeking |

---

## Related

- [Two pointers — the two variants](two-pointer-variants.md) — when to reach for #1 vs #3
- [The optimization ladder](optimization-ladder.md) — the squeeze pass, after the structure is right
