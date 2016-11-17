#include <algorithm>
#include <cstdlib>
#include <vector>

static const int INF = 0x3f3f3f3f;

class KingdomAndDice {
  public:
    double newFairness(std::vector<int> firstDie, std::vector<int> secondDie, int X);
};

double KingdomAndDice::newFairness(std::vector<int> firstDie, std::vector<int> secondDie, int X)
{
    int n = firstDie.size();
    std::vector<int> r = secondDie;
    std::sort(r.begin(), r.end());
    // cntempty[i] = number of unused values that are larger than i
    // values in secondDie
    std::vector<int> cntempty(n + 1);
    for (int i = 0; i <= n; i++) {
        cntempty[i] = (i == n ? X + 1 : r[i]) - (i == 0 ? 0 : r[i - 1]) - 1;
    }
    int cur = 0;
    int cnt0 = 0;
    for (auto x : firstDie) {
        if (x) {
            int s = std::lower_bound(r.begin(), r.end(), x) - r.begin();
            cntempty[s]--;
            cur += s;
        } else {
            cnt0++;
        }
    }
    // f[i] = minimum number of added numbers to get i/(n*n) chance of
    // winning
    std::vector<int> f(n * n + 1, INF);
    f[cur] = 0;
    for (int i = 1; i <= n; i++) {
        // Only cnt0 values are necessary
        for (int j = 0; j < cntempty[i] && j < cnt0; j++) {
            for (int k = n * n; k >= cur + i; k--) {
                f[k] = std::min(f[k], f[k - i] + 1);
            }
        }
    }
    int ans = cur;
    for (int i = cur; i <= n * n; i++) {
        if (f[i] <= cnt0 && std::abs(2 * i - n * n) < std::abs(2 * ans - n * n)) {
            ans = i;
        }
    }
    return (double)ans / (n * n);
}
