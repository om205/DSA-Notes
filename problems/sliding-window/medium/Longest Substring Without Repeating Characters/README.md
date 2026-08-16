# Longest Substring Without Repeating Characters

- Difficulty: Medium
- Topic: Hash Table, String, Sliding Window, Two Pointers
- Platform: LeetCode
- Link: https://leetcode.com/problems/longest-substring-without-repeating-characters/

---

## Problem Statement

Given a string `s`, find the length of the longest substring without repeating characters. A substring is a contiguous non-empty sequence of characters within a string. You need to return the maximum length found.

---

## Examples

### Example 1

```txt
Input: s = "abcabcbb"

Output: 3
```

Explanation: The answer is "abc", with the length of 3.

### Example 2

```txt
Input: s = "bbbbb"

Output: 1
```

Explanation: The answer is "b", with the length of 1.

### Example 3

```txt
Input: s = "pwwkew"

Output: 3
```

Explanation: The answer is "wke", with the length of 3. Note that "pwke" is a subsequence and not a substring.

---

## Constraints

- `0 <= s.length <= 5 * 10^4`
- `s consists of English letters, digits, symbols and spaces.`
---

## Intuition

The problem can be efficiently solved using a sliding window approach. We maintain a window `[left, right]` representing the current substring. We expand the window by moving the `right` pointer and adding characters to a set to track uniqueness. If a duplicate character is encountered, we shrink the window from the `left` by removing characters from the set until the duplicate is no longer present, ensuring the window always contains unique characters. At each step, we update the maximum length found.

---

## Takeaways

- The sliding window technique is effective for substring/subarray problems with a 'contiguous' constraint.
- A hash set (or frequency map) is crucial for efficiently checking character existence and managing duplicates within the window.
- The two-pointer approach (left and right) allows for dynamic expansion and contraction of the window.
- This problem is a foundational example for understanding and applying the sliding window pattern.

## C++ Concepts

-
