#include<bits/stdc++.h>
#define ll long long int
using namespace std;


class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        
        unordered_map<int,int> freq;
        for (auto&it: nums) freq[it]++;
        vector <vector<int>> bucket (1e5 + 1);
        for (auto& it: freq) bucket [it.second].push_back(it.first);
        vector <int> topk;
        for (auto it = bucket.rbegin(); it != bucket.rend(); it++) {
            for (auto& i: *it) {
                topk.push_back (i);
                if (topk.size() >= k) return topk;
            }
        }
        return topk;
    }
};