using namespace std;
#include <vector>
#include <algorithm>
#include <stack>

class Solution {
public:
    // int carFleet(int target, vector<int>& position, vector<int>& speed) {
    //     vector<pair<int,int>> start_pos;
    //     for (int i = 0; i < position.size(); ++i) {
    //         start_pos.push_back({position[i], speed[i]});
    //     }
    //     sort (start_pos.begin(), start_pos.end());
    //     stack<pair<int, int>> st;
    //     for (int i = start_pos.size() - 1; i >= 0; --i) {
    //         if (st.empty()) {
    //             st.push(start_pos[i]);
    //             continue;
    //         }
    //         auto p = st.top();
    //         bool meets = start_pos[i].second == p.second ? false : (p.first - start_pos[i].first) / (start_pos[i].second - p.second) <= (target - p.first) / p.second;
    //         if (meets) continue;
    //         st.push(start_pos[i]);
    //     }
    //     return st.size();

    // int carFleet (int target, vector<int>& position, vector<int>& speed) {
    //     vector<pair<int, double>> times;
    //     int len = position.size();
    //     for (int i = 0; i < len; ++i) {
    //         times.push_back({position[i], 1.0* (target - position[i]) / speed[i]});
    //     }
    //     sort (times.begin(), times.end());
    //     stack<pair<int,double>> st;
    //     for (int i = 0; i < len; ++i) {
    //         if (st.empty() || times[i].second <= st.top().second) {
    //             st.push(times[i]);
    //             continue;
    //         }
    //         int tc_speed = target - st.top().first / st.top().second;
    //         int cc_speed = target - times[i].first / times[i].second;
    //         bool meet = cc_speed == tc_speed ? false : times[i].second - st.top().second < (times[i].first - st.top().first) / abs (cc_speed - tc_speed);
    //         if (!meet) st.push(times[i]);
    //         else {
    //             st.pop();
    //             st.push(times[i]);
    //         }
    //     }
    //     return st.size();
    // }

    // ⭐ THE INSIGHT THAT TOOK 4 ATTEMPTS — say this out loud:
    //   times[i] is a car's arrival time ONLY IF the road ahead is empty. The moment a
    //   car joins a fleet, its real arrival becomes the fleet's — and that must
    //   PROPAGATE BACKWARD down the chain. A pairwise/adjacent comparison cannot see
    //   this; you need a fold (running max).
    //
    //   Killer case: target=10, position=[0,4,2], speed=[2,1,3] -> answer 1.
    //   The car at 2 (speed 3) is the FASTEST and still can't escape: it hits the car
    //   at 4 (speed 1) at t=1, so its "2.667" is fiction and its real time is 6.0.
    //
    // TRIGGER: "X is blocked by Y, which may itself be blocked by Z"
    //          => pairwise comparison is structurally insufficient => use a fold.
    int carFleet (int target, vector<int>& position, vector<int>& speed) {
        vector<pair<int, double>> times;

        // IMPROVE 1 — `int len = position.size();` narrows size_t to int. 10TH SIGHTING.
        // The habit is never reaching for the cast: `(int)position.size()`.
        int len = position.size();

        for (int i = 0; i < len; ++i) {
            times.push_back({position[i], (target - position[i]) * 1.0/ speed[i]});
        }
        sort (times.begin(), times.end());

        // IMPROVE 2 — this stack is a RUNNING MAX in disguise, and it costs O(n) space
        // for nothing. You only push when times[i].second > fleets.top().second, so the
        // stack is strictly increasing and top() is ALWAYS the maximum. Nothing below
        // the top is ever read. Collapse it to one scalar (O(1) space, no empty case):
        //
        //     int  count   = 0;
        //     double slowest = 0.0;                 // times are always > 0 since position < target
        //     for (int i = len - 1; i >= 0; --i)
        //         if (times[i].second > slowest) { count++; slowest = times[i].second; }
        //     return count;
        //
        // IMPROVE 3 — pair<int,double> stores the position, but after the sort the
        // position is never read again. vector<double> would do, sorted by position via
        // a zip-then-drop, or keep the pair only for the sort key.
        stack <pair<int, double>> fleets;

        for (int i = len - 1; i >= 0; --i) {
            // IMPROVE 4 — the empty special case disappears with the scalar version,
            // because `slowest = 0.0` makes the first car pass automatically.
            if (fleets.empty()) {
                fleets.push(times[i]);
                continue;
            }
            // `<=` is correct: equal arrival times mean the cars meet exactly AT the
            // target, which counts as one fleet.
            if (times[i].second <= fleets.top().second) continue;
            fleets.push(times[i]);
        }
        return fleets.size();
    }
    // VERIFIED: 0 mismatches across 40,000 randomized tests.
    // GOOD — direction is right this time (backward from the target), `<=` handles the
    // meet-at-target tie, and 1.0* forces the division into double.
    
};