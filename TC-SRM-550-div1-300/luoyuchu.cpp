#include <bits/stdc++.h>

using namespace std;

#define dig(...) fprintf(stderr, __VA_ARGS__)
template <class TAT>
inline void Ckmin(TAT &a, const TAT &b)
{
	if (a > b) a = b;
}
template <class TAT>
inline void Ckmax(TAT &a, const TAT &b)
{
	if (a < b) a = b;
}
typedef long long LL;

const int maxn = 255;
const int walk[4][2] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};//可以走的四个方向

int n;
int mat[maxn][maxn];//网格

class RotatingBot {
    public:
    int minArea(vector<int> moves) {
        int x = 125, y = 125, dir = 0;
        n = moves.size();
        memset(mat, 0, sizeof(mat));
        mat[x][y] = 1;
        for (int i = 0; i < n; ++i) {//先模拟走出轨迹
            for (int j = 1; j <= moves[i]; ++j) {
                x += walk[dir][0];
                y += walk[dir][1];
                if (mat[x][y] == 1) return -1;//判断是否有格子走了两遍
                mat[x][y] = 1;
            }
            dir = (dir + 1) % 4;
        }
        int Maxx = -2e9, Maxy = -2e9, Minx = 2e9, Miny = 2e9;
        for (int i = 0; i < maxn; ++i) {//统计实际网格的最小边界
            for (int j = 0; j < maxn; ++j) {
                if (mat[i][j]) {
                    Ckmin(Minx, i);
                    Ckmax(Maxx, i);
                    Ckmin(Miny, j);
                    Ckmax(Maxy, j);
                }
            }
        }
        memset(mat, 0, sizeof(mat));
        for (int i = Minx - 1; i <= Maxx + 1; ++i) mat[i][Miny - 1] = mat[i][Maxy + 1] = 1;//将边界框出
        for (int i = Miny - 1; i <= Maxy + 1; ++i) mat[Minx - 1][i] = mat[Maxx + 1][i] = 1;
        x = 125; y = 125; dir = 0;
        mat[x][y] = 1;
        for (int i = 0; i < n; ++i) {
            for (int j = 1; j <= moves[i]; ++j) {
                x += walk[dir][0];
                y += walk[dir][1];
                if (mat[x][y] == 1) return -1;
                mat[x][y] = 1;
            }
            if (i != n - 1 && !mat[x + walk[dir][0]][y + walk[dir][1]]) return -1;//判断个是否在合法的时候转弯
            dir = (dir + 1) % 4;
        }
        return (Maxx - Minx + 1) * (Maxy - Miny + 1);//返回答案
    }
};
