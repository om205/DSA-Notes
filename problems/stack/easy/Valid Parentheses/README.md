# Valid Parentheses

- Difficulty: Easy
- Topic: String, Stack
- Platform: LeetCode
- Link: https://leetcode.com/problems/valid-parentheses/

---

## Problem Statement

Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid. An input string is valid if open brackets are closed by the same type of brackets, open brackets are closed in the correct order, and every close bracket has a corresponding open bracket of the same type.

---

## Examples

### Example 1

```txt
Input: s = "()"

Output: true
```

Explanation: The opening parenthesis is properly closed by its matching closing parenthesis.

### Example 2

```txt
Input: s = "()[]{}"

Output: true
```

Explanation: All opening brackets are closed by their corresponding closing brackets in the correct order.

### Example 3

```txt
Input: s = "(]"

Output: false
```

Explanation: The closing bracket ']' does not match the open bracket '('.

---

## Constraints

- `1 <= s.length <= 10^4`
- `s consists of parentheses only '()[]{}'.`
---

## Intuition

Use a stack to track opening brackets as you traverse the string from left to right. When a closing bracket is encountered, verify if it matches the most recently opened bracket on top of the stack. If it matches, pop the open bracket from the stack; if it doesn't match or the stack is empty, the sequence is invalid. Finally, the string is valid if the stack is completely empty after processing all characters.

---

## Takeaways

- Stacks are the canonical data structure for problems involving nested or balanced structures due to their Last-In, First-Out (LIFO) property.
- Using a hash map to map closing brackets to their corresponding opening brackets simplifies character comparison logic.
- Don't forget edge cases like odd string lengths, starting with closing brackets, or unclosed opening brackets remaining in the stack at the end.
- **Three near-identical clauses is a bug farm.** Copy-paste-modify hides typos because the eye reads intent, not text. Collapse repetition into a lookup table and the bug class disappears.

## Bugs found on first attempt

Both were caught by the two most obvious inputs for their branches — a 60-second pre-submit trace would have found them.

### 1. `st.top()` called before the `st.empty()` guard — undefined behaviour

```cpp
char top_ch = st.top();                  // ← runs even when the stack is empty
if (st.empty() || ...) return false;     // ← guard arrives one line too late
```

Input `")"` calls `.top()` on an empty stack. That is UB, not a wrong answer. **The guard must short-circuit the access, not follow it** — same class as the skip-loop bounds ordering in [3Sum](../../../two-pointers/medium/3Sum/README.md).

### 2. `==` where `!=` was meant

```cpp
(ch == ')' && top_ch != '(')     // ok
(ch == '}' && top_ch != '{')     // ok
(ch == ']' && top_ch == '[')     // BUG - inverted
```

Broke in both directions: `"[]"` returned `false` (valid rejected) and `"(]"` returned `true` (invalid accepted).

### The structural fix

The table-driven form has one condition instead of three, so there is nothing to typo:

```cpp
bool isValid(string s) {
    stack<char> st;
    unordered_map<char,char> match = {{')','('}, {'}','{'}, {']','['}};
    for (char ch : s) {
        if (!match.count(ch)) { st.push(ch); continue; }     // opener
        if (st.empty() || st.top() != match[ch]) return false;
        st.pop();
    }
    return st.empty();
}
```

## C++ Concepts

- **`std::stack::top()` on an empty stack is undefined behaviour** — it does *not* throw. `.empty()` must be checked first, and `&&` short-circuits left-to-right, so ordering the operands correctly is the entire safety mechanism.
- **Short-circuit evaluation as a guard** — in `A && B`, `B` is evaluated only if `A` is true. Put the safety check in `A`. This one habit prevents a whole family of out-of-bounds bugs.
- **`unordered_map` brace initialization** — `unordered_map<char,char> m = {{')','('}, ...}` builds the table inline via `std::initializer_list`. Declare it `static const` to avoid rebuilding it on every call.
- **`.count()` vs `operator[]` for membership** — `.count(ch)` is a read-only test; `m[ch]` would *insert* a default entry on a miss. Reach for `.count()` / `.contains()` (C++20) / `.find()` when only testing presence.
- **`continue` is a statement, not an expression** — it cannot follow the comma operator. See [declaration & comma gotchas](../../../../notes/cpp/declaration-comma-gotchas.md).
