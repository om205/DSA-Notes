# Longest Repeating Character Replacement

- Difficulty: Medium
- Topic: String, Sliding Window, Hash Map
- Platform: LeetCode
- Link: https://leetcode.com/problems/longest-repeating-character-replacement/

---

## Problem Statement

You are given a string `s` and an integer `k`. You can choose any character in the string and change it to any other uppercase English character any number of times. You can perform this operation at most `k` times. Return the length of the longest substring containing the same letter you can get after performing the above operations.

---

## Examples

### Example 1

```txt
Input: s = "ABAB", k = 2

Output: 4
```

Explanation: Replace the two 'A's with two 'B's (or vice versa). The original string is "ABAB". With k=2, we can change 'A's to 'B's to get "BBBB" or 'B's to 'A's to get "AAAA". The longest substring of the same letter is 4.

### Example 2

```txt
Input: s = "AABABBA", k = 1

Output: 4
```

Explanation: Replace the one 'A' in the middle (at index 3) with 'B' and form "AABBBBA". The longest substring of the same letter (all 'B's from index 2 to 5) is 4.

---

## Constraints

- `1 <= s.length <= 10^5`
- ``s` consists of only uppercase English letters.`
- `0 <= k <= s.length`
---

## Intuition

The problem asks for the longest substring where, after at most `k` replacements, all characters are the same. This can be efficiently solved using a sliding window approach. We maintain a window and character frequencies within it. The key idea is that for any valid window, the number of characters that are *not* the most frequent character in that window must be less than or equal to `k`. If this condition (`window_length - max_frequency_in_window <= k`) is violated, we shrink the window from the left until it becomes valid again, while continuously tracking the maximum valid window length encountered.

---

## Takeaways

- Sliding window is a powerful technique for substring problems involving a constraint on modifications.
- The condition `window_length - max_frequency_in_window <= k` is central to this problem. It effectively checks if we have enough `k` operations to convert all non-most-frequent characters to the most frequent one within the current window.
- For a fixed alphabet size (like uppercase English letters), a frequency array (e.g., size 26) provides O(1) lookups and updates for character counts within the window.
- The `max_frequency_in_window` only needs to be updated (potentially increased) when expanding the window. When shrinking, it doesn't necessarily need to be recomputed for the entire window from scratch, as the goal is just to satisfy the condition, and a smaller `max_frequency` might still allow the window to be valid.

## C++ Concepts

-
