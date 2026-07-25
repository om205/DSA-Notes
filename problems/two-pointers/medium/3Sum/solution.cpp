#include <vector>
#include <set>
#include <algorithm>
using namespace std;

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
        set <vector<int>> triplet_st;
        vector <vector<int>> triplets;
        for (int i = 0; i < nums.size() - 1; ++i) {
            int target = -1 * nums[i];
            int l = i+1, r = nums.size() - 1;
            while (r > l) {
                if (nums[l] + nums[r] == target) {
                    vector<int> triplet = {nums[i], nums[l], nums[r]};
                    // sort (triplet.begin(), triplet.end()); // it was redundent
                    triplet_st.insert (triplet);
                    l++; r--; continue;
                }
                if (nums[l] + nums[r] > target) r--;
                else l++;
            }          
        }
        for (auto& i: triplet_st) triplets.push_back (i);
        return triplets;
    }
};