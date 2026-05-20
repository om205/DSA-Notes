# Encode and Decode Strings

- Difficulty: Medium
- Topic: Array, String
- Platform: NeetCode
- Link: https://neetcode.io/problems/string-encode-and-decode/question

---

## Problem Statement

Design an algorithm to encode a list of strings to a string. The encoded string is then sent over the network and is decoded back to the original list of strings.
decoded_strs in Machine 2 should be the same as the input strs in Machine 1.
Implement the encode and decode methods.

---

## Examples

### Example 1

Input:
```txt
strs = ["Hello","World"]
```

Output:
```txt
["Hello","World"]
```

---

## Constraints

- `0 <= strs.length < 100`
- `0 <= strs[i].length < 200`
- strs[i] contains any possible characters out of 256 valid ASCII characters.

---

## Intuition

We need a reversible encoding scheme.
Delimiter alone won't work because strings may contain delimiters.

---

## Approach

Store:
- length of string
- separator
- actual string

Example:
```txt
4#lint
```

---

## Complexity

| Operation | Complexity |
|---|---|
| Encode | O(n) |
| Decode | O(n) |

---

## Takeaways

- Always think about delimiter collision.
- Prefix-length encoding is safer.
- Useful pattern for serialization problems.