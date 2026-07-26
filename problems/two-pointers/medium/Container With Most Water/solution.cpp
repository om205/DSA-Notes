#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        // int len = height.size();
        // vector<int> pre_sum (len, -1), post_sum (len, -1);
        // int max_num = 0;
        // for (int i = 0; i + 1 < len; ++i) {
        //     if (height[i] > max_num) {
        //         max_num = height[i];
        //         pre_sum[i+1] = i;
        //     } else {
        //         pre_sum[i+1] = pre_sum[i];
        //     }
        // }
        // max_num = 0;
        // for (int i = len-1; i > 0; --i) {
        //     if (height[i] > max_num) {
        //         max_num = height[i];
        //         post_sum[i-1] = i;
        //     } else {
        //         post_sum[i-1] = post_sum[i];
        //     }
        // }
        // int max_pos = post_sum[0];
        // if (max_pos < 0) return 0; // for testcase [2, 0]
        // auto func = [&] (int max, vector<int>& arr) -> int {
        //     int pos = arr[max];
        //     int max_area = 0, anchor = -1;
        //     while (pos >= 0) {
        //         int area = height[pos] * abs(pos - max);
        //         if (area > max_area) {
        //             max_area = area;
        //             anchor = pos;
        //         }
        //         pos = arr[pos];
        //     }
        //     return anchor;
        // };
        // auto calc_area = [&] (int a, int b) -> int {
        //     if (a < 0 || b < 0) return -1;
        //     return min (height[a], height[b]) * abs (a - b);
        // };
        // int left_pos = func(max_pos, pre_sum);
        // int right_pos = func(max_pos, post_sum);
        // return max(0, max (calc_area(left_pos, right_pos), max (calc_area(left_pos, max_pos), calc_area(max_pos, right_pos))));

        // IMPROVE 1 — signed/unsigned, THIRD time: `int r = height.size() - 1;`.
        // Clean here only because the constraint guarantees n >= 2, exactly like
        // Two Sum II was clean only because of 1-indexing. The habit I keep flagging
        // is that you never reach for the defensive `(int)`. Write:
        //     int r = (int)height.size() - 1;
        // Make the cast deliberate so it's not "safe by luck of the constraints."
        // (notes/cpp/signed-unsigned-pitfalls.md)
        int l = 0, r = height.size() - 1;

        // IMPROVE 2 — declare `area` at first use, inside the loop, not hoisted
        // uninitialized up here. Same micro-habit as `int sum;` in Two Sum II.
        //     int area = ...;   // one line down, narrowest scope
        int area, max_area = 0;
        while (r > l) {
            // IMPROVE 3 — the `1ll` promotion is DEFEATED by storing into `int area`.
            // You promote the multiply to 64-bit to avoid overflow, then immediately
            // truncate the result back to 32-bit on assignment. If overflow were
            // real, this wouldn't save you — the guard has to extend to the storage
            // type (`long long area`). Good instinct (you thought about overflow),
            // incomplete execution. Here it's moot: max area = (1e5)*(1e4) = 1e9 <
            // INT_MAX (~2.1e9), so plain `int` is fine and the `1ll` can just go.
            //
            // IMPROVE 4 — `abs(r-l)` is redundant: the loop invariant is r > l, so
            // r - l is always positive. Just `(r - l)`.
            area = 1ll * abs(r-l) * min (height[l], height[r]);
            max_area = max (area, max_area);
            if (height[l] < height[r]) l++;   // discard the limiter — see README proof
            else r--;
        }
        return max_area;

        // GOOD — keep doing these:
        //   * Naming: l / r. Third clean solve in a row. The habit is fixed.
        //   * You *thought about overflow* at all — most people don't until it bites.
        //     Just make the guard reach the storage type next time.
        //   * You arrived here by proving the precompute approach can't be optimal,
        //     not by pattern-matching. That's the real win. See README.
        // Dead code above (the commented precompute attempt) should be deleted for an
        // interview submission — its "why it fails" reasoning now lives in the README.
    }
};
