#include <algorithm>
#include <array>
#include <queue>
#include <string>
#include <utility>
#include <vector>

class EqualSums {
  public:
    int count(std::vector<std::string> board);

  private:
    static const int MOD = 1000000007;
    static const int MAXCVAL = 10;
};

int EqualSums::count(std::vector<std::string> board)
{
    int n = board.size();
    int m = board[0].length();
    std::vector<int> c;
    std::vector<std::vector<char>> vis(n, std::vector<char>(m));
    std::vector<std::vector<std::pair<int, int>>> xyval(n, std::vector<std::pair<int, int>>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (board[i][j] != '-' && !vis[i][j]) {
                std::queue<std::pair<int, int>> que;
                que.push(std::make_pair(i, j));
                vis[i][j] = true;
                xyval[i][j] = std::make_pair(board[i][j] - '0', 0);
                int minxval = board[i][j] - '0';
                int minyval = 0;
                while (!que.empty()) {
                    auto p = que.front();
                    que.pop();
                    int x = p.first;
                    int y = p.second;
                    minxval = std::min(minxval, xyval[x][y].first);
                    minyval = std::min(minyval, xyval[x][y].second);
                    for (int k = 0; k < n; k++) {
                        if (board[k][y] != '-') {
                            if (!vis[k][y]) {
                                vis[k][y] = true;
                                xyval[k][y] = std::make_pair(board[k][y] - '0' - xyval[x][y].second, xyval[x][y].second);
                                que.push(std::make_pair(k, y));
                            } else if (xyval[k][y].second != xyval[x][y].second) {
                                // Given board conflicts with itself
                                return 0;
                            }
                        }
                    }
                    for (int k = 0; k < m; k++) {
                        if (board[x][k] != '-') {
                            if (!vis[x][k]) {
                                vis[x][k] = true;
                                xyval[x][k] = std::make_pair(xyval[x][y].first, board[x][k] - '0' - xyval[x][y].first);
                                que.push(std::make_pair(x, k));
                            } else if (xyval[x][k].first != xyval[x][y].first) {
                                // Given board conflicts with itself
                                return 0;
                            }
                        }
                    }
                }
                if (minxval + minyval < 0) {
                    // Negative numbers are disallowed
                    return 0;
                }
                c.push_back(minxval + minyval);
            }
        }
    }
    // f[i] = number of ways to merge current blocks to get a block with
    // minimum value i
    std::array<int, MAXCVAL> f = {0};
    f[c[0]] = 1;
    for (int i = 1; i < (int)c.size(); i++) {
        int x = c[i];
        std::array<int, MAXCVAL> g = {0};
        for (int j = 0; j < MAXCVAL; j++) {
            for (int k = 0; k <= j + x; k++) {
                int p = std::min({j, x, k, j + x - k});
                if (p >= 0) {
                    g[p] = (g[p] + f[j]) % MOD;
                }
            }
        }
        f = g;
    }
    int ans = 0;
    for (auto x : f) {
        ans = (ans + x) % MOD;
    }
    return ans;
}
