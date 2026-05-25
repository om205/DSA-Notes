# Product of Array Except Self

- Difficulty: Medium
- Topic: Array, Prefix Sum, Suffix Sum
- Platform: LeetCode
- Link: https://leetcode.com/problems/product-of-array-except-self

---

## Problem Statement

Given an integer array `nums`, you need to return an array `answer` where `answer[i]` is the product of all elements of `nums` except `nums[i]`. This problem must be solved in `O(n)` time without using the division operation. An additional challenge is to achieve this with `O(1)` extra space complexity, excluding the output array.

---

## Examples

### Example 1

```txt
Input: nums = [1,2,3,4]

Output: [24,12,8,6]
```

Explanation: answer[0] = 2*3*4 = 24, answer[1] = 1*3*4 = 12, answer[2] = 1*2*4 = 8, answer[3] = 1*2*3 = 6.

### Example 2

```txt
Input: nums = [-1,1,0,-3,3]

Output: [0,0,9,0,0]
```

Explanation: For example, answer[2] = -1 * 1 * -3 * 3 = 9. Other elements become 0 due to the presence of 0 in nums.

---

## Constraints

- `2 <= nums.length <= 10^5`
- `-30 <= nums[i] <= 30`
- `The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.`
- `The product of all the elements of nums except nums[i] will fit in a 32-bit integer.`
---

## Intuition

We will use prefix product and postfix product in place respecting O(1) space constraint.

---


---

## Takeaways

- If we consider division then an edge case comes up of division by zero. This approach eliminates it.

## C++ Concepts

- 
