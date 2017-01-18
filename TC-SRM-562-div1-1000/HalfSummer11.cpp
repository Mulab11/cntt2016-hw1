#line 2 "InducedSubgraphs.cpp"
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
#define mo 1000000009
typedef long long ll;
using namespace std;
int n, g[maxn], ei; // n是点数，g,ei是边表部分
int pre[maxn], size[maxn], f[maxn]; // pre[i]表示i在树上的父亲，size[i]表示以i为根的子树大小，f[i]表示以i为根的子树的不同拓扑序个数
bool vis[maxn]; // 标记一个点是否被访问过
int son[maxn], stot; // 枚举链的一端时，存放它的儿子
int fra[maxn], ifr[maxn]; // fra[i] = i!, ifr[i] = 1 / i!
struct edge {
	int t, nxt;
}e[maxn * 2];
void ae(int a, int b) {
	e[++ei].t = b; e[ei].nxt = g[a]; g[a] = ei;
}
void dfs(int x) { // 处理pre,size
	size[x] = 1;
	for (int i = g[x]; i; i = e[i].nxt)
		if (e[i].t != pre[x]) {
			pre[e[i].t] = x;
			dfs(e[i].t);
			size[x] += size[e[i].t];
		}
}
void add(int &a, int b) {
	a += b; a %= mo;
}
void dp(int x) { // 计算f
	size[x] = 1; vis[x] = 1; f[x] = 1;
	for (int i = g[x]; i; i = e[i].nxt) // 以x为根的子树的拓扑序中，x一定在第一个，剩下的就是把各个子树的拓扑序合并，不同的合并方式有size[x]! / size[son1]! / size[son2]! .. 这么多种
		if (!vis[e[i].t]) {
			dp(e[i].t);
			size[x] += size[e[i].t];
			f[x] = 1ll * f[x] * f[e[i].t] % mo;
			f[x] = 1ll * f[x] * ifr[size[e[i].t]] % mo; // 将e[i].t这个子树的长为size[e[i].t]的有序序列与之前的序列合并，做1 / size[son]的贡献
		}
	f[x] = 1ll * f[x] * fra[size[x] - 1] % mo; // 乘上size[x]!的贡献
}
int h[maxn][maxn][maxn]; // h[x][i][j] 表示在以x为根的子树中，选出若干子树，分配到1 ~ n - k和k + 1 - n，前者分配了i个点，后者分配了j个点，这所有的子树的拓扑序随意合并，得到一个长度为i + j的序列，这样的方案数
int tmp[2][maxn][maxn]; // 用于从子树的h计算x的h
void dpg(int x, int rt) { // 计算h[x][*][*]，在rt为枚举到的中间这块树的编号最小点时
	if (x >= rt) { // 由于rt是中间这块树的编号最小点，所以，如果点的编号不小于rt，它可以放在中间这块树里
		for (int i = g[x]; i; i = e[i].nxt)
			if (e[i].t != pre[x]) {
				pre[e[i].t] = x; dpg(e[i].t, rt); 
			}
		cl(tmp); int o = 0;
		tmp[o][0][0] = 1;
		for (int i = g[x]; i; i = e[i].nxt) // 对于每个儿子，枚举它以下的子树的分配情况
			if (e[i].t != pre[x]) {
				o ^= 1; cl(tmp[o]);
				for (int l = 0; l < size[x]; ++l) // 前若干个儿子分给1 - n - k l个节点
					for (int r = 0; r + l < size[x]; ++r) // 分给k + 1 - n r个节点
						for (int ll = 0; ll + r + l < size[x] && ll <= size[e[i].t]; ++ll) // 当前儿子e[i].t分给前半部分ll个节点
							for (int rr = 0; ll + rr + r + l < size[x] && rr <= size[e[i].t]; ++rr) { // 分给后半部分rr个节点
								int t = 1ll * tmp[o ^ 1][l][r] * h[e[i].t][ll][rr] % mo; // 两个序列各自的方案数相乘
								t = 1ll * t * fra[l + r + ll + rr] % mo; 
								t = 1ll * t * ifr[l + r] % mo;
								t = 1ll * t * ifr[ll + rr] % mo; // 再乘上合并的不同方案数
								add(tmp[o][l + ll][r + rr], t);
							}
			}
		for (int l = 0; l < size[x]; ++l)
			for (int r = 0; r + l < size[x]; ++r)
				h[x][l][r] = tmp[o][l][r];
	}
	add(h[x][size[x]][0], f[x]); // x也可以不在中间这块树里，被整体分配到前半部分/后半部分
	add(h[x][0][size[x]], f[x]);
}
int solve(int rt, int k) {
	cl(vis); dp(rt); cl(h); cl(pre); dpg(rt, rt); // 计算dp值
	return 1ll * h[rt][n - k][n - k] * fra[n - k] % mo * fra[n - k] % mo * ifr[2 * n - 2 * k] % mo; // 将若干个大小和为n - k的子树分到前半部分，若干个大小和为n - k的子树分到后半部分，这两部分的拓扑序合并起来的方案数是h，而h = 前半序列的方案数 × 后半序列的方案数 ×　合并方案数((2n - 2k)! / (n - k)! / (n - k)!), 除以后面这串，就得到了两半序列的方案数之积
}
class InducedSubgraphs {
	public:
		int getCount(vector <int> edge1, vector <int> edge2, int k) {
			cl(g); ei = 0; n = 1 + edge1.size();
			for (int i = 0; i < n - 1; ++i)
				ae(edge1[i] + 1, edge2[i] + 1), ae(edge2[i] + 1, edge1[i] + 1);　// 加边
			ifr[1] = 1;
			for (int i = 2; i <= n; ++i) ifr[i] = (mo - 1ll * (mo / i) * ifr[mo % i] % mo) % mo;
			fra[0] = 1;
			for (int i = 1; i <= n; ++i) fra[i] = 1ll * fra[i - 1] * i % mo;
			ifr[0] = 1;
			for (int i = 1; i <= n; ++i) ifr[i] = 1ll * ifr[i - 1] * ifr[i] % mo;　// 以上，处理fra[i] = i!, ifr[i] = 1 / i!
			int ans = 0;
			if (k == 1 || k == n) return fra[n]; // 可以任意编号
			if (2 * k - 1 < n) { // 此时，第k - n - k + 1个点形成了一条链
				int len = n - 2 * k + 2;
				for (int rt = 1; rt <= n; ++rt) { // 枚举第k个点
					cl(pre);
					dfs(rt);
					stot = 0;
					for (int i = g[rt]; i; i = e[i].nxt)
						son[++stot] = e[i].t; // 记录它的儿子
					for (int si = 1; si <= stot; ++si) { // 枚举第k + 1个点是它的第si个儿子
						cl(vis);
						int now = son[si]; bool flag = 1;
						if (n - size[now] != k) continue; // 去掉这个儿子所在的子树，剩下的部分大小必须为k
						for (int i = 2; i < len; ++i) {
							vis[now] = 1;
							int scnt = 0, nxt = -1;
							for (int j = g[now]; j; j = e[j].nxt)
								if (pre[e[j].t] == now) {
									++scnt; nxt = e[j].t;
								}
							if (scnt != 1) { flag = 0; break; } // 一路验证是否为链
							now = nxt; 
						}
						if (!flag) continue;
						vis[now] = vis[rt] = 1; // 将链端打上记号
						dp(rt); dp(now); // 以rt为根，去掉链的部分，剩下来大小为k的树的拓扑序个数就是编号1 - k的分配方案数。now是链的另一端，以它为根，去掉链的部分，剩下树的拓扑排序数就是编号n - k + 1 - n的分配方案数。
						add(ans, 1ll * f[rt] * f[now] % mo); // 两边的分配方案数相乘
					}
				}
			} else {
				for (int rt = 1; rt <= n; ++rt) // 枚举中间这块树中，编号最小的点rt
					add(ans, solve(rt, k));
				ans = 1ll * ans * fra[2 * k - n] % mo; // 中间大小为2 * k - n的连通块的编号可以任意分配
			}
			return ans;
		}
};
