# Daily Temperatures

- Difficulty: Medium
- Topic: Array, Stack, Monotonic Stack
- Platform: LeetCode
- Link: https://leetcode.com/problems/daily-temperatures/

---

## Problem Statement

Given an array of integers temperatures representing the daily temperatures, return an array answer such that answer[i] is the number of days you have to wait after the ith day to get a warmer temperature. If there is no future day for which this is possible, keep answer[i] == 0 instead.

---

## Examples

### Example 1

```txt
Input: temperatures = [73,74,75,71,69,72,76,73]

Output: [1,1,4,2,1,1,0,0]
```

Explanation: For index 0 (73), next warmer is 74 at index 1 (1 day). For index 2 (75), next warmer is 76 at index 6 (4 days).

### Example 2

```txt
Input: temperatures = [30,40,50,60]

Output: [1,1,1,0]
```

Explanation: Each day is followed by a warmer day except the last one.

### Example 3

```txt
Input: temperatures = [30,60,90]

Output: [1,1,0]
```

Explanation: Each day is followed by a warmer day except the last one.

---

## Constraints

- `1 <= temperatures.length <= 10^5`
- `30 <= temperatures[i] <= 100`
---

## Intuition

To efficiently find the next warmer day for each temperature, we can use a monotonic decreasing stack that stores indices of unresolved days. As we iterate through the temperatures, whenever the current day's temperature exceeds the temperature at the index stored at the top of the stack, we pop that index and calculate the number of days waited. This process ensures each index is pushed and popped from the stack at most once.

---

## Takeaways

- Monotonic stacks are ideal for 'next greater element' problems to reduce time complexity from O(n^2) to O(n).
- Store indices instead of values in the stack when you need to calculate distance between elements.
- Elements in the stack represent unresolved states waiting for a future condition to be met.
- **The trigger phrase is "next greater / how long until".** Any problem asking *"for each element, find the nearest later element satisfying X"* is a monotonic stack. Learn the **signal**, not just the technique — see [pattern triggers](../../../../notes/pattern-triggers.md).
- **Anchor the description, don't name the direction:** *"the stack holds days still waiting for a warmer one, nearest on top."* Saying "increasing stack" or "decreasing stack" invites inversion.

## Two directions, both valid

**Right-to-left (mine) — "look ahead":** walk backwards; the stack holds candidates to the right. Pop everything not warmer than today, and whatever remains on top *is* the next warmer day.

```cpp
for (int i = n - 1; i >= 0; --i) {
    while (!stk.empty() && temperatures[i] >= temperatures[stk.top()]) stk.pop();
    if (!stk.empty()) ans[i] = stk.top() - i;
    stk.push(i);
}
```

**Left-to-right (canonical) — "resolve on arrival":** the stack holds *unresolved* days; when a warmer day arrives it settles all of them.

```cpp
for (int i = 0; i < n; ++i) {
    while (!stk.empty() && temperatures[i] > temperatures[stk.top()]) {
        int j = stk.top(); stk.pop();
        ans[j] = i - j;                 // resolved
    }
    stk.push(i);
}
```

Both are O(n) — each index is pushed once and popped once. The left-to-right form is [skeleton #9](../../../../notes/dsa-patterns/loop-skeletons.md) verbatim and generalises better to "previous smaller / next smaller" variants.

## Improvements

- **`abs(i - minTemp.top().second)` — the `abs` is unnecessary.** Walking right-to-left, every index on the stack is strictly greater than `i`, so `top().second - i` is provably positive. This is **pattern #10, second sighting** (four `abs` calls in Trapping Rain Water): reaching for a defensive construct instead of stating the invariant. An interviewer asks *"can that go negative?"* and the honest answer should be *"no, and here's why."*
- **`minTemp` is the wrong name.** The stack tracks no minimum — it holds days still waiting for a warmer one. `stk` or `unresolved` or `nextWarmer`. A name that contradicts the invariant is worse than a generic one.
- **The `if/else` is redundant.** `ans` is already value-initialized to 0, so the empty-stack branch is a no-op: `if (!stk.empty()) ans[i] = stk.top() - i;` replaces five lines with one.
- **Store bare indices, not `pair<value,index>`.** `temperatures[stk.top()]` recovers the value. Same note as Sliding Window Maximum — this is the second time the pair habit appeared.
- **`int i = temperatures.size() - 1`** — signed/unsigned, **8th sighting**. Empty input underflows to `SIZE_MAX` before narrowing. Write `(int)temperatures.size() - 1`.

## C++ Concepts

- **`vector<int> ans(n, 0)`** — the fill constructor value-initializes every element, which is what makes the "no warmer day" case free: leave it alone rather than writing 0.
- **`std::stack<int>` of indices** — indices are strictly more powerful than values here: `temperatures[i]` recovers the value, but a value cannot recover its position, and the answer is a *distance*.
- **`>=` vs `>` when popping** — with `>=`, equal temperatures are popped, so ties don't count as "warmer". Correct, since the problem asks for a *strictly* warmer day. The comparison operator *is* the specification.
- **`std::abs` on a provably non-negative difference** — costs nothing at runtime, but signals to a reader that the sign was not reasoned about. Prefer stating the invariant and dropping the call.
- **Reverse iteration with a signed index** — `for (int i = n - 1; i >= 0; --i)` requires `i` to be **signed**; with `size_t`, `i >= 0` is always true and the loop never terminates. A classic instance of the [signed/unsigned trap](../../../../notes/cpp/signed-unsigned-pitfalls.md).
