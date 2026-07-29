# Trapping Rain Water

- Difficulty: Hard
- Topic: Array, Two Pointers, Dynamic Programming, Stack, Monotonic Stack
- Platform: LeetCode
- Link: https://leetcode.com/problems/trapping-rain-water/description/

---

## Problem Statement

Given `n` non-negative integers representing an elevation map where the width of each bar is 1, compute how much rainwater it can trap after raining. The elevation map is represented by an array `height`, where `height[i]` is the height of the bar at index `i`. The goal is to calculate the total amount of water that can be trapped between these bars.

---

## Examples

### Example 1

```txt
Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]

Output: 6
```

Explanation: The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped.

### Example 2

```txt
Input: height = [4,2,0,3,2,5]

Output: 9
```

Explanation: Water trapped can be visualized by finding the minimum of the max left and max right heights for each position and subtracting the current bar's height.

---

## Constraints

- `n == height.length`
- `1 <= n <= 2 * 10^4`
- `0 <= height[i] <= 10^5`
---

## Intuition

The amount of water trapped at any position `i` is determined by the minimum of the maximum height to its left and the maximum height to its right, minus its own height. If the current bar's height is greater than or equal to this minimum, no water is trapped at that position. This observation allows us to calculate water trapped by either pre-calculating left and right maximums or by using a two-pointer approach to determine these values efficiently.

---

## My solution — prefix-sum bulk fill (non-textbook)

This is the payoff of the Container lesson. There, precomputing prefix arrays **couldn't** help, because `min(h[i],h[j])*(j-i)` couples two endpoints and doesn't decompose. Here it's the opposite:

> Water trapped between a left wall `slow` and the next taller wall `fast` is a **rectangle minus the solid bars inside it**:
> ```
> water = (fast - slow) * height[slow]  -  sum(height[slow .. fast-1])
> ```
> The `sum(...)` term is a **range-sum query** → a prefix-sum array answers it in O(1). That's why precompute *works here and failed on Container*: trapping decomposes into `rectangle − solid`, and `solid` is a range sum.

The algorithm:

1. **Left-to-right pass.** Keep a left wall `slow`; advance `fast` until it finds a strictly taller wall. Everything skipped is shorter, so it's a pit bounded on the left by `height[slow]`. Add its water in one shot with the formula above, then jump `slow = fast`. This captures all **left-bounded** water (the ascending side up to the global max).
2. **Right-to-left pass.** Mirror image, capturing **right-bounded** water.
3. **The strict/non-strict asymmetry** is the subtle part: the left pass skips on `<=` (adds only on strictly taller), the right pass skips on `<` (adds on `>=`). This makes water bounded by two **equal-height** walls (e.g. `[2,0,2]`) get counted *exactly once* — by the right pass — instead of missed by both or double-counted. It also removes any need to explicitly find the peak (the leftover `max_pos` variable is vestigial and should be deleted).

Complexity as submitted: **O(n) time, O(n) space** (the two prefix-sum arrays).

### ⭐ Squeezing MY approach to O(1) space — no new algorithm needed

The prefix-sum arrays are only ever read at `slow` and `fast`. Since `fast` moves forward one step at a time and `slow` only jumps to `fast`, the needed range sum `sum(height[slow..fast-1])` can be **carried in a single scalar**:

```cpp
int trap(vector<int>& height) {
    int len = height.size();
    if (len < 2) return 0;
    ll vol = 0;
    int slow = 0, fast = 1; ll seg = height[0];   // seg = sum(height[slow..fast-1])
    while (fast < len) {
        if (height[fast] <= height[slow]) { seg += height[fast]; ++fast; continue; }
        vol += 1ll*(fast - slow)*height[slow] - seg;
        slow = fast++; seg = height[slow];
    }
    slow = len-1; fast = len-2; seg = height[len-1];
    while (fast >= 0) {
        if (height[fast] < height[slow]) { seg += height[fast]; --fast; continue; }
        vol += 1ll*(slow - fast)*height[slow] - seg;
        slow = fast--; seg = height[slow];
    }
    return vol;
}
```

**5 passes + 2 arrays → 2 passes + 2 scalars. O(n) time, O(1) space** — asymptotically identical to the canonical solution below. *(Verified against the canonical solution on 200,000 randomized tests.)*

**The lesson that matters more than the algorithm:** the "creative leap" to the canonical two-pointer was worth **zero** asymptotic improvement over simply squeezing what I already had. When asked "can you do better?", interrogate the existing solution *before* hunting for a different one. See [the optimization ladder](../../../../notes/dsa-patterns/optimization-ladder.md).

### The canonical O(1) solution — know this too

Interviewers usually expect the constant-space two-pointer:

```cpp
int trap(vector<int>& height) {
    int l = 0, r = (int)height.size() - 1;
    int leftMax = 0, rightMax = 0, water = 0;
    while (l < r) {
        if (height[l] < height[r]) {          // left wall is the limiter
            leftMax = max(leftMax, height[l]);
            water += leftMax - height[l];
            ++l;
        } else {
            rightMax = max(rightMax, height[r]);
            water += rightMax - height[r];
            --r;
        }
    }
    return water;
}
```

Same "the shorter side is the bottleneck, so move it" logic as Container With Most Water — the water at a cell is fixed the moment you know the smaller of the two running maxes. O(1) space because it never stores the sums; it adds per-cell instead of per-segment.

### Two C++ gotchas this problem surfaced

- **`fast++, continue;` won't compile.** The comma operator sequences *expressions*; `continue` is a *statement*. Use a block: `{ fast++; continue; }`.
- **`for (int i = 0, ll sum = 0; ...)` won't compile.** One declaration = one base type for all names. Make both `ll`, or declare separately. (The `#define ll` macro makes the error message cryptic — a `using ll = long long;` alias reads better.)

Full pattern reference: [Two Pointers — the two variants](../../../../notes/dsa-patterns/two-pointer-variants.md) · C++ traps: [declaration & comma gotchas](../../../../notes/cpp/declaration-comma-gotchas.md)

---

## Takeaways

- The 'min of maxes' concept is fundamental for water trapping problems.
- Dynamic Programming can be used to pre-compute maximums to the left and right.
- An optimized two-pointer approach can solve the problem in O(1) space by maintaining `max_left` and `max_right` dynamically.
- Monotonic stack is an alternative approach that can find bounding walls for each potential 'pit' efficiently.
- Trapping decomposes as `rectangle − solid bars`, and the solid-bar term is a range sum — so prefix sums genuinely help here, the mirror of why they failed on Container With Most Water.
- The strict/non-strict (`<=` vs `<`) asymmetry between the two directional passes is what counts water bounded by equal-height walls exactly once.

## C++ Concepts

- **Comma operator vs. statement** — `a, b` sequences two *expressions*; `continue`/`break`/`return` are *statements* and cannot be comma operands. `fast++, continue` fails to compile → use `{ fast++; continue; }`.
- **One base type per declaration** — `int i = 0, ll sum = 0` is illegal; all comma-separated declarators share the first type. Use `ll i = 0, sum = 0` or split the declaration.
- **`#define ll long long` (macro) vs `using ll = long long;` (alias)** — the macro is textual substitution and produces confusing diagnostics (the error points inside the macro). A type alias is scoped and gives cleaner errors. Prefer the alias.
- **`vector<ll>` for prefix sums** — sums of up to `2e4` bars of height `1e5` reach `~2e9`, past `INT_MAX`. Storing sums (and the accumulator `vol`) as `long long` is the correct overflow guard — and unlike the Container solve, the wide type reaches the storage, so the guard actually holds.
- **`int len = height.size();`** — narrowing `size_t → int`; fine for `n ≤ 2e4`, but the deliberate-cast habit (`(int)height.size()`) still applies. See [signed vs. unsigned pitfalls](../../../../notes/cpp/signed-unsigned-pitfalls.md).
