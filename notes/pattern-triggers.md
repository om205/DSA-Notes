# Pattern Triggers — Signal → Technique

> **The gap this fixes:** topic-organised practice (NeetCode 150, LeetCode tags) trains **execution** but never **selection**. You solve the stack problem because the page said "Stack." In an interview there is no label.
>
> Started 2026-08-22, after solving Daily Temperatures and noticing exactly this.

**Use it two ways:**
1. **Before every problem** — cover the topic tag. Read the statement, write down which pattern you'd pick and *which words made you pick it*. Then check. Costs 30 seconds, trains the only skill this table exists for.
2. **When stuck** — scan the Signal column, not the Technique column.

---

## The table

| Signal in the problem statement | Technique |
|---|---|
| "contiguous subarray / substring" + longest / shortest / at most K | **Sliding window** |
| Fixed window size k, something per window | **Fixed sliding window** |
| **Sorted** array + find a pair / triple summing to X | **Two pointers, opposite ends** |
| Maximise area / container / distance between two positions | **Two pointers, opposite ends** |
| **"For each element, the nearest LATER element that is bigger/smaller"** | **Monotonic stack** |
| "How many days/steps until…", "span", "next greater", "previous smaller" | **Monotonic stack** |
| Max/min of *every* window of size k | **Monotonic deque** |
| Nested, balanced, matching, undo, "valid sequence" | **Stack** |
| "Top K", "Kth largest/smallest", "merge K sorted" | **Heap** |
| Running median, "keep the k best so far" | **Two heaps** |
| Shortest path, **unweighted** graph / grid | **BFS** |
| Shortest path, **weighted**, non-negative | **Dijkstra** |
| Connected components, "are these two related", cycle in undirected | **Union-Find** |
| Dependencies, ordering, prerequisites, "can this be scheduled" | **Topological sort** |
| Explore/flood a grid or region, "count islands" | **DFS / BFS** |
| Generate **all** subsets / permutations / combinations / paths | **Backtracking** |
| "Count the ways", "min cost to reach", "can I make X" + overlapping choices | **DP** |
| Choices depend on a previous choice, 1-D state | **1-D DP** |
| Two sequences compared, or a grid walked | **2-D DP** |
| **Sorted** + "find the position/boundary of X" | **Binary search** |
| **"Minimise the maximum"** / "maximise the minimum" / "smallest k such that…" | **Binary search on the answer** |
| Many range-sum queries on a static array | **Prefix sums** |
| Prefix / autocomplete / word dictionary | **Trie** |
| Cycle in a linked list, find the middle, nth from the end | **Fast/slow pointers** |
| Intervals: merge, insert, "can attend all meetings" | **Sort by start, then sweep** |
| Anagram, permutation, "same characters" | **Frequency map** |
| "In-place", O(1) extra space demanded | **Two pointers / index encoding** |

---

## Structural tells (when the words don't give it away)

| Tell | Likely technique |
|---|---|
| Constraint `n ≤ 20` | Exponential is fine → **backtracking / bitmask** |
| Constraint `n ≤ 10^5`, answer needs O(n log n) | **Sort**, heap, or binary search |
| Constraint `n ≤ 10^3` with a 2-D feel | **O(n²) DP** |
| Answer is a *count* or a *minimum cost* | **DP** |
| Answer is *"all of the …"* | **Backtracking** |
| Asked for O(1) space on an array problem | **Two pointers** or reuse the input |
| "Return the k-th …" | **Heap** or **quickselect** or **binary search** |

---

## Drill

**Before every NC150 problem from now on:** cover the tag, read the statement, and write one line —

> *"I think this is ____ because the statement says ____."*

Then reveal the tag. **Log misses below** — a miss is more informative than a hit, because it shows which signal you failed to read.

| Date | Problem | My guess | Actual | Signal I missed |
|---|---|---|---|---|
| | | | | |

---

## Related

- [Loop skeletons](dsa-patterns/loop-skeletons.md) — once the pattern is chosen, the shape to type
- [Roadmap](roadmap.md) — bucket coverage and the theory triage
