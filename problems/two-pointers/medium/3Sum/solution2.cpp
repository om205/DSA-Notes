using namespace std;
#include <vector>
#include <algorithm>

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        // vector <vector<int>> triplets;
        // // sort (nums.begin(), nums.end());
        // map <int, vector<int>> hash_mp;
        // for (int i = 0; i < nums.size(); ++i) hash_mp [nums[i] * -1].push_back (i);
        // for (int i = 0; i < nums.size(); ++i)
        // for (int j = i+1; j < nums.size(); ++j)
        // if (hash_mp [nums[i] + nums[j]].size() > 1) {
        //     for (auto& it: hash_mp[nums[i] + nums[j]]
        // }

        // the above solution got messy - needed de-duplication

        sort (nums.begin(), nums.end());
        vector <vector<int>> triplets;
        for (int i = 0; i + 2 < nums.size(); ++i) {
            if (i > 0 && nums[i] == nums[i-1]) continue;
            int target = -1 * nums[i];
            int l = i+1, r = nums.size() - 1;
            while (r > l) {
                if (nums[l] + nums[r] == target) {
                    triplets.push_back({nums[i], nums[l], nums[r]});
                    l++; r--; 
                    while (nums[l] == nums[l-1] && l < r) l++;
                    while (nums[r] == nums[r+1] && l < r) r--;
                    continue;
                }
                if (nums[l] + nums[r] > target) r--;
                else l++;
            }          
        }
        return triplets;
    }
};