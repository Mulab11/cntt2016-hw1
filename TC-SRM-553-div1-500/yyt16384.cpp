#include <algorithm>
#include <string>
#include <utility>
#include <vector>

class TwoConvexShapes {
  public:
    int countWays(std::vector<std::string> grid);

  private:
    static const int MOD = 1000000007;

    int countSequences(const std::vector<std::pair<int, int>> &a, int m);
};

int TwoConvexShapes::countWays(std::vector<std::string> grid)
{
    int n = grid.size();
    int m = grid[0].length();
    std::vector<std::pair<int, int>> a(n, {0, m});
    std::vector<std::pair<int, int>> ar(n, {0, m});
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'W') {
                a[i].first = std::max(a[i].first, j + 1);
                ar[i].first = std::max(ar[i].first, m - j);
            } else if (grid[i][j] == 'B') {
                a[i].second = std::min(a[i].second, j);
                ar[i].second = std::min(ar[i].second, m - j - 1);
            }
        }
    }
    int ans = 0;
    // Enumerate whether to flip the grid horizontally
    for (int p = 0; p < 2; p++) {
        // Enumerate whether to flip the grid vertically
        for (int q = 0; q < 2; q++) {
            std::vector<std::pair<int, int>> b(n);
            for (int i = 0; i < n; i++) {
                b[i] = (p ? ar : a)[q ? n - i - 1 : i];
            }
            ans = (ans + countSequences(b, m)) % MOD;
        }
    }
    // Remove duplicates
    for (int i = 0; i <= n; i++) {
        bool ok = true;
        for (int j = 0; j < n; j++) {
            if (j < i ? a[j].first > 0 || a[j].second < 0 : a[j].first > m || a[j].second < m) {
                ok = false;
                break;
            }
        }
        if (ok) {
            ans = (ans + MOD - 1) % MOD;
        }
    }
    for (int i = 0; i <= n; i++) {
        bool ok = true;
        for (int j = 0; j < n; j++) {
            if (j < i ? ar[j].first > m || ar[j].second < m : ar[j].first > 0 || ar[j].second < 0) {
                ok = false;
                break;
            }
        }
        if (ok) {
            ans = (ans + MOD - 1) % MOD;
        }
    }
    for (int i = 0; i <= m; i++) {
        bool ok = true;
        for (int j = 0; j < n; j++) {
            if (a[j].first > i || a[j].second < i) {
                ok = false;
                break;
            }
        }
        if (ok) {
            ans = (ans + MOD - 1) % MOD;
        }
    }
    for (int i = 0; i <= m; i++) {
        bool ok = true;
        for (int j = 0; j < n; j++) {
            if (ar[j].first > i || ar[j].second < i) {
                ok = false;
                break;
            }
        }
        if (ok) {
            ans = (ans + MOD - 1) % MOD;
        }
    }
    for (int i = 0; i < 2; i++) {
        bool ok = true;
        for (int j = 0; j < n; j++) {
            if ((i ? ar : a)[j].first > (i ? m : 0) || (i ? ar : a)[j].second < (i ? m : 0)) {
                ok = false;
                break;
            }
        }
        if (ok) {
            ans = (ans + 1) % MOD;
        }
    }
    return ans;
}

int TwoConvexShapes::countSequences(const std::vector<std::pair<int, int>> &a, int m)
{
    // f[i] = number of ways to end the delimiter in column i
    std::vector<int> f(m + 1);
    f[0] = 1;
    for (auto x : a) {
        std::vector<int> g(m + 1);
        for (int j = 0; j <= m; j++) {
            for (int k = std::max(j, x.first); k <= x.second; k++) {
                g[k] = (g[k] + f[j]) % MOD;
            }
        }
        f = std::move(g);
    }
    int ans = 0;
    for (int i = 0; i <= m; i++) {
        ans = (ans + f[i]) % MOD;
    }
    return ans;
}
