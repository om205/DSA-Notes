#include <vector>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        // IMPROVE 1 — naming, SECOND TIME: `p1`/`p2` says "two pointers exist"
        // but not which is which. `l`/`r` (or `left`/`right`) is the universal
        // convention and encodes direction. You used `fr`/`bk` in Valid Palindrome
        // for the same reason. Third strike gets a lecture. Just use l/r.
        //
        // IMPROVE 2 — the 1-indexed pointer trick is a bad trade. You store
        // pointers 1-indexed so the return is a clean `{p1, p2}` — but you then
        // pay `-1` on BOTH array reads, every single iteration. You optimized the
        // thing that happens once and taxed the thing that happens n times.
        // Cleaner: keep pointers 0-indexed, adjust once at the return:
        //
        //     int l = 0, r = numbers.size() - 1;
        //     ...
        //     if (sum == target) return {l + 1, r + 1};
        //
        // Reads match the array's actual indexing, so there's no mental
        // translation while tracing. Say this out loud in an interview —
        // "I'll keep pointers 0-indexed and convert at the boundary" — it
        // signals you think about where conversions belong.
        int p1 = 1, p2 = numbers.size();

        // IMPROVE 3 — `sum` is declared uninitialized in the outer scope but only
        // ever used inside the loop. Declare at first use: `int sum = ...` on the
        // line below. Narrowest scope possible, no uninitialized window.
        int sum;
        while (p2 > p1) {
            sum = numbers[p1-1] + numbers[p2-1];
            if (sum == target) return {p1, p2};
            if (sum > target) p2--;
            else p1++;
        }
        // Unreachable — problem guarantees exactly one solution. Fine to keep as a
        // defensive return, but SAY that in the interview so it doesn't read as
        // "didn't notice the guarantee."
        return {};
    }
};

// GOOD — called out so you keep doing it:
//   * `int p2 = numbers.size();` has no `- 1`, so no unsigned-underflow trap this
//     time (cf. notes/cpp/signed-unsigned-pitfalls.md). Note it was the 1-indexing
//     that saved you, not a deliberate guard — if you switch to 0-indexed per
//     IMPROVE 2, write `(int)numbers.size() - 1` and keep it deliberate.
//   * No sentinel-value branching. Clean 3-way compare on `sum`. This is the
//     shape interviewers want.
//   * O(n) time, O(1) space, single pass. Correct on all three examples.
