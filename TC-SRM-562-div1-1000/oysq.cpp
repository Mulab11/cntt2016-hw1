#line 2 "InducedSubgraphs.cpp"  
#include <bits/stdc++.h> 

using namespace std;  

#define ui unsigned
#define ll long long

#define pii std::pair<int,int>
#define mp std::make_pair
#define fi first
#define se second

#define SZ(x) (int)(x).size()
#define pb push_back

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(x > y) x = y;}

const int N = 40;
const int MOD = 1000000009;

int n, k;
std::vector<int> adj[N + 9];

int fa[N + 9], dep[N + 9];

int fac[N + 9], inv[N + 9];

int ans;

int fpm(int a, int b) {// 快速幂
	int ret = 1;
	while(b) {
		if(b & 1) ret = (ll)ret * a % MOD;
		a = (ll)a * a % MOD, b >>= 1;
	}
	return ret;
}

void dfs(int x, int fa) {// 处理出fa和dep
	::fa[x] = fa;
	for(int i = 0; i < SZ(adj[x]); ++i)
		if(adj[x][i] != fa) {
			dep[adj[x][i]] = dep[x] + 1;
			dfs(adj[x][i], x);
		}
}

bool ok(int u, int v, std::vector<int> &p) {// 检测两端点的路径是否为一条长为n - 2 * k + 2的链，并存储在p中
	if(u == v) return false;
	std::vector<int> x, y;
	x.pb(u), y.pb(v);
	while(dep[u] > dep[v]) u = fa[u], x.pb(u);
	while(dep[v] > dep[u]) v = fa[v], y.pb(v);
	while(u != v) {
		u = fa[u], v = fa[v];
		x.pb(u), y.pb(v);
	}
	std::reverse(y.begin(), y.end()), p = x;
	for(int i = 1; i < SZ(y); ++i) p.pb(y[i]);
	if(SZ(p) == n - 2 * k + 2) {
		for(int i = 1; i < SZ(p) - 1; ++i)
			if(SZ(adj[p[i]]) > 2)
				return false;
		return true;
	}
	else return false;
}

int f[N + 9][N + 9];// f[i][j] 表示以i为根，j为i的父亲的子树中标号的方案数
int s[N + 9][N + 9];// s[i][j] 表示以i为根，j为i的父亲的子树中的节点数

void dp1(int x, int fa) {
	if(s[x][fa] != -1) return ;
	s[x][fa] = f[x][fa] = 1;
	// f[x] = 孩子的f的积 * (子树大小 - 1)! / ((每个孩子的子树的大小)!的积)
	for(int i = 0; i < SZ(adj[x]); ++i)
		if(adj[x][i] != fa) {
			dp1(adj[x][i], x);
			s[x][fa] += s[adj[x][i]][x];
			f[x][fa] = (ll)f[x][fa] * f[adj[x][i]][x] % MOD * inv[s[adj[x][i]][x]] % MOD;
		}
	f[x][fa] = (ll)f[x][fa] * fac[s[x][fa] - 1] % MOD;
}

int g[N + 9][N + 9][N + 9][N + 9];// g[i][j][u][v] 表示以i为根，j为i的父亲的子树中有u个红点，v个蓝点的标号方案数

int C(int n, int m) {// 组合数
	return (ll)fac[n] * inv[m] % MOD * inv[n - m] % MOD;
}

void dp2(int x, int fa) {
	if(s[x][fa] != -1) return ;// 计算过了
	s[x][fa] = 0, g[x][fa][0][0] = 1;
	for(int i = 0; i < SZ(adj[x]); ++i)
		if(adj[x][i] != fa) {
			dp2(adj[x][i], x);
			int p[N + 9][N + 9] = {0};
			for(int j = 0; j <= s[x][fa]; ++j)
				for(int k = 0; k <= s[x][fa]; ++k)
					p[j][k] = g[x][fa][j][k], g[x][fa][j][k] = 0;
			s[x][fa] += s[adj[x][i]][x];
			for(int j = 0; j <= s[x][fa]; ++j)
				for(int k = 0; j + k <= s[x][fa]; ++k) {
					int &val = g[x][fa][j][k];
					for(int u = 0; u <= j && u <= s[adj[x][i]][x]; ++u)
						for(int v = 0; v <= k && u + v <= s[adj[x][i]][x]; ++v)
							(val += (ll)p[j - u][k - v] * g[adj[x][i]][x][u][v] % MOD * C(j, u) % MOD * C(k, v) % MOD) %= MOD;
					// 相当于将u个有序元素插进j - u个有序元素中的方案数 * 将v个有序元素插进j - v个有序元素中的方案数
				}
		}
	s[x][fa]++;
	g[x][fa][s[x][fa]][0] = g[x][fa][s[x][fa] - 1][0], g[x][fa][0][s[x][fa]] = g[x][fa][0][s[x][fa] - 1];// 根节点为蓝或者根节点为红
}

class InducedSubgraphs {  
public:  
	int getCount(vector <int> edge1, vector <int> edge2, int _k) {  
		// 初始化
		n = SZ(edge1) + 1, k = _k, ans = 0, fac[0] = 1;
		for(int i = 1; i <= n; ++i) adj[i].clear();
		memset(s, -1, sizeof s);
		memset(f, 0, sizeof f);
		memset(g, 0, sizeof g);
		
		for(int i = 1; i <= n; ++i) fac[i] = (ll)fac[i - 1] * i % MOD;// 预处理n!
		
		if(k == 1) return fac[n];// 特殊考虑k = 1
		
		inv[n] = fpm(fac[n], MOD - 2);
		for(int i = n - 1; i >= 0; --i) inv[i] = (ll)inv[i + 1] * (i + 1) % MOD;// 预处理1/n!
		
		for(int i = 0; i < n - 1; ++i) edge1[i]++, edge2[i]++, adj[edge1[i]].pb(edge2[i]), adj[edge2[i]].pb(edge1[i]);// 连边
		
		if(2 * k <= n) {// 第一种情况
			dfs(1, 0);// 处理出fa和dep
			for(int i = 1; i <= n; ++i)
				for(int j = 1; j <= n; ++j) {// 枚举中间链的两端
					std::vector<int> path;
					if(ok(i, j, path)) {// 判断合法性1
						dp1(i, path[1]);
						dp1(j, path[SZ(path) - 2]);
						if(s[i][path[1]] == k && s[j][path[SZ(path) - 2]] == k)// 判断合法性2
							(ans += (ll)f[i][path[1]] * f[j][path[SZ(path) - 2]] % MOD) %= MOD;
					}
				}
		}
		else {// 第二种情况
			for(int i = 1; i <= n; ++i) {
				dp2(i, 0);
				(ans += g[i][0][n - k][n - k]) %= MOD;
			}
			ans = (ll)ans * fac[2 * k - n - 1] % MOD;// 白点的方案数
		}
		return ans;
	}  
};  
