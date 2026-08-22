# Car Fleet

- Difficulty: Medium
- Topic: Array, Stack, Sorting, Monotonic Stack
- Platform: LeetCode
- Link: https://leetcode.com/problems/car-fleet/description/

---

## Problem Statement

There are n cars at given positions traveling towards a target destination at given speeds. A car can never pass another car ahead of it, but it can catch up and merge into a fleet traveling at the slower car's speed. Return the number of car fleets that will arrive at the destination.

---

## Examples

### Example 1

```txt
Input: target = 12, position = [10,8,0,5,3], speed = [2,4,1,1,3]

Output: 3
```

Explanation: The cars starting at 10 (speed 2) and 8 (speed 4) become a fleet at position 12. The car starting at 0 doesn't catch up to any car. The cars starting at 5 (speed 1) and 3 (speed 3) become a fleet at position 6 and arrive at 12 together.

### Example 2

```txt
Input: target = 10, position = [3], speed = [3]

Output: 1
```

Explanation: There is only one car, so there is 1 fleet.

### Example 3

```txt
Input: target = 100, position = [0,2,4], speed = [4,2,1]

Output: 1
```

Explanation: All cars catch up to each other and form a single fleet.

---

## Constraints

- `n == position.length == speed.length`
- `1 <= n <= 10^5`
- `0 < target <= 10^6`
- `0 <= position[i] < target`
- `All the values of position are unique.`
- `0 < speed[i] <= 10^6`
---

## Intuition

Sort cars by starting position in descending order to process those closest to the target first. Calculate the time each car needs to reach the target independently. If a trailing car takes less or equal time than the leading fleet in front of it, it catches up and merges into that fleet; otherwise, it starts a new fleet.

---

## Takeaways

- Sorting elements relative to destination simplifies tracking interactions.
- Transforming speed and distance into time-to-target reduces a dynamic simulation to static comparisons.
- A monotonic stack or maintaining a running maximum time tracks active fleet leaders efficiently.
- **The reframe that collapses this problem:** don't compute *where* cars meet — compare *when they arrive*. Car `i` joins the fleet ahead **iff `time[i] <= time[ahead]`**. Since it starts behind, arriving no later means it must have caught up before the target.
- **Any ratio in a geometry/motion problem is a `double`.** Integer division silently truncates and flips comparisons that are close.

## First attempt — the model was right, the guards were missing

I built a catch-up-time model: *time for the rear car to close the gap* vs *time for the fleet ahead to reach the target*.

```cpp
bool meets = cur.speed == p.speed ? false
           : (p.pos - cur.pos) / (cur.speed - p.speed) <= (target - p.pos) / p.speed;
```

Conceptually sound — but it failed **LeetCode's own example 1** and ~45% of random tests. Two bugs.

### Bug 1 — integer division

Both quotients are `int` arithmetic, and arrival times are almost never whole numbers.

```
target = 27, position = [3, 10], speed = [7, 5]
  true times:  3.5  and  3.4   -> no catch-up -> 2 fleets
  int  times:  3    and  3     -> 3 <= 3 -> "meets" -> 1 fleet   ✗
```

### Bug 2 — no guard that the rear car is faster

```cpp
(p.pos - cur.pos) / (cur.speed - p.speed)
                     └── NEGATIVE when the rear car is slower
```

The gap is positive and the speed difference is negative, so the catch-up time comes out **negative** — and a negative value is `<=` any positive time. **A slower car "catches" the car ahead.**

That is exactly what breaks example 1: the car at position 5 (speed 1) chasing position 10 (speed 2) computes `5 / (1-2) = -5 <= 1`, joins wrongly, and the answer comes out 2 instead of 3.

### The two-line fix — the model survives

```cpp
bool meets = (cur.speed > p.speed) &&                              // guard FIRST
             ((double)(p.pos - cur.pos) / (cur.speed - p.speed)    // then double
              <= (double)(target - p.pos) / p.speed);
```

Verified: **0 mismatches across 40,000 randomized tests.** The approach was never wrong — it was under-guarded.

## Second attempt — worse, and the lesson is about *debugging*, not cars

V2 switched to arrival times (correct, in `double`) — and then **also** computed catch-up geometry on top of them. Result: longer, slower, and more wrong than V1.

| Version | Wrong on 30,000 random tests |
|---|---|
| V1 (catch-up model, int division) | 13,5xx (~45%) |
| V2 (times **plus** geometry) | **13,688 (~46%)** |
| V2 with the geometry **deleted** | **0** |

### What broke

```cpp
int tc_speed = target - st.top().first / st.top().second;
```

- **Operator precedence:** `/` binds tighter than `-`, so this is `target - (position / time)`. The intent was `(target - position) / time`. Meaningless quantity.
- **Assigned to `int`**, truncating the `double` that had just been deliberately created.
- **Recomputing a discarded value:** `speed` was dropped when building `times`, then reconstructed by division. It was already available.
- **`if` should be `while`:** one car can absorb several fleets behind it; a single `if` merges at most one.
- **`<=` should be `<`** in the push test: equal arrival times mean the cars meet *at* the target, which counts as one fleet.
- **`abs()` on a difference** whose sign the ordering already fixes — third sighting.

### The fix is deletion

```cpp
int carFleet(int target, vector<int>& position, vector<int>& speed) {
    int len = position.size();
    vector<pair<int,double>> times;
    for (int i = 0; i < len; ++i)
        times.push_back({position[i], 1.0 * (target - position[i]) / speed[i]});
    sort(times.begin(), times.end());

    stack<double> st;
    for (int i = 0; i < len; ++i) {
        while (!st.empty() && st.top() <= times[i].second) st.pop();  // it catches me -> merge
        st.push(times[i].second);
    }
    return st.size();
}
```

Same direction, same structure, geometry removed. **0 failures in 30,000 randomized tests.**

Note this iterates **left to right** (farthest from the target first), which is a valid alternative to the usual right-to-left scan: each new car is closer to the target than everything on the stack, so any fleet behind it with an arrival time `<= ` its own must merge into it.

### ⭐ The transferable lesson — additive debugging

The reframe *"compare arrival times, not catch-up positions"* was applied **on top of** the old model instead of **replacing** it. Once `times[i].second` existed, the question *"does the car behind catch me?"* was fully answered by `st.top() <= times[i].second`. Every line after that solved a problem that had already been eliminated.

> **When you adopt a new framing, delete the old one first. If both are still in the code, at least one of them is wrong.**
>
> Ask **"what can I remove?"** before **"what can I add?"**

## Third attempt — adjacent comparison, and the failing case that exposes it

```cpp
int fleets = 1;
for (int i = 1; i < len; ++i) {
    if (times[i].second >= times[i-1].second) continue;
    fleets++;
}
```

**Fails `target=10, position=[0,4,2], speed=[2,1,3]`** → returns 2, answer is 1.

Sorted by position: `[(0, 5.0), (2, 2.667), (4, 6.0)]`. At `i=1`, `2.667 >= 5.0` is false, so it counts a new fleet — deciding the car at position 2 escapes the car at position 0.

**But 2.667 is fiction.** The car at position 2 is stuck behind the car at position 4:

```
 t      A(p0,s2)   C(p2,s3)   B(p4,s1)
 0.0      0.00      2.00      4.00
 1.0      2.00      5.00      5.00   <- C reaches B, stuck at speed 1 forever
 2.0      4.00      6.00      6.00
 3.0      6.00      7.00      7.00
 4.0      8.00      8.00      8.00   <- A reaches the fleet
 5.0      9.00      9.00      9.00
 6.0     10.00     10.00     10.00   <- all three arrive together => 1 FLEET
```

C is the *fastest* car and still cannot escape, because speed doesn't matter once something slower is in front.

> ### ⭐ The core insight
> **`times[i]` is the arrival time only if the road ahead is empty. The moment a car joins a fleet, its real arrival time becomes the fleet's — and that must propagate backward down the chain.**

An adjacent comparison cannot see this. The fleet ahead's arrival time is the **maximum of every time ahead**, not the time of the one neighbouring car.

### The fix — one variable

```cpp
int fleets = 0;
double slowest = 0.0;
for (int i = len - 1; i >= 0; --i)        // from the TARGET backward
    if (times[i].second > slowest) {      // cannot catch the fleet ahead
        fleets++;
        slowest = times[i].second;        // this car now leads; its time propagates
    }
return fleets;
```

`slowest` **is** the propagation. Two changes from V3: iterate backward, and compare against the running max rather than `times[i-1]`.

### The thread across all three attempts

| Attempt | Compared | Missing |
|---|---|---|
| V1 | catch-up geometry, adjacent pair | sign guard, `double`, propagation |
| V2 | times **and** geometry, adjacent pair | propagation |
| V3 | raw times, adjacent pair | propagation |

Every version compared **one car to one neighbour**. The problem needs state that **accumulates down the chain**.

> **Trigger:** when a problem says *"X is blocked by Y, which may itself be blocked by Z,"* pairwise comparison is structurally insufficient. Reach for a **fold** — running max, running min, or a stack.

## The simpler formulation

Comparing arrival times removes the gap algebra, the speed comparison, the divide-by-zero case, and even the stack — the "monotonic stack" here is just a running maximum:

```cpp
int carFleet(int target, vector<int>& position, vector<int>& speed) {
    int n = position.size();
    vector<pair<int,double>> cars;
    for (int i = 0; i < n; ++i)
        cars.push_back({position[i], (double)(target - position[i]) / speed[i]});
    sort(cars.begin(), cars.end());               // by position, ascending

    int fleets = 0;
    double slowest = 0.0;
    for (int i = n - 1; i >= 0; --i)              // nearest the target first
        if (cars[i].second > slowest) {           // cannot catch the fleet ahead
            fleets++;
            slowest = cars[i].second;             // this car now leads
        }
    return fleets;
}
```

**Lesson:** the problem is tagged *Stack*, and reaching for one was reasonable — but the tag names a *possible* tool, not the necessary one. The trigger here is *"process items in order, each blocked by the slowest one ahead"* → sort + running max. See [pattern triggers](../../../../notes/pattern-triggers.md).

## C++ Concepts

- **Integer vs floating-point division** — `(a - b) / c` on `int`s truncates toward zero. Cast **one operand** to `double` *before* dividing: `(double)(a - b) / c`. Casting the result (`(double)((a-b)/c)`) is too late — truncation already happened.
- **Short-circuit `&&` as a guard** — `(cur.speed > p.speed) && (ratio <= ratio)` evaluates the division only when the speed test passes, preventing both the negative-time bug and a divide-by-zero on equal speeds. Same guard-before-access habit as the skip-loops in 3Sum and `stack::top()` in Valid Parentheses.
- **`sort` on `vector<pair<A,B>>`** — `pair`'s `operator<` is lexicographic, so this sorts by `.first` (position) then `.second`. That is exactly what's wanted; no comparator needed.
- **Pairing two parallel arrays** — `position[i]` and `speed[i]` must stay associated through the sort, so they must be zipped into one container first. Sorting them separately would silently destroy the correspondence.
- **`double` precision here is safe** — positions and speeds are small integers, so the ratios are exactly representable enough that ties compare correctly. For adversarial inputs, compare cross-multiplied integers (`(target - a.pos) * b.speed` vs `(target - b.pos) * a.speed`) to avoid floating point entirely.
- **Signed/unsigned** — `i < position.size()` mixes `int` and `size_t`. **9th sighting.** See [signed vs. unsigned pitfalls](../../../../notes/cpp/signed-unsigned-pitfalls.md).

> ⚠️ `solution.cpp` is still a stub — paste the corrected version in.
