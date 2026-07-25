# 3Sum

- Difficulty: Medium
- Topic: Array, Two Pointers, Sorting
- Platform: LeetCode
- Link: https://leetcode.com/problems/3sum/description/

---

## Problem Statement

Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0. Notice that the solution set must not contain duplicate triplets.

---

## Examples

### Example 1

```txt
Input: nums = [-1,0,1,2,-1,-4]

Output: [[-1,-1,2],[-1,0,1]]
```

Explanation: The distinct triplets that sum to zero are [-1,0,1] and [-1,-1,2]. Other combinations like [-1,2,-1] are duplicates.

### Example 2

```txt
Input: nums = [0,1,1]

Output: []
```

Explanation: The only possible triplet [0,1,1] does not sum to 0.

### Example 3

```txt
Input: nums = [0,0,0]

Output: [[0,0,0]]
```

Explanation: The only possible triplet [0,0,0] sums to 0.

---

## Constraints

- `3 <= nums.length <= 3000`
- `-10^5 <= nums[i] <= 10^5`
---

## Intuition

To find unique triplets that sum to zero, a crucial first step is to sort the array. This helps in efficiently handling duplicates and enables the use of the Two Pointers technique. By iterating through the sorted array and fixing one element `nums[i]`, the problem is reduced to finding two other elements `nums[left]` and `nums[right]` in the remainder of the array `nums[i+1...n-1]` that sum to `-nums[i]`. This 2Sum subproblem can be solved efficiently with two pointers moving inwards.

---

## Solution — the journey (why the final one looks like it does)

I went through three stages on this problem. Keeping all three because the *contrast* is the lesson.

### Attempt 1 — hashmap (abandoned)

Idea: store `value -> indices`, then for each pair `(i, j)` look up `-(nums[i] + nums[j])`. This is the natural extension of Two Sum I's hashmap trick.

**Why it got messy:** the hashmap solves *finding* the third number, but it does nothing for the hard part of 3Sum — **deduplication**. The output must contain no duplicate *triplets*, and with an unsorted array the same triplet appears via different index orderings (`[-1,0,1]` found as `(i,j,k)` and again as `(k,j,i)`). You end up canonicalising every triplet (sort it, hash the sorted form into a `set<vector<int>>`) just to dedupe — which is exactly the overhead sorting the input would have removed for free. The hashmap optimises the easy sub-problem and leaves the hard one untouched.

**Takeaway:** in N-Sum, the enemy is duplicates, not lookup speed. Pick the approach that makes *dedup* cheap.

### Attempt 2 — sort + two pointers + `set` (works, but wasteful)

Sort, fix `nums[i]`, run opposite-ends two pointers on the suffix to find pairs summing to `-nums[i]`. Dump every found triplet into a `set<vector<int>>` to dedupe, then copy the set into the answer.

Correct, but the `set` costs `O(log K)` per insert and `O(K)` extra space for `K` triplets — and it's unnecessary, because a sorted array lets us skip duplicates *in place*.

### Attempt 3 — sort + two pointers + in-place dedup (final, `solution2.cpp`)

Same core, but drop the `set`. Because the array is sorted, duplicates are always *adjacent*, so we dedup by skipping equal neighbours:

- **Fixed element:** `if (i > 0 && nums[i] == nums[i-1]) continue;` — never start a triplet with a value we already used as the anchor.
- **After recording a pair:** advance `l`/`r` past any run of equal values so the next pair is genuinely different.

No `set`, no post-processing copy. `O(1)` auxiliary space beyond the sort and the output.

```cpp
sort(nums.begin(), nums.end());
vector<vector<int>> triplets;
for (int i = 0; i + 2 < (int)nums.size(); ++i) {
    if (i > 0 && nums[i] == nums[i-1]) continue;          // skip duplicate anchor
    int target = -nums[i];
    int l = i + 1, r = (int)nums.size() - 1;
    while (l < r) {
        int sum = nums[l] + nums[r];
        if (sum == target) {
            triplets.push_back({nums[i], nums[l], nums[r]});
            ++l; --r;
            while (l < r && nums[l] == nums[l-1]) ++l;      // skip dup left
            while (l < r && nums[r] == nums[r+1]) --r;      // skip dup right
        } else if (sum > target) {
            --r;
        } else {
            ++l;
        }
    }
}
return triplets;
```

> **One fix vs. what I wrote:** my skip-loops were `while (nums[l] == nums[l-1] && l < r)` — the array read comes *before* the `l < r` guard. It happens to be safe here (I checked the bounds), but the habit that keeps you safe when it *isn't* obvious is **bounds-check first**: `while (l < r && nums[l] == nums[l-1])`. Same skip-loop shape as Valid Palindrome. Make the guard short-circuit before the access, always.

---

## Optimizations to revisit

- **Early break on positives:** once `nums[i] > 0`, every later element is `>= nums[i] > 0` (sorted), so no triplet from here on can sum to zero. `if (nums[i] > 0) break;` prunes a lot. Classic interviewer-pleaser.
- **`i + 2 < n` bound:** correctly stops the anchor at `n-3` (needs two elements after it). Tighter than `i < n-1`, and — bonus — no `size() - 1` subtraction, so no unsigned-underflow trap (cf. [signed vs. unsigned pitfalls](../../../../notes/cpp/signed-unsigned-pitfalls.md)).
- **Dead code:** the commented hashmap attempt at the top of both files should be deleted for an interview submission. It lives on here in the README instead, which is where the "why" belongs.

Full pattern reference: [Two Pointers — the two variants](../../../../notes/dsa-patterns/two-pointer-variants.md)

---

## Takeaways

- Sorting an array is a powerful pre-processing step for problems involving combinations, order, or duplicate handling.
- The 'N-Sum' problem (e.g., 3Sum, 4Sum) can often be solved by reducing it to an (N-1)-Sum problem by fixing one element and applying iteration or recursion.
- The Two Pointers technique is highly effective for finding pairs with a target sum in a sorted array and for skipping duplicate elements.
- Careful duplicate handling is essential at all levels (for the fixed element and the two-pointer elements) to ensure the solution set contains only unique triplets.

## C++ Concepts

- **`set<vector<int>>`** — a `std::set` of vectors works because `vector` has a built-in lexicographic `operator<`, so the set can order and dedupe whole triplets. Convenient, but `O(log K)` per insert + `O(K)` memory — the thing attempt 3 removes.
- **Sorted-array dedup = skip equal neighbours** — after `sort`, duplicates are adjacent, so `while (l < r && nums[l] == nums[l-1]) ++l;` collapses a run of equal values. This is the in-place alternative to a `set`.
- **Short-circuit evaluation ordering** — in `A && B`, `A` is evaluated first. Put the bounds guard as `A` so a failed guard prevents the array access in `B`: `l < r && nums[l] == ...`, never the reverse.
- **`sort(v.begin(), v.end())`** — `O(N log N)` introsort from `<algorithm>`. The `O(log N)` recursion stack is the real auxiliary-space cost of the "O(1) space" solution.
- **Brace-init in `push_back({a, b, c})`** — constructs the inner `vector<int>` in place from an initializer list, no named temporary.
- **`i + 2 < (int)nums.size()`** — cast `size()` (unsigned) so the comparison is signed-vs-signed; avoids the mixed-sign warning and keeps intent obvious.
