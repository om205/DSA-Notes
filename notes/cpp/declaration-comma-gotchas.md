# C++ Declaration & Comma-Operator Gotchas — Flashcards

- Topic: C++ language — declarations, the comma operator, statements vs expressions, macros
- Source: Trapping Rain Water solve (two compile errors under time pressure)
- Date: 2026-07-27
- Real example: `problems/two-pointers/hard/Trapping Rain Water/solution.cpp`

> **How to use:** Read the question, answer it OUT LOUD from memory, *then* expand the answer. These are the kind of errors that cost you 60 seconds and composure in a live interview — the goal is to never hit them again. Revisit weekly until reflexive.

---

## The comma operator

<details>
<summary><b>Q1.</b> Why does <code>if (cond) fast++, continue;</code> fail with "expected expression"?</summary>

The comma there is the **comma operator**, which sequences two *expressions* and yields the value of the second. `fast++` is an expression (fine), but `continue` is a **statement** — a control-flow jump with no value. A statement cannot be an operand of the comma operator, so the parser reports "expected expression" where `continue` appears.

**Fix — use a block (statement context):**
```cpp
if (cond) { fast++; continue; }
```
</details>

<details>
<summary><b>Q2.</b> Which keywords can NEVER appear after a comma operator, and what's the rule of thumb?</summary>

`continue`, `break`, `return`, `goto` — all **statements**, not expressions. Rule of thumb: **the moment you need a control-flow keyword, you need `{ }`.** The comma operator is only for chaining side-effecting expressions (`++i, ++j`), which is itself rare and usually better as two statements.
</details>

---

## One declaration, one type

<details>
<summary><b>Q3.</b> Why does <code>for (int i = 0, ll sum = 0; ...)</code> fail with "expected unqualified-id"?</summary>

A single declaration statement applies **one base type** to all its comma-separated declarators. After `int i = 0,` the compiler expects another *name* of type `int`, but instead sees `ll` — a type keyword (it expands to `long long int`). So it reads `int i = 0, long long int sum` and errors on the stray type ("expected unqualified-id" = "I wanted a variable name here").

**Fixes:**
```cpp
for (ll i = 0, sum = 0; i < len; ++i)   // both ll
// or declare sum before the loop if i must stay int
```
</details>

<details>
<summary><b>Q4.</b> How did the <code>#define ll long long int</code> macro make Q3 worse, and what's the better tool?</summary>

`#define` is **textual substitution** done by the preprocessor, so the error message points *inside the macro expansion* and reads cryptically ("expanded from macro 'll'"). A **type alias** is part of the language proper and scoped:
```cpp
using ll = long long;   // preferred
typedef long long ll;   // older equivalent
```
The alias gives clearer diagnostics and respects scope. (The one-type-per-declaration rule from Q3 still applies either way — the alias fixes the *messaging*, not the mixed-type mistake.)
</details>

---

## Self-check

- [ ] Explain in one sentence why `x++, continue` doesn't compile.
- [ ] Write a `for` loop with an `int` index and a `long long` accumulator, correctly.
- [ ] State one reason to prefer `using ll = long long;` over `#define ll long long`.

---

## Related

- [[signed-unsigned-pitfalls]] — the other family of "compiles-or-not depending on types" C++ traps.
