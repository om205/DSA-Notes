# Permutation in String

- Difficulty: Medium
- Topic: Hash Table, String, Sliding Window
- Platform: LeetCode
- Link: https://leetcode.com/problems/permutation-in-string

---

## Problem Statement

Given two strings s1 and s2, return true if s2 contains a permutation of s1, or false otherwise. In other words, the problem asks us to determine if any of s1's permutations is a substring of s2.

---

## Examples

### Example 1

```txt
Input: s1 = "ab", s2 = "eidbaooo"

Output: true
```

Explanation: s2 contains one permutation of s1 ("ba").

### Example 2

```txt
Input: s1 = "ab", s2 = "eidboaoo"

Output: false
```

Explanation: s2 does not contain any permutation of s1.

---

## Constraints

- `1 <= s1.length, s2.length <= 10^4`
- `s1 and s2 consist of lowercase English letters.`
---

## Intuition

The core idea is to efficiently check if any substring of s2, with a length equal to s1, has the same character frequency counts as s1. Since we are looking for a substring of a fixed length (length of s1), a sliding window approach is highly suitable. We can maintain frequency counts for s1 and a dynamic frequency count for the current window in s2, then slide this window across s2, updating character counts at the window's edges and comparing the frequency maps to determine if a permutation is found.

---

## Takeaways

- Sliding Window is excellent for substring problems with a fixed target length or properties that can be maintained efficiently by adding/removing characters from window ends.
- Frequency arrays/maps are crucial for checking permutations or anagrams, especially with a limited character set.
- To optimize, instead of comparing two full frequency maps, maintain a 'match count' or a difference array to track how many characters' frequencies currently match between the window and the target string.
- For small, fixed alphabets (like lowercase English letters), an array of size 26 is more efficient than a hash map for frequency counting due to direct indexing.

## C++ Concepts

-
