using namespace std;
#include <deque>
#include <vector>


class Solution {
public:
    // KEY OBSERVATION (say this out loud in an interview):
    //   If nums[j] < nums[i] for some j < i, then nums[j] can never be the maximum
    //   of any window containing i -> discard it permanently. Same domination lemma
    //   derived from scratch in Container With Most Water. Each element enters and
    //   leaves the deque once -> O(n).
    //
    // ANCHOR THE PHRASE, DON'T NAME THE DIRECTION:
    //   say "the front of the deque always holds the window's maximum"
    //   NOT "we maintain an increasing/decreasing sequence" (inverted 3x so far).
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque <pair<int, int>> maximums;

        // IMPROVE 1 — store bare indices, not pairs. nums[dq.back()] recovers the
        // value, so deque<int> suffices: half the memory, no .first/.second noise.
        //
        // IMPROVE 2 — this line is a special case the loop already handles. The
        // `!maximums.empty()` guard below covers the first iteration, so start the
        // prime loop at i = 0 and delete this. It also removes an unguarded nums[0]
        // read (safe only because constraints promise n >= 1).
        maximums.push_back({nums[0], 0});
        for (int i = 1; i < k; ++i) {
            while (!maximums.empty() && nums[i] > maximums.back().first) {
                maximums.pop_back();
            }
            maximums.push_back({nums[i], i});
        }
        vector <int> ans;
        ans.push_back(maximums.front().first);

        // IMPROVE 3 — two loops duplicate the pop-back logic. Skeletons #2 (fixed
        // window) + #9 (monotonic deque) combine into ONE loop:
        //
        //   for (int i = 0; i < n; ++i) {
        //       if (!dq.empty() && dq.front() == i - k) dq.pop_front();          // evict
        //       while (!dq.empty() && nums[dq.back()] <= nums[i]) dq.pop_back(); // dominate
        //       dq.push_back(i);
        //       if (i >= k - 1) ans.push_back(nums[dq.front()]);                 // record
        //   }
        //
        // IMPROVE 4 — `i < nums.size()` compares int against size_t. 7TH SIGHTING.
        // Write `i < (int)nums.size()`. The habit is never reaching for the cast.
        for (int i = k; i < nums.size(); ++i) {
            if (maximums.front().second == i-k) {
                maximums.pop_front();
            }
            while (!maximums.empty() && nums[i] > maximums.back().first) {
                maximums.pop_back();
            }
            maximums.push_back({nums[i], i});
            ans.push_back(maximums.front().first);
        }
        return ans;
    }
};
