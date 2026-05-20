# Encode and Decode Strings

- Difficulty: Medium
- Topic: Array, String
- Platform: LeetCode
- Link: https://leetcode.com/problems/encode-and-decode-strings/

---

## Problem Statement

Design an algorithm to encode a list of strings to a string...

---

## Examples

### Example 1

Input:
```txt
["lint","code","love","you"]
```

Output:
```txt
"4#lint4#code4#love3#you"
```


---

### Example 2

Input:
```txt
["we","say",":","yes"]
```

Output:
```txt
"2#we3#say1#:3#yes"
```

---

## Constraints

- `1 <= strs.length <= 200`
- `0 <= strs[i].length <= 200`
- Strings may contain any valid ASCII character.

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