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
- **The key observation to state out loud:** a permutation of `s1` is exactly a length-`|s1|` substring whose character frequencies match `s1`'s. Order is irrelevant — only counts. Naming the *technique* ("fixed sliding window") without naming this *reduction* reads as pattern-matching from memory.

## Structure note — the pre-fill loop is avoidable

My version primes the first `len-1` characters in a separate loop, then expands/evicts in the main one. Skeleton #2 folds that away into a single loop:

```cpp
for (int r = 0; r < n; ++r) {
    freq2[s2[r] - 'a']++;                       // expand
    if (r >= m) freq2[s2[r - m] - 'a']--;       // evict the one that fell out
    if (r >= m - 1 && equal(freq1, freq1 + 26, freq2)) return true;   // record
}
```

The `if (r >= m)` guard does the priming implicitly. One loop, no duplicated bookkeeping. See [loop skeletons](../../../../notes/dsa-patterns/loop-skeletons.md) #2.

**Follow-up optimization:** the 26-element compare per position is `O(26n)` — technically `O(n)`, but if asked to drop the constant, maintain a `matched` counter of how many of the 26 buckets currently agree, updated incrementally on each add/evict. Validity becomes `matched == 26`, an `O(1)` check.

## C++ Concepts

- **`std::equal(first1, last1, first2)`** — from `<algorithm>`, compares two ranges elementwise. `equal(freq1, freq1+26, freq2)` is clearer and faster than a hand-rolled 26-iteration loop that doesn't `break` early.
- **`int freq[26] = {}`** — the `= {}` value-initializes *all* elements to zero. Without it the array holds garbage; this is a common and silent bug source.
- **Range-for by reference** — `for (char& ch : s1)` avoids a copy per character. Use `const char&` (or just `char`) when not mutating; `char` by value is fine for a 1-byte type.
- **`ch - 'a'` offset indexing** — maps `'a'..'z'` to `0..25`. For *mixed* case, prefer `int freq[128]` indexed by the raw char — no offset arithmetic, no branching on case.
- **Signed/unsigned comparison** — `i + len <= s2.size()` compares `int` against `size_t`, promoting the left side to unsigned. Cast explicitly: `(int)s2.size()`. See [signed vs. unsigned pitfalls](../../../../notes/cpp/signed-unsigned-pitfalls.md).
