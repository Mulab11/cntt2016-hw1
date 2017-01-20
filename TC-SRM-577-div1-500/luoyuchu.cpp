#include <bits/stdc++.h>
using namespace std;

#define dig(...) fprintf(stderr, __VA_ARGS__)

template <class TAT>
void Ckmin(TAT &a, const TAT &b)
{
	if (a > b) a = b;
}
template <class TAT>

void Ckmax(TAT &a, const TAT &b)
{
	if (a < b) a = b;
}

typedef long long LL;

using namespace std;

const int maxn = 105;
const int maxm = 17;

int n;
struct Point
{
	int x, y;
	Point() {}
	Point(int _x, int _y):x(_x), y(_y) {}
}dot[maxn];
int f[maxm][maxm][maxm][maxm];

bool In(int a, int b, int c, int d, int p)
{
	return dot[p].x >= a && dot[p].x <= b && dot[p].y >= c && dot[p].y <= d;
}

int dist(int a, int b, int c, int d, int p)
{
	return max(dot[p].x - a, max(b - dot[p].x, max(dot[p].y - c, d - dot[p].y)));
}

int Solve()
{
	int ta, tb, tc, td, sum;
	memset(f, 0x3f, sizeof(f));//f[a][b][c][d]表示在已经变换过的坐标轴上，已经加入所有的x坐标在[a,b]，y坐标在[c,d]的点的最小代价
	for (int i = 1; i <= n; ++i) {
		f[dot[i].x][dot[i].x][dot[i].y][dot[i].y] = 0;
	}
	for (int a = 0; a < 15; ++a) {
		for (int b = 0; b + a < 15; ++b) {
			for (int c = 0; c < 15; ++c) {
				for (int d = 0; d + c < 15; ++d) {
					for (int i = 1; i <= n; ++i) {
						if (!In(b, a + b, d, c + d, i)) {//转移是由于知道了上下边界，所以可以直接转移
							ta = min(b, dot[i].x);
							tb = max(b + a, dot[i].x);
							tc = min(d, dot[i].y);
							td = max(d + c, dot[i].y);
							sum = dist(b, a + b, d, c + d, i);
							for (int j = 1; j <= n; ++j) {
								if (i != j && (!In(b, a + b, d, c + d, j)) && In(ta, tb, tc, td, j)) {
									sum += dist(ta, tb, tc, td, j);
								}
							}
							Ckmin(f[ta][tb][tc][td], f[b][a + b][d][c + d] + sum);
						}
					}
				}
			}
		}
	}
	ta = tb = dot[1].x;
	tc = td = dot[1].y;
	for (int i = 2; i <= n; ++i) {
		Ckmin(ta, dot[i].x);
		Ckmax(tb, dot[i].x);
		Ckmin(tc, dot[i].y);
		Ckmax(td, dot[i].y);
	}
	return f[ta][tb][tc][td];//返回答案
}

class EllysChessboard {
    public:
    int minCost(vector<string> board) {
		n = 0;
		for (int i = 0; i < (int)board.size(); ++i) {
			for (int j = 0; j < (int)board[i].length(); ++j) {
				if (board[i][j] == '#') {
					++n;
					dot[n].x = i + j;//将坐标轴旋转45度
					dot[n].y = i + 7 - j;
				}
			}
		}
		if (n <= 1) return 0;
		else return Solve();//Dp
    }
};
