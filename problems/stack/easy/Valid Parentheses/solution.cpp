using namespace std;
#include <string>
#include <stack>

class Solution {
public:
    bool isValid(string s) {
        stack <char> st;
        for (char& ch: s) {
            if (ch == '(' || ch == '{' || ch == '[') st.push(ch);
            else {
                if (st.empty() ) return false;
                char top_ch = st.top();
                
                if ( (ch == ')' && top_ch != '(') || (ch == '}' && top_ch != '{') || (ch == ']' && top_ch != '[')) return false; 
                st.pop();
            }
        }
        return st.empty();
    }
};