using namespace std;
#include <vector>
#include <stack>
#include <algorithm>

class Solution {
public:
    // TRIGGER TO MEMORISE (this is the gap, not the technique):
    //   "for each element, find the NEAREST LATER element satisfying X"  -> monotonic stack.
    //   Solved here only because the topic label said "stack". In an interview there is
    //   no label -- train the signal. See notes/pattern-triggers.md
    //
    // ANCHOR THE DESCRIPTION, DON'T NAME A DIRECTION:
    //   "the stack holds days still waiting for a warmer one, nearest on top"
    //   NOT "an increasing stack" / "a decreasing stack" (inverted 3x so far).
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        // IMPROVE 1 — name contradicts the invariant. This tracks no minimum; it holds
        // unresolved days. Call it `stk` or `unresolved`. A wrong name is worse than a
        // generic one.
        //
        // IMPROVE 2 — store bare indices, not pairs. temperatures[stk.top()] recovers
        // the value; a value can't recover its index, and the answer is a distance.
        // (2nd time the pair habit appeared — see Sliding Window Maximum.)
        stack<pair<int,int>> minTemp;

        vector<int> ans (temperatures.size(), 0);

        // IMPROVE 3 — `temperatures.size() - 1` is size_t arithmetic. 8TH SIGHTING.
        // On empty input it underflows to SIZE_MAX before narrowing to int.
        // Write `(int)temperatures.size() - 1`. NOTE: `i` must stay SIGNED here —
        // with size_t, `i >= 0` is always true and this loop never ends.
        for (int i = temperatures.size() - 1; i >= 0; --i) {
            while (!minTemp.empty() && temperatures[i] >= minTemp.top().first) {
                minTemp.pop();
            }
            // IMPROVE 4 — the whole if/else collapses to one line. `ans` was already
            // value-initialised to 0, so the empty branch is a no-op:
            //     if (!minTemp.empty()) ans[i] = minTemp.top().second - i;
            //
            // IMPROVE 5 — abs() is unnecessary, and it's PATTERN #10 (2nd sighting;
            // first was 4 calls in Trapping Rain Water). Walking right-to-left, every
            // index on the stack is strictly greater than i, so the difference is
            // provably positive. Defensive abs reads as "I didn't track the sign" —
            // and an interviewer WILL ask "can that go negative?"
            if (minTemp.empty()) {
                ans[i] = 0;
            } else {
                ans[i] = abs(i-minTemp.top().second);
            }
            minTemp.push({temperatures[i], i});
        }
        return ans;
    }
};