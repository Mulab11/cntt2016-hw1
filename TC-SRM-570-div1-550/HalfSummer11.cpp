#line 2 "CentaurCompany.cpp"
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
#define maxn 50
typedef long long ll;
using namespace std;
double f[maxn][maxn][maxn][2], G[2][maxn][maxn][maxn]; // f[x][i][j][k]表示以x为根的子树中，有i个点被选出，形成了j个连通块，且x是否被选出的状态为k 的概率. G是一个滚动数组,now[i][j][k]表示前若干个子树中共选出i个点，形成了j个连通块，且这些子树中根被选出的有k个 的概率
int O;
#define now G[O]
#define lst G[O ^ 1] 
int n, g[maxn], ei, size[maxn]; // 边表
struct edge{
	int t, nxt;
}e[maxn * 2];
void ae(int a, int b) {
	e[++ei].t = b; e[ei].nxt = g[a]; g[a] = ei;
}
void dfs(int x, int fa) {
	size[x] = 0;
	for (int i = g[x]; i; i = e[i].nxt)
		if (e[i].t != fa) dfs(e[i].t, x);
	cl(G); now[0][0][0] = 1; 
	int scnt = 0;
	for (int i = g[x]; i; i = e[i].nxt)
		if (e[i].t != fa) { // 枚举每个儿子
			O ^= 1; cl(now);
			for (int j = 0; j <= size[e[i].t]; ++j) // 儿子子树里被选出的点数
				for (int k = 0; k <= j; ++k) // 儿子子树里选出点形成的连通块数
					for (int p = 0; p <= 1; ++p) // 儿子是否被选出
						for (int jj = 0; jj <= size[x]; ++jj) // 前若干个儿子子树里选出的总点数
							for (int kk = 0; kk <= jj; ++kk) // 前若干个儿子子树里形成的总连通块数
								for (int pp = 0; pp <= scnt; ++pp) // 前若干个儿子里被选出的个数
									now[jj + j][kk + k][pp + p] += lst[jj][kk][pp] * f[e[i].t][j][k][p];
			++scnt; size[x] += size[e[i].t];
		}
	++size[x];
	for (int i = 0; i < size[x]; ++i)
		for (int j = 0; j <= i; ++j)
			for (int k = 0; k <= min(scnt, j); ++k) {
				f[x][i][j][0] += 0.5 * now[i][j][k]; // 有0.5的概率x不被选出
				f[x][i + 1][j - k + 1][1] += 0.5 * now[i][j][k]; // 有0.5的概率x被选出，此时，它把k个被选出儿子所在的连通块连成了一个，故向j - k + 1贡献
			}
}
class CentaurCompany {
	public:
		double getvalue(vector <int> a, vector <int> b) {
			cl(f); cl(g); ei = 0; n = a.size() + 1;
			for (int i = 0; i < n - 1; ++i)
				ae(a[i], b[i]), ae(b[i], a[i]);
			dfs(1, -1);
			double ans = 0;
			for (int i = 0; i <= n; ++i)
				for (int j = 0; j <= i; ++j)
					ans += max(0, 2 * j - 2 - i) * (f[1][i][j][0] + f[1][i][j][1]); // 当有i个点，j个连通块时，需要2j - 2个接口，至少需要增加max(2 * j - 2 - i, 0)个接口。可以证明只需要增加这么多。
			return ans * 2; // 两个公司的情况是一样的，把它们各自的期望花费加起来就是答案
		}
};
