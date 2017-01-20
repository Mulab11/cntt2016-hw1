#include <bits/stdc++.h>

#define dig(...) fprintf(stderr, __VA_ARGS__)

using namespace std;

template <class TAT>
void Ckmax(TAT &a, const TAT &b)
{
    if (a < b) a = b;
}
template <class TAT>
void Ckmin(TAT &a, const TAT &b)
{
    if (a > b) a = b;
}

typedef long long LL;

const int maxn = 55;

int n;
bool B[maxn][maxn];
bool color[maxn][maxn];
bool vis[maxn][maxn];
bool FAIL = 0;

void Dfs(int x, int y, int c)
{
    if (vis[x][y] == 1) {
        if (color[x][y] != c) FAIL = 1;
        return;
    }
    vis[x][y] = 1;
    color[x][y] = c;
    if (B[x - 1][y]) Dfs(x - 1, y, c ^ 1);
    if (B[x - 1][y + 1]) Dfs(x - 1, y + 1, c ^ 1);
    if (B[x][y - 1]) Dfs(x, y - 1, c ^ 1);
    if (B[x][y + 1]) Dfs(x, y + 1, c ^ 1);
    if (B[x + 1][y - 1]) Dfs(x + 1, y - 1, c ^ 1);
    if (B[x + 1][y]) Dfs(x + 1, y, c ^ 1);
}

bool Check()
{
    FAIL = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (B[i][j] && !vis[i][j]) {
                Dfs(i, j, 0);
            }
        }
    }
    return (FAIL == 0);
}

class HexagonalBoard {
    public:
    int minColors(vector<string> board) {
        int Ans = 0;
        n = board.size(); 
        memset(B, 0, sizeof(B));
        memset(vis, 0, sizeof(vis));
        memset(color, 0, sizeof(color));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                B[i + 1][j + 1] = (board[i][j] == 'X');
            }
        }
        for (int i = 1; i <= n; ++i) {//如果没有染色格子，答案为0,如果没有相邻的染色格子，答案为1,如果不是二分图，则答案为3,否则为2
            for (int j = 1; j <= n; ++j) {
                if (B[i][j]) {
                    Ckmax(Ans, 1);
                    if (B[i - 1][j] || B[i - 1][j + 1] || B[i][j - 1]) Ckmax(Ans, 2);
                    if (B[i - 1][j] && B[i - 1][j + 1]) Ckmax(Ans, 3);
                    if (B[i][j - 1] && B[i - 1][j]) Ckmax(Ans, 3);
                }
            }
        }
        if (Ans == 2) {
            if (Check() == 0) Ans = 3;
        }
        return Ans;
    }
};
