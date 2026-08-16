using namespace std;
#include <string>

class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int len = s1.size();
        if (s2.size() < len) return false;
        int freq1 [26] = {}, freq2[26] = {};
        for (char& ch: s1) 
            freq1[ch - 'a']++;
        for (int i = 0; i+1 < len; ++i) 
            freq2[s2[i] - 'a']++;
        for (int i = 0; i + len <= s2.size(); ++i) {
            freq2[s2[i+len-1] - 'a']++; // expand right window

            bool isPermutation = true;
            for (int j = 0; j < 26; ++j) if (freq1[j] != freq2[j]) isPermutation = false;
            if (isPermutation) return true;

            freq2[s2[i] - 'a']--; // shrink left window
        }
        return false;
    }
};
