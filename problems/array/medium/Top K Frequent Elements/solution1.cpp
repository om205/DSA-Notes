#include<bits/stdc++.h>
#define ll long long int
using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map <int, int> mp;
        vector<int> freq;
        for (int& num: nums) mp[num] ++;
        priority_queue <pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        for (auto& it: mp) {
            pq.push ({it.second, it.first});
            if (pq.size() > k) pq.pop();
        }
        while (pq.size() > 0) {
            freq.push_back(pq.top().second);
            pq.pop();
        }
        return freq;
    }
};