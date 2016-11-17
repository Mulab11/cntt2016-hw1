#include <algorithm>
#include <array>
#include <string>
#include <utility>
#include <vector>

static const int INF = 0x3f3f3f3f;

class EllysChessboard {
  public:
    int minCost(std::vector<std::string> board);

  private:
    static const int BOARDSZ = 8;
};

int EllysChessboard::minCost(std::vector<std::string> board)
{
    std::vector<std::pair<int, int>> a;
    for (int i = 0; i < BOARDSZ; i++) {
        for (int j = 0; j < BOARDSZ; j++) {
            if (board[i][j] == '#') {
                a.push_back(std::make_pair(i + j, i + BOARDSZ - j - 1));
            }
        }
    }
    if (a.empty()) {
        return 0;
    }
    // f[i][j][p][q] = minimum cost to place all pebbles with i <= x <=
    // j, p <= y <= q
    std::array<std::array<std::array<std::array<int, 2 * BOARDSZ>, 2 * BOARDSZ>, 2 * BOARDSZ>, 2 * BOARDSZ> f;
    std::fill_n(&f[0][0][0][0], 2 * BOARDSZ * 2 * BOARDSZ * 2 * BOARDSZ * 2 * BOARDSZ, INF);
    for (auto x : a) {
        f[x.first][x.first][x.second][x.second] = 0;
    }
    int ans = INF;
    for (int i = 2 * BOARDSZ - 1; i >= 0; i--) {
        for (int j = i; j < 2 * BOARDSZ; j++) {
            for (int p = 2 * BOARDSZ - 1; p >= 0; p--) {
                for (int q = p; q < 2 * BOARDSZ; q++) {
                    std::vector<std::pair<int, int>> rem;
                    for (auto x : a) {
                        if (x.first < i || x.first > j || x.second < p || x.second > q) {
                            rem.push_back(x);
                        }
                    }
                    if (rem.empty()) {
                        ans = std::min(ans, f[i][j][p][q]);
                        continue;
                    }
                    for (auto x : rem) {
                        int ni = std::min(i, x.first);
                        int nj = std::max(j, x.first);
                        int np = std::min(p, x.second);
                        int nq = std::max(q, x.second);
                        int cost = 0;
                        for (auto y : rem) {
                            if (y.first >= ni && y.first <= nj && y.second >= np && y.second <= nq) {
                                cost += std::max({y.first - ni, nj - y.first, y.second - np, nq - y.second});
                            }
                        }
                        f[ni][nj][np][nq] = std::min(f[ni][nj][np][nq], f[i][j][p][q] + cost);
                    }
                }
            }
        }
    }
    return ans;
}
