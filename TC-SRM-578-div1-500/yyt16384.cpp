#include <algorithm>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

class WolfInZooDivOne {
  public:
    int count(int N, std::vector<std::string> L, std::vector<std::string> R);

  private:
    static const int MOD = 1000000007;

    int count2(int n, const std::vector<int> &left, const std::vector<int> &right);
};

int WolfInZooDivOne::count(int N, std::vector<std::string> L, std::vector<std::string> R)
{
    std::string sl;
    for (const auto &x : L) {
        sl += x;
    }
    std::string sr;
    for (const auto &x : R) {
        sr += x;
    }
    int val;
    std::vector<int> left;
    std::istringstream ssl(sl);
    while (ssl >> val) {
        left.push_back(val);
    }
    std::vector<int> right;
    std::istringstream ssr(sr);
    while (ssr >> val) {
        right.push_back(val);
    }
    return count2(N, left, right);
}

int WolfInZooDivOne::count2(int n, const std::vector<int> &left, const std::vector<int> &right)
{
    std::vector<int> rpos(n);
    for (int i = 0; i < n; i++) {
        rpos[i] = i;
    }
    for (int i = 0; i < (int)left.size(); i++) {
        for (int j = left[i]; j <= right[i]; j++) {
            rpos[j] = std::max(rpos[j], right[i] + 1);
        }
    }
    // f[i][j] = number of ways to get the state where there can be no
    // more wolves until position i, and at most one wolf until position
    // j
    std::vector<std::vector<int>> f(n + 1, std::vector<int>(n + 1));
    f[0][0] = 1;
    for (int i = 0; i < n; i++) {
        std::vector<std::vector<int>> g(n + 1, std::vector<int>(n + 1));
        for (int j = i; j <= n; j++) {
            for (int k = j; k <= n; k++) {
                int nextj;
                int nextk;
                nextj = std::max(j, i + 1);
                nextk = std::max(k, i + 1);
                g[nextj][nextk] = (g[nextj][nextk] + f[j][k]) % MOD;
                if (j == i) {
                    nextj = std::max(k, i + 1);
                    nextk = std::max(rpos[i], i + 1);
                    g[nextj][nextk] = (g[nextj][nextk] + f[j][k]) % MOD;
                }
            }
        }
        f = std::move(g);
    }
    return f[n][n];
}
