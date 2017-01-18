#line 2 "CoinsGame.cpp"
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
#define maxn 45
#define maxm 1650
#define mo 1000000009
typedef long long ll;
using namespace std;
/*
   用总数 - 不合法的情况
   不合法的情况有：
   1. 所有的棋子都不能掉下去，2 ^ m
   2. 棋子个数不超过1, n种情况。没有棋子 / 有一个被围住的棋子在1中考虑过
   3. 所有的棋子都可以掉下去，并且必须同时掉下去。考虑每对棋子之间的关系，如果必须同时掉下去，就连边。只要选中的棋子都属于同一个连通块，它们就是必须同时掉下去的。方案数为2 ^ c - c - 1, 从c个点中选出至少两个点。
*/
const int dx[] = {0, 1, 0, -1}; // 四个移动方向
const int dy[] = {1, 0, -1, 0};
int n, m, k, r, c, num[maxn][maxn]; // n是可以掉下去的硬币位置个数，m是被围在障碍里的位置个数，k是棋盘周围的位置个数，r/c是棋盘的尺寸，num[i][j] = 0表示位置(i, j)是障碍，否则表示位置(i, j)的编号
int px[maxm], py[maxm], bx[maxm], by[maxm]; // px,py[i]是第i个空位的坐标,bx,by[i]是第i个边缘位置的坐标
bool col[maxn][maxn]; // col[i][j]表示位置(i, j)是否与边缘连通
bool good[maxm][maxm], vis[maxm]; // good[i][j]表示一对格子(i, j)上放置的棋子，能否通过某种移动方式，使得其中一个留在棋盘上，另一个掉下去，vis[i]用于之后的统计，表示第i个位置有没有被访问过
int q[maxn * maxn * maxn * maxn], qh, qt; // bfs用的队列
void add(int &a, int b) {
	a += b; a %= mo;
}
void color(int x, int y) { // 搜出所有可以move出棋盘的位置
	if (col[x][y]) return;
	col[x][y] = 1;
	for (int d = 0; d < 4; ++d) {
		int nx = x + dx[d], ny = y + dy[d];
		if (nx < 0 || ny < 0 || nx >= r || ny >= c || !num[nx][ny]) continue;
		color(nx, ny);
	}
}
int power(int a, int b) { // a ^ b
	int c = 1;
	for (; b; b >>= 1, a = 1ll * a * a % mo)
		if (b & 1) c = 1ll * c * a % mo;
	return c;
}
void check(int x1, int y1, int x2, int y2) { // 检查一个棋子在(x1, y1), 一个在(x2, y2)这种情况的合法性，并加入队列
	if (x1 < 0 || x1 >= r || x2 < 0 || x2 >= r || y1 < 0 || y1 >= c || y2 < 0 || y2 >= c) return; // 超出范围
	if (!num[x1][y1] || !num[x2][y2]) return; // 障碍
	if (x1 == x2 && y1 == y2) return; 
	if (good[num[x1][y1]][num[x2][y2]]) return; // 已经访问过这个位置，不必再加入队伍
	good[num[x1][y1]][num[x2][y2]] = good[num[x2][y2]][num[x1][y1]] = 1;
	q[++qt] = ((((x1 << 6) | y1) << 12) | ((x2 << 6) | y2));
}
int count(int x) { // dfs搜出某个位置所在连通块的大小
	vis[x] = 1; int ret = 1;
	for (int i = 1; i <= n + m; ++i)
		if (col[px[i]][py[i]] && !good[x][i] && !vis[i]) // 需要是一个能掉下去的位置，并且这个位置上的棋子必须与x同时掉下
			ret += count(i);
	return ret;
}
class CoinsGame {
	public:
		int ways(vector <string> board) {
			cl(num); cl(col); cl(good); cl(vis); n = m = k = 0;
			r = board.size(); c = board[0].size();
			for (int i = 0; i < r; ++i)
				for (int j = 0; j < c; ++j)
					if (board[i][j] != '#')
						num[i][j] = ++n, px[n] = i, py[n] = j;
			int ans = power(2, n); // 所有的方案数
			for (int i = 0; i < r; ++i) { // 从边缘的每个位置开始搜，搜出所有能够掉下去的位置
				if (num[i][0]) color(i, 0);
				if (num[i][c - 1]) color(i, c - 1);
			}
			for (int i = 0; i < c; ++i) {
				if (num[0][i]) color(0, i);
				if (num[r - 1][i]) color(r - 1, i);
			}
			for (int i = 0; i < r; ++i)
				for (int j = 0; j < c; ++j)
					if (col[i][j]) ++m, --n;
			swap(n, m); // n是能掉下去的位置，m是被围住的位置
			add(ans, mo - power(2, m)); // 2 ^ m种谁都掉不下去的情况
			add(ans, mo - n); // n种棋子个数只有一个的情况
			// 考虑一对可以不同时掉下去的棋子，存在一个时刻，其中一个掉下去了——相当于处于棋盘外面的一圈位置上，一个在棋盘上。枚举这个时刻时两个棋子的位置，再倒推回去，标记所有合法的棋子对
			for (int i = 0; i < r; ++i) { // 把棋盘外面的一圈位置记下来
				bx[++k] = i; by[k] = -1;
				bx[++k] = i; by[k] = c;
			}
			for (int i = 0; i < c; ++i) {
				by[++k] = i; bx[k] = -1;
				by[++k] = i; bx[k] = r;
			}
			for (int i = 1; i <= n + m; ++i) {
				if (!col[px[i]][py[i]]) continue;
				for (int j = 1; j <= k; ++j) { // 枚举一对合法棋子中的一个掉下去时的情况
					int sta, cx1, cy1, cx2, cy2, nx1, ny1, nx2, ny2, fx1, fy1, fx2, fy2;
					q[qh = qt = 1] = 0; 
					while (qh <= qt) {
						sta = q[qh++];
						if (qh == 2) {
							cx1 = px[i]; cy1 = py[i];
							cx2 = bx[j]; cy2 = by[j];
						} else {
							cy2 = (sta & 63); sta >>= 6;
							cx2 = (sta & 63); sta >>= 6;
							cy1 = (sta & 63); sta >>= 6;
							cx1 = (sta & 63); 
						}
						for (int d = 0; d < 4; ++d) { // 考虑上一步移动的方向
							fx1 = cx1 + dx[(d + 2) % 4]; fy1 = cy1 + dy[(d + 2) % 4]; // 反方向的格子
							fx2 = cx2 + dx[(d + 2) % 4]; fy2 = cy2 + dy[(d + 2) % 4];
							nx1 = cx1 + dx[d]; ny1 = cy1 + dy[d]; nx2 = cx2 + dx[d]; ny2 = cy2 + dy[d];
							check(nx1, ny1, nx2, ny2); // 两个棋子都移动了
							if (fx1 >= 0 && fx1 < r && fy1 >= 0 && fy1 < c && !num[fx1][fy1]) // 可能出现第一个棋子碰到障碍，没有继续前进的情况
								check(cx1, cy1, nx2, ny2);
							if (fx2 >= 0 && fx2 < r && fy2 >= 0 && fy2 < c && !num[fx2][fy2])
								check(nx1, ny1, cx2, cy2);
						}
					}
				}
			}
			for (int i = 1; i <= n + m; ++i) {
				if (vis[i] || !col[px[i]][py[i]]) continue;
				int c = count(i); // 大小为c的这些位置上的棋子，必须同时掉落
				add(ans, mo - power(2, c)); // 子集个数
				add(ans, 1 + c); // 去掉大小不足2的子集
			}
			return ans;
		}
};
