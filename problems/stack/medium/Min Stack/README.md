# Min Stack

- Difficulty: Easy
- Topic: Stack, Design
- Platform: LeetCode
- Link: https://leetcode.com/problems/min-stack/description/

---

## Problem Statement

Design a stack that supports push, pop, top, and retrieving the minimum element in constant time. Implement the MinStack class with push(val), pop(), top(), and getMin() methods. Each function must operate in O(1) time complexity.

---

## Examples

### Example 1

```txt
Input: ["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]

Output: [null,null,null,null,-3,null,0,-2]
```

Explanation: MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin(); // return -3
minStack.pop();
minStack.top();    // return 0
minStack.getMin(); // return -2

---

## Constraints

- `-2^31 <= val <= 2^31 - 1`
- `Methods pop, top and getMin operations will always be called on non-empty stacks.`
- `At most 3 * 10^4 calls will be made to push, pop, top, and getMin.`
---

## Intuition

To retrieve the minimum element in constant time, we can maintain an auxiliary stack alongside the main stack that stores the minimum value seen up to each point. Whenever a new element is pushed, we also push the smaller of the new element and the current minimum onto the auxiliary stack. Popping from both stacks simultaneously ensures that the minimum state remains synchronized with the stack content.

---

## Takeaways

- Use an auxiliary stack or pair values with their corresponding state to achieve O(1) query time.
- Trade O(n) space complexity to achieve optimal O(1) time complexity across all stack operations.
- Keep dual data structures synchronized during state-changing operations like push and pop.
- **Every technique carries an applicability condition that is invisible in its code.** Transferring a pattern means asking *"does the reason it worked still hold?"* — not *"does the shape fit?"*

## ⚠️ Why the monotonic deque fails here (first attempt)

I reached for the monotonic deque straight from [Sliding Window Maximum](../../../sliding-window/hard/Sliding%20Window%20Maximum/README.md). Right instinct, violated precondition.

### Minimal failing case — 4 operations

```
push(2)  →  st=[2]     dq=[2]
push(1)  →  st=[2,1]   dq.back()=2 > 1 → pop_back → push → dq=[1]
                                    ↑ the 2 is destroyed, but it is STILL IN THE STACK
pop()    →  st.top()=1 == dq.front()=1 → pop_front → dq=[]   st=[2]
getMin() →  dq.front() on an empty deque → UB.  Correct answer is 2.
```

### The precondition

> **Discarding a dominated element is only safe if that element is guaranteed to leave before the element that dominated it.**

| Container | Removal order | Dominated element leaves first? |
|---|---|---|
| Sliding window (FIFO) | oldest first | ✅ `j < i` ⇒ `j` exits first ⇒ `j` can never win again |
| **Stack (LIFO)** | newest first | ❌ `i` pops *before* `j` ⇒ `j` resurfaces as the minimum |

In a stack the dominated element sits **underneath** and outlives its dominator, so discarding it destroys information guaranteed to be needed later.

A second symptom followed from the same root: `pop()` compared against `dq.front()` while the stack removes from the top, so stale entries also accumulated. **Two bugs, one cause — the stack removes newest-first while the deque was organised oldest-first.**

## The fix — an auxiliary stack of minima

```cpp
void push(int value) {
    st.push(value);
    if (dq.empty() || dq.back() >= value) dq.push_back(value);   // never discard
}
void pop() {
    if (dq.back() == st.top()) dq.pop_back();
    st.pop();
}
int getMin() { return dq.back(); }
```

Stop discarding entirely. `dq` becomes a stack of minima aligned with the main stack's LIFO order, so `dq.back()` is always the current minimum. **O(1) for every operation, O(n) space.**

### `>=` is load-bearing, not a style choice

With `>` instead of `>=`, `push(1); push(1)` records only one `1`. The first `pop()` then removes the sole copy from `dq` while a `1` remains in `st`, and `getMin()` breaks. **`>=` keeps duplicates, which is exactly what a stack of minima requires.**

## C++ Concepts

- **`std::stack` is a container adaptor** — a thin interface (`push`/`pop`/`top`/`empty`/`size`) over a `deque` by default. No iteration, no random access; that restriction is the point.
- **Name the type after the role.** `dq` here is only ever used as a stack (`push_back`/`pop_back`/`back`), so declare `stack<int> mins`. A `deque` whose extra capability is never used misleads the reader about the invariant.
- **`std::deque::back()` on an empty deque is undefined behaviour**, exactly like `stack::top()`. `pop()` here is safe only because `dq` is non-empty whenever `st` is — worth stating as an explicit invariant rather than leaving implicit.
- **Trading space for time** — the auxiliary stack costs O(n) memory to make `getMin()` O(1) instead of O(n). Naming this trade-off out loud is a scoring beat in an interview.
- **Empty constructor body** — `MinStack() {}` is fine; both members default-construct. `= default` states the intent more clearly.
