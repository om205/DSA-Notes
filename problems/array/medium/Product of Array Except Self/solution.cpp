#include<bits/stdc++.h>
#define ll long long int
using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> productArr (n);
        productArr[0] = 1;
        for (int i = 1; i < n; ++i) productArr[i] = productArr[i-1] * nums[i-1];
        int postProduct = 1;
        for (int i = n-2; i >=0; --i) {
            productArr[i] *= nums[i+1] * postProduct;
            postProduct *= nums[i+1];
        }
        /**
         * Improvement
         *  int postProduct = 1;
            for (int i = n - 1; i >= 0; --i) {
                productArr[i] *= postProduct;
                postProduct *= nums[i];
            }
         */
        return productArr;
    }
};