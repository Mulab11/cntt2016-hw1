#line 2 "EllysChessboard.cpp"
#include<vector>
#include<list>
#include<map>
#include<set>
#include<deque>
#include<stack>
#include<bitset>
#include<algorithm>
#include<functional>
#include<numeric>
#include<utility>
#include<sstream>
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<cstring>
#define cl(x) memset(x, 0, sizeof(x));
#define pii pair<int, int>
#define fr first
#define sc second
#define mp make_pair
#define pb push_back
#define oo 0x3f3f3f3f
#define maxn 17
typedef long long ll;
using namespace std;
/*
   将图旋转45°，曼哈顿距离变成了切比雪夫距离，可以发现先把一个矩形里的棋子放满，再往外扩张，是最优的。于是以矩形的坐标为状态进行dp即可，
*/
bool a[maxn][maxn]; // a[x][y] = 1 <==> 这个位置有棋子
int f[maxn][maxn][maxn][maxn]; // f[xl][xr][yl][yr]表示把xl <= x <= xr, yl <= y <= yr的棋子都放上所需要的最小代价
class EllysChessboard {
	public:
		int minCost(vector <string> board) {
			cl(a); memset(f, 0x3f, sizeof(f));
			bool has = 0;
			for (int i = 0; i < 8; ++i)
				for (int j = 0; j < 8; ++j)
					if (board[i][j] == '#') {
						a[i + j][i + 7 - j] = 1;
						f[i + j][i + j][i + 7 - j][i + 7 - j] = 0; // 第一个棋子代价为0
						has = 1;
					}
			if (!has) return 0; // 没有需要放的棋子
			for (int x = 0; x <= 14; ++x) // 枚举矩形的长宽
				for (int y = 0; y <= 14; ++y) 
					for (int xl = 0; xl + x <= 14; ++xl) // 枚举矩形左上角的位置
						for (int yl = 0; yl + y <= 14; ++yl) {
							int xr = xl + x, yr = yl + y;
							for (int d = 0; d < 4; ++d) { // 枚举扩展的方向
								int nxl = xl - (d == 0), nxr = xr + (d == 1), nyl = yl - (d == 2), nyr = yr + (d == 3); // 新矩形的坐标
								if (nxl < 0 || nyl < 0 || nxr > 14 || nyr > 14) continue;
								int sum = 0;
								if (d <= 1) {
									int nxt = (d == 0) ? nxl : nxr;
									for (int j = nyl; j <= nyr; ++j) // 对于扩充区域中的棋子，计算代价
										if (a[nxt][j]) sum += max(max(abs(nxt - nxl), abs(nxt - nxr)), max(abs(j - nyl), abs(j - nyr)));
								} else {
									int nxt = (d == 2) ? nyl : nyr;
									for (int j = nxl; j <= nxr; ++j) // 同理
										if (a[j][nxt]) sum += max(max(abs(nxt - nyl), abs(nxt - nyr)), max(abs(j - nxl), abs(j - nxr)));
								}
								f[nxl][nxr][nyl][nyr] = min(f[nxl][nxr][nyl][nyr], f[xl][xr][yl][yr] + sum);
							}
						}
			return f[0][14][0][14];
		}
};
