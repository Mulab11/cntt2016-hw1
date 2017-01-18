#line 2 "ArcadeManao.cpp"
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
bool vis[maxn][maxn]; // vis[i][j]表示(i, j)是否可达
int qh, qt, n, m; // qh, qt是队头/尾，n, m是矩形的长宽
pii q[maxn * maxn]; // bfs队列
class ArcadeManao {
	public:
		int shortestLadder(vector <string> g, int R, int C) {
			n = g.size(); m = g[0].size(); --R; --C;
			if (R == n - 1) return 0;
			for (int L = 0; L <= n; ++L) { // 从小到大枚举梯子长度
				cl(vis); qh = 1; qt = 0; 
				for (int i = 0; i < m; ++i) { // 初始可达的是地上的点
					vis[n - 1][i] = 1; q[++qt] = mp(n - 1, i);
				}
				while (qh <= qt) { // bfs
					int x = q[qh].fr, y = q[qh].sc; ++qh;
					if (x == R && y == C) return L; // 达到目的地
					if (y > 0 && g[x][y - 1] == 'X' && !vis[x][y - 1]) { // 往两边走
						vis[x][y - 1] = 1;
						q[++qt] = mp(x, y - 1);
					}
					if (y < m - 1 && g[x][y + 1] == 'X' && !vis[x][y + 1]) {
						vis[x][y + 1] = 1;
						q[++qt] = mp(x, y + 1);
					}
					for (int i = -L; i <= L; ++i) { // 用梯子走
						if (x + i >= 0 && x + i < n && g[x + i][y] == 'X' && !vis[x + i][y]) {
							vis[x + i][y] = 1;
							q[++qt] = mp(x + i, y);
						}
					}
				}
			}
		}
};
