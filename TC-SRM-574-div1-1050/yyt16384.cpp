#include <algorithm>
#include <string>
#include <utility>
#include <vector>

static const int INF = 0x3f3f3f3f;

class Tunnels {
  public:
    int minimumTunnels(std::vector<std::string> frame);

  private:
    int maximumPairs(const std::vector<int> &a, const std::vector<int> &b);
};

int Tunnels::minimumTunnels(std::vector<std::string> frame)
{
    static const int DIRS[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    int n = frame.size();
    int m = frame[0].length();
    int cnt = 0;
    std::vector<int> cl(n, -1);
    std::vector<int> cr(n, -1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (frame[i][j] == 'X') {
                int adjcnt = 0;
                for (int k = 0; k < 4; k++) {
                    int x = i + DIRS[k][0];
                    int y = j + DIRS[k][1];
                    if (x >= 0 && x < n && y >= 0 && y < m && frame[x][y] == 'X') {
                        adjcnt++;
                    }
                }
                if (adjcnt == 1) {
                    // A endpoint
                    cnt++;
                } else if (adjcnt == 0) {
                    // A length-1 tunnel part
                    cnt += 2;
                }
                if (adjcnt <= 1 && (j == 0 || j == m - 1) && !(i > 1 && (j == 0 ? cl[i - 1] : cr[i - 1]) != -1)) {
                    int dy = j == 0 ? 1 : -1;
                    int y = j;
                    while (y >= 0 && y < m && frame[i][y] == 'X') {
                        y += dy;
                    }
                    y -= dy;
                    int val;
                    if (i > 0 && frame[i - 1][y] == 'X') {
                        // Can connect downwards
                        val = 0;
                    } else if (i < n - 1 && frame[i + 1][y] == 'X') {
                        // Can connect upwards
                        val = 1;
                    } else if (y == m - j - 1) {
                        // Special connection method
                        val = 2;
                    } else if (i == 0) {
                        // Can connect downwards or upwards, but
                        // connecting downwards is better
                        val = 0;
                    } else {
                        // Can connect upwards
                        val = 1;
                    }
                    if (j == 0) {
                        cl[i] = val;
                    } else {
                        cr[i] = val;
                    }
                }
            }
        }
    }
    if (m == 1) {
        // Special case
        return cnt ? 1 : 0;
    }
    return cnt / 2 - maximumPairs(cl, cr);
}

int Tunnels::maximumPairs(const std::vector<int> &a, const std::vector<int> &b)
{
    int n = a.size();
    // f[i][j] = maximum number of pairs when sequence a has i unmatched
    // left brackets and sequence b has j unmatched left brackets
    std::vector<std::vector<int>> f(n + 1, std::vector<int>(n + 1, -INF));
    f[0][0] = 0;
    for (int i = 0; i < n; i++) {
        std::vector<std::vector<int>> g(n + 1, std::vector<int>(n + 1, -INF));
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k <= n; k++) {
                if (f[j][k] >= 0) {
                    int nj;
                    int nk;
                    int w;
                    if (a[i] != 2) {
                        nj = std::max(j + (a[i] == -1 ? 0 : (a[i] ? -1 : 1)), 0);
                        nk = std::max(k + (b[i] == -1 ? 0 : (b[i] ? -1 : 1)), 0);
                        w = (a[i] == 1 && j) + (b[i] == 1 && k);
                        g[nj][nk] = std::max(f[nj][nk], f[j][k] + w);
                    } else {
                        // Turn a[i] and b[i] into one left bracket and
                        // one right bracket
                        nj = j + 1;
                        nk = std::max(k - 1, 0);
                        w = k > 0;
                        g[nj][nk] = std::max(f[nj][nk], f[j][k] + w);
                        nj = std::max(j - 1, 0);
                        nk = k + 1;
                        w = j > 0;
                        g[nj][nk] = std::max(f[nj][nk], f[j][k] + w);
                    }
                }
            }
        }
        f = std::move(g);
    }
    int ans = 0;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            ans = std::max(ans, f[i][j]);
        }
    }
    return ans;
}
