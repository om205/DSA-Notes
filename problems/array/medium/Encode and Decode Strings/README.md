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

Delimiter alone won't work because strings may contain delimiters. We need to store length#string so that we can easily extract the length using delimeter and using length extract string.

---


## Complexity

| Operation | Complexity |
|---|---|
| Encode | O(n) | 
| Decode | O(m+n) |

where n is length of arry and m is sum of length of strings.

---

## Takeaways

- Delimeter after length (number) is necessary. After string it is not.
- Useful pattern for serialization problems.

## C++ concepts

- char can be added to string using + operator. Thus conversion of char to int isn't straightforward since String(ch) will convert it's ascii value to string. We need to do either
    - `str = "" + ch;` -> add empty string to it
    - `str = {ch};` initialization from list of chars
    - str.push_back()
- `stoi` function is used to convert string to integer
- lambda functions in C++:
    ```C++
    auto my_lambda = [capture](parameters) -> return_type {
        // Function body
    };
    ```
    - [] (Empty): Captures nothing. The lambda behaves like a standard function.
    - [x]: Captures variable x by value (makes a read-only copy).
    - [&x]: Captures variable x by reference (allows you to modify the original variable).
    - [=]: Captures all local variables in scope by value.
    - [&]: Captures all local variables in scope by reference.[=, &x]: Captures everything by value, but x by reference.

    If something in capture list changes inside lambda, we use **mutable** keyword just after parenthesis / parameters.
    