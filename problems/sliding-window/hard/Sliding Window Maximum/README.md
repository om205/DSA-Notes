# Sliding Window Maximum

- Difficulty: Hard
- Topic: Array, Queue, Sliding Window, Monotonic Queue, Heap (Priority Queue)
- Platform: LeetCode
- Link: https://leetcode.com/problems/sliding-window-maximum

---

## Problem Statement

You are given an array of integers nums, and a sliding window of size k moving from the very left of the array to the very right. You can only see the k numbers in the window at any point, and the window moves right by one position each time. Return an array containing the maximum element for each sliding window position.

---

## Examples

### Example 1

```txt
Input: nums = [1,3,-1,-3,5,3,6,7], k = 3

Output: [3,3,5,5,6,7]
```

Explanation: Window position: [1 3 -1] max = 3; [3 -1 -3] max = 3; [-1 -3 5] max = 5; [-3 5 3] max = 5; [5 3 6] max = 6; [3 6 7] max = 7.

### Example 2

```txt
Input: nums = [1], k = 1

Output: [1]
```

Explanation: There is only one element in the array, so the maximum is 1.

---

## Constraints

- `1 <= nums.length <= 10^5`
- `-10^4 <= nums[i] <= 10^4`
- `1 <= k <= nums.length`
---

## Intuition

Maintain a double-ended queue (deque) storing indices of array elements in monotonically decreasing order of their values. For each new element, pop smaller elements from the back of the deque since they can no longer be the maximum, and pop elements from the front if they fall outside the current window size k. The element at the front of the deque will always be the maximum for the current sliding window.

---

## Takeaways

- A monotonic queue enables O(1) query time for the maximum or minimum element in a dynamic window.
- Storing indices in the deque allows efficient verification of whether elements have slipped out of the window.
- Each element is pushed and popped at most once, leading to an optimal linear O(n) runtime.
- **State the anchor, never the direction.** Say *"the front of the deque always holds the window's maximum"* — not *"we maintain a decreasing sequence."* A concrete position cannot be inverted; a direction word can (and I have inverted it three times running).

## The key observation — it's the domination lemma again

> **If `nums[j] < nums[i]` for some `j < i`, then `nums[j]` can never be the maximum of any window containing `i`. It is dominated — discard it permanently.**

This is the *same argument* derived from scratch in [Container With Most Water](../../../two-pointers/medium/Container%20With%20Most%20Water/README.md): a candidate that cannot win under any future configuration is discarded forever. Each element enters and leaves the deque once → **O(n)**.

## ⚠️ The precondition — why this technique does NOT transfer to a stack

The monotonic deque *looks* like "keep it ordered, drop the dominated." Its actual contract is stricter:

> **Discarding a dominated element is only safe if that element is guaranteed to leave before the element that dominated it.**

| Container | Removal order | Dominated element leaves first? |
|---|---|---|
| Sliding window (FIFO) | oldest first | ✅ `j < i` ⇒ `j` exits first ⇒ safe to discard |
| **Stack (LIFO)** | newest first | ❌ `i` pops *before* `j` ⇒ `j` becomes the min again ⇒ **unsafe** |

Applying this deque to [Min Stack](../../../stack/medium/Min%20Stack/README.md) destroys values still sitting in the stack. When transferring a pattern, the question is not *"does the shape fit?"* but ***"does the reason it worked still hold?"***

## Structure note

Two loops (prime + main) duplicate the pop-back logic. Skeletons #2 and #9 combine into one, storing bare indices:

```cpp
for (int i = 0; i < n; ++i) {
    if (!dq.empty() && dq.front() == i - k) dq.pop_front();          // evict
    while (!dq.empty() && nums[dq.back()] <= nums[i]) dq.pop_back(); // dominate
    dq.push_back(i);
    if (i >= k - 1) ans.push_back(nums[dq.front()]);                 // record
}
```

## C++ Concepts

- **`std::deque`** — double-ended queue with O(1) `push_back` / `pop_back` / `push_front` / `pop_front` and random access. The only STL container offering all of those; `vector` cannot pop from the front cheaply, `queue` cannot pop from the back at all.
- **Store indices, not `pair<value, index>`** — `nums[dq.back()]` recovers the value, so `deque<int>` suffices. Halves the memory and removes `.first`/`.second` noise. Indices are also *required* for the eviction test (`dq.front() == i - k`).
- **`<=` vs `<` when popping the back** — with `<=`, equal values are evicted so only the newest survives (it stays in the window longer). Both are correct here; `<=` keeps the deque smaller.
- **Unguarded `nums[0]`** — the initial `push_back({nums[0], 0})` reads element 0 before any size check. Safe only because the constraints guarantee `n >= 1`. Starting the loop at `i = 0` removes both the special case and the unguarded read, since the `!empty()` guard already covers the first iteration.
- **Signed/unsigned comparison** — `i < nums.size()`. Seventh occurrence; see [signed vs. unsigned pitfalls](../../../../notes/cpp/signed-unsigned-pitfalls.md).
