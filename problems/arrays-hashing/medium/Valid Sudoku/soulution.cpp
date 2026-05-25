#include <vector>
using namespace std;

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        int row[9] = {}, column[9] = {}, box[9] = {};
        for (int r = 0; r < board.size(); ++r) {
            for (int c = 0; c < board[0].size(); ++c) {
                int num = board[r][c] - '0';
                if (num < 0) continue;
                int b = (r/3) * 3 + (c/3);
                if (row[r] & (1 << num)) return false;
                if (column[c] & (1 << num)) return false;
                if (box[b] & (1 << num)) return false;
                row[r] |= 1 << num;
                column[c] |= 1 << num;
                box[b] |= 1 << num;
            }
        }
        return true;
    }
};