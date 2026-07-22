# Two Sum II - Input Array Is Sorted

- Difficulty: Medium
- Topic: Array, Two Pointers, Binary Search
- Platform: LeetCode
- Link: https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/description/

---

## Problem Statement

Given a 1-indexed array of integers `numbers` that is already *sorted in non-decreasing order*, find two numbers such that they add up to a specific `target` number. Return the indices of the two numbers, `index1` and `index2`, *added by one* as an integer array `[index1, index2]` of length 2, where `1 <= index1 < index2 <= numbers.length`. The tests are generated such that there is exactly one solution, and you may not use the same element twice. Your solution must use only constant extra space.

---

## Examples

### Example 1

```txt
Input: numbers = [2,7,11,15], target = 9

Output: [1,2]
```

Explanation: 2 and 7 add up to 9. Therefore, index1 = 1, index2 = 2. We return [1, 2].

### Example 2

```txt
Input: numbers = [2,3,4], target = 6

Output: [2,3]
```

Explanation: 2 and 4 add up to 6. Therefore, index1 = 2, index2 = 3. We return [2, 3].

### Example 3

```txt
Input: numbers = [-1,0], target = -1

Output: [1,2]
```

Explanation: -1 and 0 add up to -1. Therefore, index1 = 1, index2 = 2. We return [1, 2].

---

## Constraints

- `2 <= numbers.length <= 3 * 10^4`
- `-1000 <= numbers[i] <= 1000`
- `numbers is sorted in non-decreasing order.`
- `-1000 <= target <= 1000`
- `The tests are generated such that there is exactly one solution.`
---

## Intuition

Since the input array is sorted, we can efficiently find the pair using a two-pointer approach. Initialize a left pointer at the beginning and a right pointer at the end of the array. Calculate their sum. If the sum equals the target, we've found our pair. If the sum is too small, increment the left pointer to increase the sum. If the sum is too large, decrement the right pointer to decrease the sum. This method converges to the solution in linear time, leveraging the sorted property to avoid a brute-force O(n^2) search or a hash map's O(n) space.

---

## Why Discarding a Pointer Is Safe

The part that is genuinely non-obvious. When `sum > target`, we do `r--`. Why is that not throwing away a possible answer?

Because `arr[l]` is the **smallest live element**. For every `i` in `[l, r-1]`, sortedness gives `arr[i] >= arr[l]`, so:

```txt
arr[i] + arr[r] >= arr[l] + arr[r] > target
```

So `arr[r]` overshoots against **every remaining partner**, not just the current `l`. It is not "this pair failed" — it is "this element is dead."

**The objection worth answering:** *"If I drop `r` now and later advance `l`, wouldn't that new `l` have needed the `r` I discarded?"* No — the proof above was quantified over the **whole remaining window** `[l, r-1]`, and `l` only ever increases inside that window. Every future `l` was already covered when `r` was dropped. The elimination is permanent, which is exactly why the algorithm never backtracks.

Mirror image when `sum < target`: `arr[l]` is too small to reach the target even against the largest live partner `arr[r]`, so `arr[l]` is dead against everything in `[l+1, r]`. Advance `l`.

Each move deletes an entire row/column of the O(n²) pair grid → O(n) total.

Full pattern write-up: [Two Pointers — the two variants](../../../../notes/dsa-patterns/two-pointer-variants.md)

---

## Takeaways

- Leverage sorted input: When an array is sorted, consider two-pointer techniques or binary search for efficient solutions.
- Two-pointer pattern: Effective for finding pairs or sub-arrays that satisfy a condition in sorted data structures.
- Space optimization: The two-pointer approach often provides an O(1) space complexity solution by avoiding auxiliary data structures.
- Index handling: Always pay attention to whether the problem expects 0-indexed or 1-indexed results, and adjust accordingly.
- **Convert at the boundary, not in the hot loop.** Keeping pointers 0-indexed and doing `{l+1, r+1}` once at the return beats 1-indexed pointers that pay `-1` on every array read.
- Elimination arguments in two-pointer proofs are quantified over the *entire remaining window*, not just the current pair — that is what makes them backtrack-free.

## C++ Concepts

- **`vector<int>` brace-return** — `return {l + 1, r + 1};` constructs the vector in place via `std::initializer_list`. No named temporary needed.
- **`return {};`** — value-initializes an empty `vector<int>`. Useful as a defensive "not found" return even when the problem guarantees a solution.
- **`numbers.size()` returns `size_t` (unsigned)** — safe here because there is no `- 1`, but `int r = numbers.size() - 1;` would be the classic underflow trap. See [signed vs. unsigned pitfalls](../../../../notes/cpp/signed-unsigned-pitfalls.md).
- **Declare at first use** — `int sum = numbers[l] + numbers[r];` inside the loop, not `int sum;` hoisted above it. Narrowest scope, no uninitialized window.
- **Pass by reference** — `vector<int>& numbers` avoids an O(n) copy of the input on every call.
