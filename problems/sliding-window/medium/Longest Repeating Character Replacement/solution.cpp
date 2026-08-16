using namespace std;
#include <unordered_map>


class Solution {
public:
    int characterReplacement(string s, int k) {
        int len = s.size();
        unordered_map <char,int> freq;
        int l = 0, r = 0, ans = 0;
        while (r <= len) {
            int max_freq = 0; char ch;

            for (auto& it: freq) {
                if (it.second > max_freq) {
                    max_freq = it.second;
                    ch = it.first;
                }
            }

            int replacable = r-l-max_freq;
            if (replacable <= k) {
                ans = max (ans, r-l);
                if (r < len)
                freq[s[r]]++; 
                r++;
                continue;
            }
            freq[s[l]]--;
            if (freq[s[l]] == 0) freq.erase (s[l]);
            l++; 
        }
        return ans;
    }
};