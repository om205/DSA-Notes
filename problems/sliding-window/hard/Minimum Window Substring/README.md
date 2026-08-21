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
- **Minimize vs. maximize windows are mirror images.** Maximize = shrink while *invalid*, record after. Minimize = shrink while *valid*, record before each shrink. Same skeleton, inverted loop condition.
- **Terminology that must be exact:** the window must **cover** `t` — a **superset** relation (`window[c] >= need[c]` for every `c`). Not a "subset", and not a "substring of the frequency set". Wrong direction words derail the listener.

## Optimization — make the validity check O(1)

`isFreqSubset` scans all of `t`'s distinct characters on every call, and it is called once per expansion plus once per shrink — so `O(52n)`. That is still `O(n)`, and the amortization argument is correct: **each character is added once and removed at most once.**

To drop the constant, track two counters instead of rescanning:

```cpp
int need = freq2.size();   // distinct characters required
int have = 0;              // how many are currently satisfied
// on add(c):     if (++freq1[c] == freq2[c]) have++;
// on remove(c):  if (freq1[c]-- == freq2[c]) have--;
// window is valid  <=>  have == need
```

Same algorithm; validity collapses to one integer comparison.

## Bug avoided — record indices, not substrings

The first attempt built `s.substr(...)` on every improvement and hit **Memory Limit Exceeded** on a large test. Fix: store `win_l` / `win_r` and materialize the substring exactly once, at return. General rule — **inside a hot loop, record a reference to the answer, never a copy of it.**

## C++ Concepts

- **`unordered_map::operator[]` INSERTS on a missing key.** `m2[it.first]` inside `isFreqSubset` silently adds zero-valued entries — a *mutating read*. Use `.find()` / `.count()`, or take the parameter as `const&` and watch it stop compiling. Same class of bug as `exists[s[r]]` in Longest Substring.
- **`std::string::substr(pos, len)`** — the second argument is a **length**, not an end index. Hence `s.substr(win_l, win_r - win_l + 1)`.
- **`unordered_map` vs a flat array** — the map was chosen to handle mixed case, but `int freq[128]` indexed by the raw char handles that with no offset arithmetic *and* no hashing. Prefer the array whenever the key domain is small and dense.
- **Sentinel initialization** — `win_l = -1` marks "no window found yet". A cleaner alternative avoiding the two-variable sentinel: `int bestLen = INT_MAX` plus `bestL`, then test `bestLen == INT_MAX` at return.
- **Signed/unsigned comparison** — `r < s.size()` mixes `int` and `size_t`. See [signed vs. unsigned pitfalls](../../../../notes/cpp/signed-unsigned-pitfalls.md).
