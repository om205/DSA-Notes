#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    const char DELIMETER = '#';

    string encode(vector<string>& strs) {
        string encoded = "";
        for (string& str: strs) 
            encoded += to_string(str.size()) + DELIMETER + str;
        return encoded;
    }

    vector<string> decode(string s) {
        vector<string> decoded;
        int next_seg_len, del_pos, pos = 0;
        string next_seg;
        char delimeter = DELIMETER;
        auto next_del_pos = [delimeter](string& str, int pos) -> int {
            for (int i = pos; i < str.size(); ++i) 
                if (str[i] == delimeter) return i;
            return str.size();
        };
        while (pos < s.size()) {
            del_pos = next_del_pos(s, pos);
            next_seg_len = stoi(s.substr(pos, del_pos - pos));
            pos = del_pos + 1;
            next_seg = s.substr(pos, next_seg_len);
            decoded.push_back(next_seg);
            pos += next_seg_len;
        }
        return decoded;
    }
};