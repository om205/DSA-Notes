# Longest Consecutive Sequence

- Difficulty: Medium
- Topic: Array, Hash Table
- Platform: LeetCode
- Link: https://leetcode.com/problems/longest-consecutive-sequence

---

## Problem Statement

Given an unsorted array of integers `nums`, return the length of the longest consecutive elements sequence. You must write an algorithm that runs in O(n) time.

---

## Examples

### Example 1

```txt
Input: nums = [100,4,200,1,3,2]

Output: 4
```

Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.

### Example 2

```txt
Input: nums = [0,3,7,2,5,8,4,6,0,1]

Output: 9
```

Explanation: The longest consecutive elements sequence is [0, 1, 2, 3, 4, 5, 6, 7, 8]. Therefore its length is 9.

---

## Constraints

- `0 <= nums.length <= 10^5`
- `-10^9 <= nums[i] <= 10^9`
---

## Intuition

The most efficient way to check for the presence of an element in an unsorted array is to store all elements in a hash set (or a dictionary/hash map). By doing so, we can achieve O(1) average time lookups. To find the longest consecutive sequence in O(n) time, we iterate through each number in the input array. For each number, we check if it is the *start* of a sequence (i.e., if `num - 1` is not present in our hash set). If it is the start, we then count upwards, checking `num + 1`, `num + 2`, and so on, updating the maximum length found so far.

---

## Takeaways

- Using a hash set allows for O(1) average time complexity for checking element existence, which is crucial for achieving an O(n) solution.
- To optimize, only initiate sequence counting from potential 'start' elements (numbers `x` for which `x-1` is not present in the set). This ensures each number is part of an extension check at most once, preventing redundant computations.
- The problem leverages the benefits of hash-based data structures to transform a potentially O(N log N) (with sorting) or O(N^2) (naive check) problem into an efficient O(N) solution.

## C++ Concepts

There are three more solutions using hash map that we can remember:
- Using hashmap and updating boundary nodes. 
- Top down DB - memorization approach
- Union find
