# Minimum Window Substring

- Difficulty: Hard
- Topic: Hash Table, String, Sliding Window
- Platform: LeetCode
- Link: https://leetcode.com/problems/minimum-window-substring/description/

---

## Problem Statement

Given two strings `s` and `t` of lengths `m` and `n` respectively, find the minimum window substring of `s` such that every character in `t` (including duplicates) is present in the window. If no such substring exists, return an empty string `""`. The test cases will be generated such that the answer is unique.

---

## Examples

### Example 1

```txt
Input: s = "ADOBECODEBANC", t = "ABC"

Output: "BANC"
```

Explanation: "BANC" is the smallest substring of "ADOBECODEBANC" that contains all characters A, B, and C from "ABC".

### Example 2

```txt
Input: s = "a", t = "a"

Output: "a"
```

Explanation: The smallest window is the string itself.

### Example 3

```txt
Input: s = "a", t = "aa"

Output: ""
```

Explanation: No window can contain two 'a's from s="a".

---

## Constraints

- `m == s.length`
- `n == t.length`
- `1 <= m, n <= 10^5`
- `s and t consist of uppercase and lowercase English letters.`
---

## Intuition

The core idea is to use a sliding window approach with two pointers, `left` and `right`. We expand the window by moving the `right` pointer, keeping track of character counts within the current window using a hash map. Once the current window contains all characters of `t` (verified by comparing character counts and a 'formed' counter), we try to shrink the window from the `left` side, updating the minimum window found so far, until the window no longer contains all characters of `t`. This process repeats until the `right` pointer reaches the end of `s`.

---

## Takeaways

- The Sliding Window technique is highly effective for substring or subarray problems that involve finding a minimum/maximum valid segment.
- Using a frequency map (hash map) is crucial for efficiently tracking character counts of required characters (from `t`) and characters present in the current window.
- A counter to track how many unique characters from `t` have met their frequency requirement in the current window can optimize the condition check.
- The general strategy is: expand the window until the condition is met, then contract it from the left while maintaining the condition, updating the best result, until the condition is broken.

## C++ Concepts

-
