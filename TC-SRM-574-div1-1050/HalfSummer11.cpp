#line 2 "Tunnels.cpp"
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
#define maxn 60
typedef long long ll;
using namespace std;
/*
	找到图中的连通块，一些连通块可能在边界之外连起来。连通块总数 - 可以配对的连通块对数 = tunnel个数。
	能在边界之外连起来的连通块，首先都和左/右边界相邻，其次是它所在连通块中最上面/下面的一格，且从它开始能够一笔走完整个连通块。预处理lu[],ld[],ru[],rd[]分别表示某一行左端能否伸出去往上延伸，能否伸出去往下延伸。
	需要特殊处理宽度为1 / 有满的行 / 贴着边缘长度 <= 2的连通块。
	然后，就转化成两边一堆左右括号，挑出尽量多的组成合法的括号序列，这样一个问题。可以dp解决。
*/
int f[maxn][maxn][maxn]; // f[i][j][k]表示考虑前i行，左边的括号序列前缀和为j，右边的为k，此时最多的配对括号数。
bool lu[maxn], ld[maxn], ru[maxn], rd[maxn], lr[maxn]; // 表示某一行的左/右是否可以是一个左/右括号。lr[]表示这一行是否是满且孤立的。
int deg[maxn][maxn], col[maxn][maxn]; // deg[i][j]是(i, j)的度，col[i][j]是(i, j)所属连通块的标号
int n, m, mi[maxn * maxn], mx[maxn * maxn], cnt; // n,m是矩形长、宽.mi[c], mx[c]标记第c个连通块最上面/最下面一行的位置。cnt是连通块个数。
bool graph[maxn][maxn]; // graph[i][j] = 1表示(i, j)处是"X"
const int dx[] = {0, 1, 0, -1}; // 往四个方向移动
const int dy[] = {1, 0, -1, 0};
void color(int x, int y, int c) { // dfs出一个连通块
	col[x][y] = c; 
	mi[c] = min(mi[c], x); mx[c] = max(mx[c], x);
	for (int d = 0; d < 4; ++d) {
		int nx = x + dx[d], ny = y + dy[d];
		if (nx >= 0 && nx < n && ny >= 0 && ny < m && graph[nx][ny] && !col[nx][ny]) {
			++deg[x][y]; ++deg[nx][ny];
			color(nx, ny, c);
		}
	}
}
class Tunnels {
	public:
		int minimumTunnels(vector <string> frame) {
			cl(col); cnt = 0; cl(deg); cl(lu); cl(ld); cl(ru); cl(rd); cl(lr); cl(graph);
			n = frame.size(); m = frame[0].size();
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < m; ++j) 
					graph[i][j] = (frame[i][j] == 'X');
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < m; ++j) {
					if (frame[i][j] == 'X' && !col[i][j]) { // 找出所有的连通块
						++cnt; mi[cnt] = n; mx[cnt] = -1;
						color(i, j, cnt);
					}
				}
			if (!cnt) return 0; 
			if (m == 1) return 1; // 特判。此时一定可以把所有的连通块连起来。
			for (int i = 0; i < n; ++i) {
				if (graph[i][0] && i && mi[col[i][0]] == i && ((deg[i][0] & 1) || !deg[i][0])) lu[i] = 1; // 能往上延伸的条件：位于所在连通块的最上面一行，并且从它出发能一笔走完整个连通块(连通块只有它一个格子 / 它是连通块的一端).此外，若已经位于第0行，就没有往上延伸的意义了。
				if (graph[i][0] && mx[col[i][0]] == i && ((deg[i][0] & 1) || !deg[i][0])) ld[i] = 1; // 类似
				if (lu[i] && ld[i]) ld[i] = 0; // 如果必须往上延伸，就不能往下延伸。
				if (graph[i][m - 1] && i && mi[col[i][m - 1]] == i && ((deg[i][m - 1] & 1) || !deg[i][m - 1])) ru[i] = 1;
				if (graph[i][m - 1] && mx[col[i][m - 1]] == i && ((deg[i][m - 1] & 1) || !deg[i][m - 1])) rd[i] = 1;
				if (ru[i] && rd[i]) rd[i] = 0;
				lr[i] = 1;
				for (int j = 0; j < m; ++j)
					lr[i] &= graph[i][j]; // 这一行是满的
				lr[i] &= (mi[col[i][0]] == i && mx[col[i][0]] == i); // 连通块只有这一行
				if (lr[i]) ld[i] = lu[i] = rd[i] = ru[i] = 0; // 对于这种情况，两端首先都最多只能选一个方向延伸，这两个方向还不能相同，需要在dp时特殊考虑
			}
			for (int i = 0; i < n - 1; ++i) { // 处理边界上有相邻两个"X",且一个往上延伸，一个往下延伸的情况。如果都延伸，延伸的部分会相邻，不合法。所以强制不让下面的延伸。
				if (lu[i] && ld[i + 1]) ld[i + 1] = 0;
				if (ru[i] && rd[i + 1]) rd[i + 1] = 0;
			}
			memset(f, -0x3f, sizeof(f));
			f[0][0][0] = 0;
			for (int i = 0; i < n; ++i) 
				for (int x = 0; x <= i; ++x) // 左边的前缀和
					for (int y = 0; y <= i; ++y) // 右边的前缀和
						for (int l = -1; l <= 1; ++l) // 左边这行选择(/./)
							for (int r = -1; r <= 1; ++r) { // 右边这行选择(/./)
								if (l + x < 0 || r + y < 0) continue; // 括号序列要合法
								if (lr[i]) {
									if (l == r && !(l == 0 && i == 0)) continue; // 两边或者不同，或者两边都不延伸，且位于第一行
								} else {
									if (l == -1 && !lu[i]) continue; // 需要存在对应的括号
									if (l == 1 && !ld[i]) continue;
									if (r == -1 && !ru[i]) continue;
									if (r == 1 && !rd[i]) continue;
								}
								f[i + 1][x + l][y + r] = max(f[i + 1][x + l][y + r], f[i][x][y] + (l == -1) + (r == -1));
							}
			int ans = 0;
			for (int x = 0; x <= n; ++x)
				for (int y = 0; y <= n; ++y)
					ans = max(ans, f[n][x][y]);
			return cnt - ans;
		}
};
