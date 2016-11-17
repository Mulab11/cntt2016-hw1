#include <algorithm>
#include <cstdlib>
#include <string>
#include <vector>

static const int INF = 0x3f3f3f3f;

class FoxAndFlowerShopDivOne {
  public:
    int theMaxFlowers(std::vector<std::string> flowers, int maxDiff);

  private:
    int maxFlowersLR(const std::vector<std::vector<char>> &a, int d);
};

int FoxAndFlowerShopDivOne::theMaxFlowers(std::vector<std::string> flowers, int maxDiff)
{
    int n = flowers.size();
    int m = flowers[0].length();
    std::vector<std::vector<char>> a(n, std::vector<char>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            a[i][j] = flowers[i][j] == '.' ? 0 : (flowers[i][j] == 'L' ? 1 : -1);
        }
    }
    int ans1 = maxFlowersLR(a, maxDiff);
    std::vector<std::vector<char>> b(m, std::vector<char>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            b[i][j] = flowers[j][i] == '.' ? 0 : (flowers[j][i] == 'L' ? 1 : -1);
        }
    }
    int ans2 = maxFlowersLR(b, maxDiff);
    int ans = std::max(ans1, ans2);
    return ans < 0 ? -1 : ans;
}

int FoxAndFlowerShopDivOne::maxFlowersLR(const std::vector<std::vector<char>> &a, int d)
{
    int n = a.size();
    int m = a[0].size();
    std::vector<std::vector<int>> sum(n + 1, std::vector<int>(m + 1));
    std::vector<std::vector<int>> sabs(n + 1, std::vector<int>(m + 1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            sum[i + 1][j + 1] = sum[i + 1][j] + sum[i][j + 1] - sum[i][j] + a[i][j];
            sabs[i + 1][j + 1] = sabs[i + 1][j] + sabs[i][j + 1] - sabs[i][j] + std::abs(a[i][j]);
        }
    }
    // fl[i][j] = maximum number of flowers chosen in the first i
    // columns with one rectangle and difference between the number of
    // two kinds of flowers = j - n * m
    std::vector<std::vector<int>> fl(m + 1, std::vector<int>(2 * n * m + 1, -INF));
    // fr[i][j] = maximum number of flowers chosen in the last n - i
    // columns with one rectangle and difference between the number of
    // two kinds of flowers = j - n * m
    std::vector<std::vector<int>> fr(m + 1, std::vector<int>(2 * n * m + 1, -INF));
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j <= m; j++) {
            for (int p = 0; p < n; p++) {
                for (int q = p + 1; q <= n; q++) {
                    int ss = sum[q][j] - sum[q][i] - sum[p][j] + sum[p][i];
                    int sa = sabs[q][j] - sabs[q][i] - sabs[p][j] + sabs[p][i];
                    fl[j][ss + n * m] = std::max(fl[j][ss + n * m], sa);
                    fr[i][ss + n * m] = std::max(fr[i][ss + n * m], sa);
                }
            }
        }
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j <= 2 * n * m; j++) {
            fl[i][j] = std::max(fl[i][j], fl[i - 1][j]);
        }
    }
    for (int i = m - 1; i >= 0; i--) {
        for (int j = 0; j <= 2 * n * m; j++) {
            fr[i][j] = std::max(fr[i][j], fr[i + 1][j]);
        }
    }
    // Enumerate a column between two rectangles
    int ans = -INF;
    for (int i = 1; i < m; i++) {
        for (int j = 0; j <= 2 * n * m; j++) {
            for (int k = 0; k <= 2 * n * m; k++) {
                if (std::abs(j + k - 2 * n * m) <= d) {
                    ans = std::max(ans, fl[i][j] + fr[i][k]);
                }
            }
        }
    }
    return ans;
}
