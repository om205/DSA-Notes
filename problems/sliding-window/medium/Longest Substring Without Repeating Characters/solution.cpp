using namespace std;
#include<algorithm>
#include<unordered_map>
#include<string>

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int len = s.size(), l = 0, r = 0, max_len = 0; 
        unordered_map <char, bool> exists;
        while (r < len) {
            if (exists[s[r]]) {
                while (l < r) {
                    exists[s[l]] = false;
                    if (s[l] == s[r]) {
                        l++;
                        break;
                    }
                    l++;
                }
            }
            exists[s[r]] = true;
            max_len = max (max_len, r-l+1);
            r++;

            // if (exists[s[r]]) 
            //     while (s[l] != s[r]) exists[s[l++]] = false; 
            // exists[s[r]] = true;
            // max_len = max(max_len, ++r - l);
        }
        return max_len;
    }
};
