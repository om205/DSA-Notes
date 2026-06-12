#include <string>
using namespace std;

class Solution {
public:
    bool isPalindrome(string s) {
        // IMPROVE 1 — naming: `fr`/`bk` is non-standard. Convention in two-pointer
        // problems is `l`/`r` or `left`/`right`. Interviewers skim faster with that.
        //
        // IMPROVE 2 — signed/unsigned trap: `s.size()` returns size_t (unsigned).
        // If s were empty, `s.size() - 1` underflows to SIZE_MAX BEFORE the int
        // assignment. Lucky here because LeetCode guarantees length >= 1, but in
        // general write: `int bk = (int)s.size() - 1;` — or check empty first.
        // See: notes/cpp/signed-unsigned-pitfalls.md
        int fr = 0, bk = s.size() - 1;

        // IMPROVE 3 — sentinel smell: returning '*' to mean "not alphanumeric"
        // and then branching on it 3 ways below is the root cause of the messy
        // cascade. The canonical pattern is two skip-loops + one compare:
        //
        //     while (l < r) {
        //         while (l < r && !isAlnum(s[l])) l++;
        //         while (l < r && !isAlnum(s[r])) r--;
        //         if (toLower(s[l]) != toLower(s[r])) return false;
        //         l++; r--;
        //     }
        //
        // One concern per loop. Memorize this shape — it shows up in 3Sum,
        // Container With Most Water, Trapping Rain Water, Two Sum II.
        auto fn = [&s] (int pos) -> char {
            if (s[pos] >= 'A' && s[pos] <= 'Z') return s[pos] + 32;
            if ((s[pos] >= 'a' && s[pos] <= 'z') || (s[pos] >= '0' && s[pos] <= '9')) return s[pos];
            return '*';
        };
        while (bk > fr) {
            char ch_fr = fn(fr), ch_bk = fn(bk);
            // IMPROVE 4 — this 4-branch cascade is the cost of the '*' sentinel.
            // With skip-loops above, this whole block collapses to one compare.
            if (ch_fr == '*' && ch_bk == '*') {
                bk--; fr++; continue;
            } else if (ch_fr == '*') {
                fr++; continue;
            } else if (ch_bk == '*') {
                bk--; continue;
            }
            if (ch_fr != ch_bk) return false;
            fr++; bk--;
        }
        return true;
    }
};
