using namespace std;
#include <vector>
#include <algorithm>

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int maxProfit = 0, s = 0, f = 1;
        while (f < prices.size()) {
            maxProfit = max (maxProfit, prices[f] - prices[s]);
            if (prices[f] < prices[s]) s = f;
            f++;
        }
        return maxProfit;
    }
};