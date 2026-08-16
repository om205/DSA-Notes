using namespace std;
#include <unordered_map>
#include <string>

class Solution {
    bool isFreqSubset (unordered_map <char, int> & m1, unordered_map <char, int>& m2) {
        for (auto& it: m1) {
            if (m2[it.first] < it.second) return false;
        }
        return true;
    }
public:
    string minWindow(string s, string t) {
        if (s.size() < t.size()) return "";
        unordered_map <char, int> freq1, freq2;
        int l = 0;
        int win_l = -1, win_r = -1;
        string win_substr = ""; // discarded computing substr as memory limit start to exceed
        for (char &ch: t) freq2[ch]++;
        for (int r = 0; r < s.size(); ++r) {
            freq1[s[r]]++; // expand

            while (isFreqSubset (freq2, freq1)) {
                if (win_l == -1 || r-l+1 < win_r - win_l + 1)  { // record
                    win_r = r, win_l = l;
                }

                freq1[s[l]]--;
                l++; // repair
            }
        }
        if (win_l == -1) return "";
        return s.substr (win_l, win_r - win_l + 1);
    }
};
