using namespace std;
#include <deque>
#include <vector>


class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque <pair<int, int>> maximums;
        maximums.push_back({nums[0], 0});
        for (int i = 1; i < k; ++i) {
            while (!maximums.empty() && nums[i] > maximums.back().first) {
                maximums.pop_back();
            }
            maximums.push_back({nums[i], i});
        }
        vector <int> ans;
        ans.push_back(maximums.front().first);
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
