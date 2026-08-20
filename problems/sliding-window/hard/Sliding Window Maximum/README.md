# Sliding Window Maximum

- Difficulty: Hard
- Topic: Array, Queue, Sliding Window, Monotonic Queue, Heap (Priority Queue)
- Platform: LeetCode
- Link: https://leetcode.com/problems/sliding-window-maximum

---

## Problem Statement

You are given an array of integers nums, and a sliding window of size k moving from the very left of the array to the very right. You can only see the k numbers in the window at any point, and the window moves right by one position each time. Return an array containing the maximum element for each sliding window position.

---

## Examples

### Example 1

```txt
Input: nums = [1,3,-1,-3,5,3,6,7], k = 3

Output: [3,3,5,5,6,7]
```

Explanation: Window position: [1 3 -1] max = 3; [3 -1 -3] max = 3; [-1 -3 5] max = 5; [-3 5 3] max = 5; [5 3 6] max = 6; [3 6 7] max = 7.

### Example 2

```txt
Input: nums = [1], k = 1

Output: [1]
```

Explanation: There is only one element in the array, so the maximum is 1.

---

## Constraints

- `1 <= nums.length <= 10^5`
- `-10^4 <= nums[i] <= 10^4`
- `1 <= k <= nums.length`
---

## Intuition

Maintain a double-ended queue (deque) storing indices of array elements in monotonically decreasing order of their values. For each new element, pop smaller elements from the back of the deque since they can no longer be the maximum, and pop elements from the front if they fall outside the current window size k. The element at the front of the deque will always be the maximum for the current sliding window.

---

## Takeaways

- A monotonic queue enables O(1) query time for the maximum or minimum element in a dynamic window.
- Storing indices in the deque allows efficient verification of whether elements have slipped out of the window.
- Each element is pushed and popped at most once, leading to an optimal linear O(n) runtime.

## C++ Concepts

-
