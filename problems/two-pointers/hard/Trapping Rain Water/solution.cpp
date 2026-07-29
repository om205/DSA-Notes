using namespace std;

#define ll long long
#include <vector>
#include <algorithm> 

class Solution {
public:
    // APPROACH (yours — non-textbook, and clever):
    //   Water between a left wall `slow` and the next taller wall `fast` =
    //   (bounding rectangle) - (solid bars inside) = (fast-slow)*h[slow] - sum(h[slow..fast-1]).
    //   The "sum of solid bars" is a range-sum query → that's why the prefix-sum
    //   arrays pay off HERE (unlike Container, where precompute couldn't help).
    //   Left pass handles left-bounded water; right pass handles right-bounded.
    //   The strict/non-strict asymmetry (`<=` skip on the left, `<` skip on the
    //   right) makes equal-height walls get counted exactly once. Nice trick.
    int trap(vector<int>& height) {
        int len = height.size();
        vector<ll> pre_sum(len), post_sum(len);
        for (ll i = 0, sum = 0; i < len; ++i)      // ✅ fixed: both `ll` (can't mix types in one decl)
        pre_sum[i] = sum, sum += height[i];
        for (ll i = len-1, sum = 0; i >= 0; --i)
        post_sum[i] = sum, sum += height[i];

        // IMPROVE 1 — DEAD CODE. `max_pos` is computed here and never used again.
        // It's a leftover from an earlier design (split at the global max). Your
        // strict/non-strict asymmetry replaced the need for it. Delete these lines.
        // (You did the same with commented code in 3Sum and Container — habit worth
        // breaking: don't ship vestigial code.)
        int max_pos = 0;
        for (int i = 1; i < len; ++i) if (height[i] > height[max_pos]) max_pos = i;

        int slow = 0, fast = 1;
        ll vol = 0;
        while (fast < len) {
            if (height[fast] <= height[slow]) {
                fast++; continue;                  // ✅ fixed: block, not `fast++, continue` (continue is a statement)
            }
            // IMPROVE 2 — `abs()` here papers over signs you can PROVE. In this pass
            // fast > slow always, and pre_sum is non-decreasing (cumulative of
            // non-negatives), so both differences are already >= 0. Writing
            // `(fast - slow)` and `(pre_sum[fast] - pre_sum[slow])` is clearer and
            // tells a reviewer you know the invariant. abs = "I didn't track the sign."
            vol += 1ll * abs(fast - slow) * height[slow] - abs(pre_sum[fast] - pre_sum[slow]);
            slow = fast++;
        }
        slow = len - 1; fast = len - 2;
        while (fast >= 0) {
            if (height[fast] < height[slow]) {
                fast--; continue;
            }
            // Here fast < slow, so if you drop abs, write it as (slow - fast) and
            // (post_sum[fast] - post_sum[slow]) — post_sum DEcreases with index, so
            // post_sum[fast] >= post_sum[slow]. Know the direction, don't abs it.
            vol += 1ll * abs(fast - slow) * height[slow] - abs(post_sum[fast] - post_sum[slow]);
            slow = fast--;
        }
        return vol;
    }
    // GOOD — genuinely, call these out:
    //   * Overflow handled RIGHT this time: `1ll * ...` computes in 64-bit AND lands
    //     in `ll vol` — the wide type reaches storage. Contrast Container, where the
    //     `1ll` was defeated by an `int` accumulator. You fixed that habit.
    //   * You transferred the prefix-sum idea from Container to the problem where it
    //     actually decomposes. That's the whole decomposability lesson, applied.
    //   * The `<=` / `<` asymmetry to count shared/equal walls once — that's a subtle
    //     correctness insight most people miss and patch with an explicit max split.
    //
    // NOTE — space: this is O(n) (two prefix-sum arrays), NOT O(1). The canonical
    // two-pointer (track runningLeftMax/runningRightMax, add per-cell) is O(1) space.
    // Yours is a valid, arguably more original trade: O(n) space to add water in bulk
    // per segment instead of per cell. Know the O(1) version too — interviewers expect it.
};