#include <algorithm>
#include <queue>
#include <string>
#include <utility>
#include <vector>

class HexagonalBoard {
  public:
    int minColors(std::vector<std::string> board);
};

int HexagonalBoard::minColors(std::vector<std::string> board)
{
    static const int DIRS[6][2] = {{1, 0}, {0, 1}, {-1, 1}, {-1, 0}, {0, -1}, {1, -1}};
    int n = board.size();
    std::vector<std::vector<int>> col(n, std::vector<int>(n, -1));
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == 'X' && col[i][j] == -1) {
                // Try to color this connected component
                int anscur = 1;
                std::queue<std::pair<int, int>> que;
                que.push(std::make_pair(i, j));
                col[i][j] = 0;
                while (!que.empty()) {
                    std::pair<int, int> p = que.front();
                    que.pop();
                    int x = p.first;
                    int y = p.second;
                    for (int k = 0; k < 6; k++) {
                        int x2 = x + DIRS[k][0];
                        int y2 = y + DIRS[k][1];
                        if (x2 >= 0 && x2 < n && y2 >= 0 && y2 < n && board[x2][y2] == 'X') {
                            if (col[x2][y2] == -1) {
                                col[x2][y2] = col[x][y] ^ 1;
                                anscur = 2;
                                que.push(std::make_pair(x2, y2));
                            } else if (col[x2][y2] == col[x][y]) {
                                // Graph is not bipartite, answer is 3
                                return 3;
                            }
                        }
                    }
                }
                ans = std::max(ans, anscur);
            }
        }
    }
    return ans;
}
