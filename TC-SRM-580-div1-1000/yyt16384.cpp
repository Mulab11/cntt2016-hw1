#include <algorithm>
#include <string>
#include <vector>

static const int INF = 0x3f3f3f3f;

class WallGameDiv1 {
  public:
    int play(std::vector<std::string> costs);
};

int WallGameDiv1::play(std::vector<std::string> costs)
{
    int m = costs[0].length();
    // g[i] = total cost starting when Rabbit reaches this row at column
    // i
    std::vector<int> g(m);
    for (int i = 0; i < m; i++) {
        g[i] = costs.back()[i] - '0';
    }
    for (int p = costs.size() - 2; p >= 0; p--) {
        std::vector<int> sumcost(m + 1);
        for (int i = 0; i < m; i++) {
            sumcost[i + 1] = sumcost[i] + costs[p][i] - '0';
        }
        // f[i][j] = total cost starting from current line, Rabbit is in
        // column i, and columns in range [min(i, j), max(i, j)] have
        // walls
        std::vector<std::vector<int>> f(m, std::vector<int>(m));
        // Filling whole row with walls is disallowed
        f[0][m - 1] = f[m - 1][0] = -INF;
        for (int l = m - 2; l >= 0; l--) {
            for (int i = 0; i < m - l; i++) {
                int j = i + l;
                // Try to go down in the left
                int wleft = i == 0 ? INF : std::max(f[i - 1][j], g[i - 1]) + costs[p][i - 1] - '0';
                // Try to go down in the right
                int wright = j == m - 1 ? INF : std::max(f[j + 1][i], g[j + 1]) + costs[p][j + 1] - '0';
                f[i][j] = std::min(wleft, wright + sumcost[j + 1] - sumcost[i + 1]);
                f[j][i] = std::min(wleft + sumcost[j] - sumcost[i], wright);
            }
        }
        for (int i = 0; i < m; i++) {
            // Either create a wall to get f[i][i], or let Rabbit go
            // down and get g[i]
            g[i] = std::max(f[i][i], g[i]) + costs[p][i] - '0';
        }
    }
    int ans = INF;
    for (auto x : g) {
        ans = std::min(ans, x);
    }
    return ans;
}
