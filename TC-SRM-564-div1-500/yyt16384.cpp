#include <algorithm>

class AlternateColors2 {
  public:
    long long countWays(int n, int k);
};

long long AlternateColors2::countWays(int n, int k)
{
    long long ans = 0;
    // Enumerate the number of green balls
    for (int i = 0; i <= n; i++) {
        // There are still green and blue balls remaining after k steps
        if (k % 3 == 1 && (k + 2) / 3 <= i) {
            int minr = (k + 2) / 3;
            int maxr = n - i - (k + 2) / 3;
            if (minr <= maxr) {
                ans += maxr - minr + 1;
            }
        }
        // There are still one of green or blue balls remaining after k
        // steps
        if (k > 3 * i && (k - 3 * i) % 2 == 1) {
            int minr = (k - 3 * i + 1) / 2 + i;
            int maxr = n - i - (k - 3 * i + 1) / 2 - i;
            if (minr <= maxr) {
                ans += 2 * (maxr - minr + 1);
            }
        }
        // There are no green or blue balls remaining after k steps
        int minr = std::max(n - 2 * i, n + i - k + 1);
        int maxr = n - i;
        if (minr <= maxr) {
            ans += 2 * (maxr - minr + 1);
            if (minr == n - 2 * i) {
                ans--;
            }
        }
    }
    return ans;
}
