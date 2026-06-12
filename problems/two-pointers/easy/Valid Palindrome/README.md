# Valid Palindrome

- Difficulty: Easy
- Topic: String, Two Pointers
- Platform: LeetCode
- Link: https://leetcode.com/problems/valid-palindrome/description/

---

## Problem Statement

A phrase is a palindrome if, after converting all uppercase letters into lowercase letters and removing all non-alphanumeric characters, it reads the same forward and backward. Given a string s, return true if it is a palindrome, and false otherwise.

---

## Examples

### Example 1

```txt
Input: s = "A man, a plan, a canal: Panama"

Output: true
```

Explanation: "amanaplanacanalpanama" is a palindrome.

### Example 2

```txt
Input: s = "race a car"

Output: false
```

Explanation: "raceacar" is not a palindrome.

### Example 3

```txt
Input: s = " "

Output: true
```

Explanation: s is an empty string "" after removing non-alphanumeric characters. An empty string is a palindrome.

---

## Constraints

- `s consists only of printable ASCII characters.`
---

## Intuition

The core idea is to use a two-pointer approach to check for palindromic properties while ignoring non-alphanumeric characters and case. Initialize one pointer at the beginning of the string and another at the end. Iterate inward, advancing each pointer until it points to an alphanumeric character. Once both pointers are at valid characters, convert them to lowercase and compare. If they don't match, the string is not a palindrome. If they match, continue moving the pointers until they cross each other. If all comparisons pass, the string is a palindrome.

---

## Takeaways

- The two-pointer technique is highly efficient for problems requiring symmetrical comparisons in strings or arrays.
- Preprocessing steps like filtering non-alphanumeric characters and normalizing case are crucial for string problems with specific comparison rules.
- Careful handling of edge cases, such as empty strings or strings containing only non-alphanumeric characters, is necessary for robust solutions.
- Utilize built-in character functions (e.g., `isalnum`, `lower`) to simplify character validation and transformation.

## C++ Concepts

-
