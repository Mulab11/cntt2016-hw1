#line 2 "EqualSums.cpp"
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
#define maxn 120
#define mo 1000000007
typedef long long ll;
using namespace std;
int n, g[maxn], ei;
struct edge{
	int t, w, nxt;
}e[maxn * maxn];
void ae(int a, int b, int c) {
	e[++ei].t = b; e[ei].nxt = g[a]; g[a] = ei; e[ei].w = c;
}
int p[maxn], q[maxn], vis[maxn]; // 对于一个连通块，设里面编号最小的元素为a，则其中所有的元素x[i]都能表示为p[i] * a + q[i]的形式；vis[i]标记一个点是否被访问过
int ans, L, R, flag; // ans是答案，L，R是根据连通块内的情况，确定的a的上下界，flag表示矩阵是否已经是不合法的
void dfs(int x) { // 弄出a所在连通块
	vis[x] = 1;
	if (p[x] > 0) 
		L = max(L, -q[x]); // a + q[x] >= 0, a >= -q[x]
	else 
		R = min(R, q[x]); // q[x] - a >= 0, a <= q[x]
	for (int i = g[x]; i; i = e[i].nxt)
		if (vis[e[i].t]) {
			if (p[x] + p[e[i].t] != 0 || q[x] + q[e[i].t] != e[i].w) { // 条件出现了矛盾，这个矩阵已经不合法
				flag = 0; break;
			}
		} else {
			p[e[i].t] = -p[x]; q[e[i].t] = e[i].w - q[x]; // 根据x + e[i].t = e[i].w，表示出e[i].t
			dfs(e[i].t);
		}
}
class EqualSums {
	public:
		int count(vector <string> board) {
			cl(g); ei = 0; cl(vis);
			ans = 1; 
			n = board.size();
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < n; ++j)
					if (board[i][j] != '-') {
						ae(i, j + n, board[i][j] - '0'); // 添加和为w的限制
						ae(j + n, i, board[i][j] - '0');
					}
			flag = 1; int del = 1; // del记录min{x} > 0的方案数，需要从ans中减去
			for (int i = 0; i < 2 * n; ++i)
				if (!vis[i]) {
					p[i] = 1; q[i] = 0;
					L = 0; R = +oo;
					dfs(i); // dfs i 所在连通块，get 元素i的取值范围[L, R]
					if (!flag) return 0;
					if (L <= R) 
						ans = 1ll * ans * (R - L + 1) % mo;
					else
						ans = 0;
					++L; // 需要去掉min{x} > 0的情况，所有a + q[x] >= 1, 下限L恰好增加1
					if (L <= R)
						del = 1ll * del * (R - L + 1) % mo;
					else
						del = 0;
				}
			ans = (ans + mo - del) % mo;
			return ans;
		}
};
