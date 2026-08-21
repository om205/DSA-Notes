# Evaluate Reverse Polish Notation

- Difficulty: Medium
- Topic: Array, Math, Stack
- Platform: LeetCode
- Link: https://leetcode.com/problems/evaluate-reverse-polish-notation/

---

## Problem Statement

You are given an array of strings tokens that represents an arithmetic expression in a Reverse Polish Notation. Evaluate the expression and return an integer that represents the value of the expression. Note that valid operators are '+', '-', '*', and '/', division truncates toward zero, and the given expression is guaranteed to be valid.

---

## Examples

### Example 1

```txt
Input: tokens = ["2","1","+","3","*"]

Output: 9
```

Explanation: ((2 + 1) * 3) = 9

### Example 2

```txt
Input: tokens = ["4","13","5","/","+"]

Output: 6
```

Explanation: (4 + (13 / 5)) = 4 + 2 = 6

### Example 3

```txt
Input: tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]

Output: 22
```

Explanation: ((10 * (6 / ((9 + 3) * -11))) + 17) + 5 = 22

---

## Constraints

- `1 <= tokens.length <= 10^4`
- `tokens[i] is either an operator: '+', '-', '*', or '/', or an integer in the range [-200, 200]`
---

## Intuition

In Reverse Polish Notation, operators follow their operands. Iterate through the tokens: if a token is a number, push it onto a stack; if it is an operator, pop the top two numbers from the stack, perform the operation, and push the result back. The final remaining item in the stack is the calculated result.

---

## Takeaways

- A stack is the natural data structure for postfix notation evaluation as operators act on the most recently parsed operands.
- Order of operands matters for non-commutative operations like subtraction and division; the first popped element is the second (right) operand.
- Be cautious with integer division truncating toward zero depending on the language (e.g., Python's // truncates towards negative infinity, so int(a / b) should be used instead).
- **This did not need a tutorial.** I expected to have to study postfix theory first and instead derived it cold. Evidence for the just-in-time-theory rule: *"can I derive this in 25 minutes?"* — for RPN evaluation the answer is yes, so studying first would have been wasted time.
- **The trigger:** *"evaluate an expression where operators follow their operands"* → stack. Operators consume the most recently produced values, which is LIFO by definition.

## The two places this problem is usually failed

**1. Operand order.** `"a b op"` means `a op b`. Since `a` is pushed first, popping yields `b` **first**:

```cpp
int b = operands.top(); operands.pop();   // right operand
int a = operands.top(); operands.pop();   // left operand
operands.push(a - b);                     // NOT b - a
```

Commutative operators (`+`, `*`) hide the bug; `-` and `/` expose it. Got this right first time.

**2. Telling an operand from an operator.** The test used here:

```cpp
if (str.size() > 1 || (ch >= '0' && ch <= '9'))   // it's a number
```

It works because **every operator is exactly one character**, so any token of length ≥ 2 must be a number — which is what catches negatives like `"-11"`. A single-character token is a number only if it is a digit, so a lone `"-"` is correctly read as an operator. Compact and correct.

## Improvements

- **Parenthesise `&&` inside `||`.** `str.size() > 1 || ch <= '9' && ch >= '0'` is correct by precedence (`&&` binds tighter), but it relies on the reader knowing that, and GCC/Clang emit `-Wparentheses` here. Write the parentheses.
- **Use `switch`, not four sequential `if`s.** After `'+'` matches, the current code still tests `'-'`, `'*'`, `'/'`. A `switch` expresses the mutual exclusivity and stops early. This is also the same **repetition-as-bug-farm** shape that hid the inverted `==` in [Valid Parentheses](../../easy/Valid%20Parentheses/README.md) — no bug here, but the same structure.
- **Range-for by value.** `for (string& str : tokens)` takes a mutable reference without mutating. Prefer `const string&` — it documents intent and permits const inputs.

## C++ Concepts

- **`std::stoi`** — parses a leading integer from a `string`, handling an optional sign, so `"-11"` works with no special case. Throws `std::invalid_argument` on no conversion and `std::out_of_range` on overflow. `atoi` is faster but reports no errors.
- **Integer division truncates toward zero — guaranteed since C++11.** `-7 / 2 == -3`, not `-4`. That matches this problem's spec exactly. Before C++11 the rounding direction was implementation-defined.
- **Operator precedence: `&&` binds tighter than `||`.** So `a || b && c` is `a || (b && c)`. Correct here, but write the parentheses — compilers warn precisely because this is a common misreading.
- **`std::string::operator[]` at index 0 on an empty string** returns the null character (defined behaviour since C++11), unlike `std::vector`, where the equivalent is UB. Still worth guarding when input isn't guaranteed non-empty.
- **`std::stack<int>::top()` on an empty stack is UB.** Two `top()`/`pop()` pairs run per operator with no arity check — safe only because the input is guaranteed to be a well-formed RPN expression. Worth saying out loud in an interview.
- **Overflow** — `a * b` is `int` arithmetic. Safe here only because the problem guarantees all intermediate values fit in a 32-bit integer. Flag the assumption rather than assuming it silently.
