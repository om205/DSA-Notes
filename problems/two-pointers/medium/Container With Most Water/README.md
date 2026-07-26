# Container With Most Water

- Difficulty: Medium
- Topic: Array, Two Pointers, Greedy
- Platform: LeetCode
- Link: https://leetcode.com/problems/container-with-most-water/description/

---

## Problem Statement

You are given an integer array `height` of length `n`. There are `n` vertical lines drawn such that the two endpoints of the `i`th line are `(i, 0)` and `(i, height[i])`. Find two lines that together with the x-axis form a container, such that the container contains the most water. Return the maximum amount of water a container can store. Notice that you may not slant the container.

---

## Examples

### Example 1

```txt
Input: height = [1,8,6,2,5,4,8,3,7]

Output: 49
```

Explanation: The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case, the max area of water (blue section) the container can contain is 49. This is achieved by lines at indices 1 (height 8) and 8 (height 7), where min(8,7) * (8-1) = 7 * 7 = 49.

### Example 2

```txt
Input: height = [1,1]

Output: 1
```

Explanation: With lines of height 1 at indices 0 and 1, the area is min(1,1) * (1-0) = 1 * 1 = 1.

---

## Constraints

- `n == height.length`
- `2 <= n <= 10^5`
- `0 <= height[i] <= 10^4`
---

## Intuition

The problem asks to find the maximum area formed by two vertical lines and the x-axis, where the area is determined by the shorter line's height multiplied by the distance between the lines. A brute-force approach checking all pairs of lines would be O(n^2). An optimized approach uses two pointers, one at the beginning and one at the end of the array. At each step, calculate the current area. To potentially find a larger area, move the pointer associated with the *shorter* line inward. This is because moving the taller line's pointer inward would either keep the minimum height the same or decrease it, while always decreasing the width, thus guaranteeing a smaller or equal area. Moving the shorter line's pointer offers the chance to find a taller line, which could increase the minimum height and potentially the overall area despite the decreasing width.

---

## Why precomputation doesn't win here (the real lesson)

I first tried prefix-max / suffix-max arrays — the tool that works for Trapping Rain Water. It fails here, and understanding *why* is the whole point of this problem.

### The structural reason

- **Trapping Rain Water decomposes per index:** `water[i] = min(preMax[i], sufMax[i]) − h[i]`. Each cell's answer depends only on its own left-max and right-max, so precomputed arrays nail it.
- **Container does not decompose:** `area(i,j) = min(h[i], h[j]) × (j − i)` couples *both* endpoints. No per-index precompute can represent a quantity that depends on two walls at once. Same-looking problems, different structure.

Also: "tallest wall to the left" is not the best partner. Fixed right wall of height 5; left candidate A = height 100 at distance 1 gives `min(100,5)×1 = 5`, candidate B = height 5 at distance 10 gives `min(5,5)×10 = 50`. The prefix-max array points at A — the wrong wall.

### The staircase observation (this part IS correct)

There *is* a true structural fact here, and it's worth stating precisely because it's a hair from the optimal solution:

> **Domination lemma.** For a fixed right wall `i` and two left walls `a < b < i` with `h[a] ≥ h[b]` (farther *and* at least as tall), `(a,i)` dominates `(b,i)`: it's both wider (`i−a > i−b`) and no shorter (`min(h[a],h[i]) ≥ min(h[b],h[i])`). So `area(a,i) ≥ area(b,i)` always.

**Corollary:** the optimal left partner for `i` can never be a wall that has a taller-or-equal wall to its left. The only survivors are the **prefix maxima** — "highest on the left, highest to the left of that, …". So the best partner *is* on that staircase.

**But it's not optimal in time.** On a strictly increasing array `[1,2,…,n]`, every wall is a prefix max, so each `i`'s staircase has length `i`, and scanning them all is `∑ i = O(n²)` — dead at `n = 10⁵`.

### How two pointers collapses it to O(n)

Two pointers *is* this staircase, walked from both ends simultaneously. When `h[l] < h[r]`, wall `l` is the limiter at maximum width — by the domination lemma no closer partner can beat what we just recorded, so `l` is discarded forever. Advancing `l` to the next taller wall is climbing the left staircase; `r` climbs the right one inward at the same time. Every wall is visited once → `O(n)`. Same domination principle, no `O(n²)` traversal.

Full pattern reference: [Two Pointers — the two variants](../../../../notes/dsa-patterns/two-pointer-variants.md)

---

## Takeaways

- Two Pointers is a powerful technique for optimizing problems involving arrays where relative order matters and calculations involve endpoints.
- The greedy choice of moving the pointer associated with the shorter line is crucial. This strategy maximizes the chance of increasing the effective height (min_height) of the container.
- Understanding the trade-off between increasing height and decreasing width is key. By moving the shorter pointer, we prioritize the possibility of a greater height to offset the inevitable decrease in width.
- A quantity that couples two indices (like `min(h[i],h[j])*(j-i)`) cannot be captured by per-index precomputation; that is exactly what separates this problem from Trapping Rain Water, which decomposes per index.
- The optimal partner for a fixed endpoint lives on the prefix-max staircase (domination lemma), and two pointers walks that staircase from both ends in O(n) instead of O(n^2).

## C++ Concepts

- **`size()` returns `size_t` (unsigned)** — `int r = height.size() - 1;` is the recurring underflow trap; safe here only because `n >= 2`. Prefer a deliberate `(int)height.size() - 1`. See [signed vs. unsigned pitfalls](../../../../notes/cpp/signed-unsigned-pitfalls.md).
- **`1ll * a * b` overflow guard** — promoting one operand to `long long` forces the multiply into 64-bit, avoiding mid-expression overflow. But it only helps if the *result is stored* in a 64-bit variable; assigning back into `int` truncates and defeats the guard. Here the true max (`1e5 * 1e4 = 1e9`) fits in `int` anyway, so the promotion is unnecessary.
- **`abs(r - l)`** — redundant when a loop invariant already guarantees `r > l`. Drop it; `r - l` is provably non-negative.
- **Declare at first use** — `int area = ...;` inside the loop beats a hoisted, uninitialized `int area;`. Narrowest scope, no uninitialized window.
- **`std::min` / `std::max` from `<algorithm>`** — both take two args of the same type and return by const-ref; fine for `int` here.
