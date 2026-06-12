# Signed vs. Unsigned Pitfalls in C++ — Flashcards

- Topic: C++ language — integer types, implicit conversions, STL `size()`
- Source: Valid Palindrome solve (mentor review)
- Date: 2026-06-09
- Real example: `problems/two-pointers/easy/Valid Palindrome/solution.cpp` — `int bk = s.size() - 1;`

> **How to use:** Read the question, answer it OUT LOUD from memory, *then* expand the answer. Don't peek first — the retrieval is what builds the memory. Revisit weekly.

---

## The core trap

<details>
<summary><b>Q1.</b> What is the type returned by <code>vector::size()</code>, <code>string::size()</code>, and most STL containers' <code>size()</code>?</summary>

`size_t` — an **unsigned** integer type (usually 64-bit on modern systems). It cannot represent negative values.
</details>

<details>
<summary><b>Q2.</b> What happens when you compute <code>s.size() - 1</code> on an empty string?</summary>

`0 - 1` evaluated in unsigned arithmetic **wraps around** to `SIZE_MAX` (e.g. `18446744073709551615` on a 64-bit system). It does NOT become `-1`. Unsigned types have no negatives — they wrap.
</details>

<details>
<summary><b>Q3.</b> In <code>int bk = s.size() - 1;</code> with empty <code>s</code>, what value does <code>bk</code> end up with?</summary>

The subtraction happens FIRST in unsigned space (→ `SIZE_MAX`), THEN it's narrowed to `int`. The narrowing is **implementation-defined** in pre-C++20 and **implementation-defined-but-consistent** in C++20+. In practice on x86 it lands on `-1` because of two's-complement bit-pattern reuse — but you can't *rely* on that. It's a latent bug masquerading as working code.
</details>

---

## Fixes

<details>
<summary><b>Q4.</b> What are three safe ways to write the "last valid index" of a string/vector?</summary>

1. **Cast to signed first:** `int bk = (int)s.size() - 1;` — subtraction now in signed space.
2. **Guard with `empty()`:** `if (s.empty()) return ...; int bk = s.size() - 1;` — never reach the bad case.
3. **Use signed throughout:** `ssize_t bk = (ssize_t)s.size() - 1;` — or simply `int n = s.size(); int bk = n - 1;` (split the conversion from the arithmetic).
</details>

<details>
<summary><b>Q5.</b> Why is <code>for (int i = 0; i &lt; v.size(); ++i)</code> a (mild) bug?</summary>

`int` (signed) compared to `size_t` (unsigned) triggers an implicit conversion of `i` to unsigned for the comparison. With a normal `i >= 0` this is fine, but it generates a compiler warning, and it's a *symptom* of mixing the types — the same code with `--i` somewhere would underflow without warning. Either use `size_t i` or cast: `i < (int)v.size()`.
</details>

---

## The deeper rule

<details>
<summary><b>Q6.</b> What's the one-line rule that prevents all of these bugs?</summary>

**Never subtract from an unsigned value unless you've proven it's >= the amount you're subtracting.** Either guard, or convert to signed *before* the arithmetic. The unsigned domain has no "below zero" — it has wrap, and wrap is silent.
</details>

<details>
<summary><b>Q7.</b> Why does this matter specifically in DSA / two-pointer / sliding-window code?</summary>

Right-pointer initialization (`r = n - 1`), backward loops (`for (int i = n-1; i >= 0; --i)`), window shrink (`r - l - 1`), and "previous index" computations all do subtractions from `size()` or indices derived from it. One empty edge case + one unsigned wrap = your loop runs 2^64 times or your index reads garbage memory. Most LeetCode problems guarantee non-empty input, so the bug **hides** — until production code or a different problem exposes it.
</details>

<details>
<summary><b>Q8.</b> What's the habit to build?</summary>

When you see `.size()` in arithmetic, *pause and ask:* "Could the result of this expression be negative if the container is small?" If yes — cast to `int` (or use `(int)v.size()`) **at the point of the arithmetic**, not after. The cast is free; the bug is expensive.
</details>

---

## Self-check

After a week, can you:

- [ ] Explain why `s.size() - 1` is dangerous in under 30 seconds?
- [ ] Spot the bug in someone else's code review?
- [ ] Write `int n = s.size(); int r = n - 1;` reflexively instead of `int r = s.size() - 1;`?

If yes — promote this card to monthly review. If no — stay weekly.

---

## Related

- [[durable-pipelines-flashcards]] — different topic (system design), but similar theme: *silent failures from skipping the empty/edge case*.
