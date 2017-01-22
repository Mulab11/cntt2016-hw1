#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define bin(x) (1<<(x))
#define LX_JUDGE

using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

template<typename T> inline void upmax(T &x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T &x, T y) { x > y ? x = y : 0; }

const int mo = 1e9 + 7;
const int N = 53;
const int M = 6611;

inline void upd(int &x, int y) {
	(x += y) >= mo ? x -= mo : 0;
}

class SimilarNames {
private :
	int n, tot;				// 串和被限制的标号个数
	vector<int> adj[N];		// 前缀树的邻接表
	int can[1 << 16 | 1], stc;		// 当 S 合法时，can[S] >= 0, 其值表示状态 S 的标号
	int dp[N][M];			// dp[x][i] 表示 x 为根的子树，使用的标号集合为 i 的方案数
	vector<pii> vidsub[M];		// 合法转移（子集）
	vector<int> vidP[M];		// 对状态 S，vidP[S] 记录 S 中哪些标号可以放在根

	inline bool isPrefix(const string &a, const string &b) {		// b 是否是 a 的前缀？
		if (a.size() < b.size())  return 0;
		rep (i, 0, b.size() - 1) if (a[i] != b[i]) {
			return 0;
		}
		return 1;
	}

	map<int, int> G;		// 用来离散化有限制的标号
	void transform(vector<int> &V) {		//带限制的标号的离散化
		rep (i, 0, V.size()-1) {
			int &x = V[i];
			if (G.find(x) == G.end()) {
				G[x] = tot++;
			}
			x = G[x];
		}
	}

	void treeDP(int x) {			//DP 过程
		for (int to : adj[x]) {
			treeDP(to);
		}
		static int g[2][M];			// g 数组辅助转移
		int t = 0;
		memset(g[t], 0, sizeof(g[t]));
		g[t][0] = 1;
		for (int to : adj[x]) {
			memset(g[t ^ 1], 0, sizeof(g[t ^ 1]));
			rep (i, 0, stc-1) {
				int &res = g[t ^ 1][i];
				for (pii u : vidsub[i]) {		//枚举哪些标号来自这一棵子树
					upd(res, (LL) g[t][u.x] * dp[to][u.y] % mo);
				}
			}
			t ^= 1;
		}
		memcpy(dp[x], g[t], sizeof(g[t]));
		if (x < n) {			// 枚举在 x 上放一个标号
			down (i, stc-1, 0) {
				for (int u : vidP[i]) {
					upd(dp[x][i], dp[x][u]);
				}
			}
		}
	}
public :
	// 状压DP，树形DP，状态优化
	// 令 m 表示限制条件个数，则状态数的上界为 3^m，而合法转移的上界为 5^m
	int count(vector<string> name, vector<int> a1, vector<int> a2) {
		n = name.size();
		rep (i, 0, n - 1) {			//建立串之间的前缀关系树
			int f = n;
			rep (j, 0, n - 1) {
				if (i != j && (f == n || name[j].size() > name[f].size()) && isPrefix(name[i], name[j])) {
					f = j;
				}
			}
			adj[f].pb(i);
		}
		transform(a1);		//离散化标号
		transform(a2);
		rep (i, 0, bin(tot) - 1) {			//预处理合法状态、合法子集
			rep (j, 0, a1.size()-1) {
				if ((i & bin(a1[j])) && !(i & bin(a2[j]))) {
					can[i] = -1;
					break ;
				}
			}
			if (can[i] != -1) {
				can[i] = stc++;
				int v = can[i];
				int s = i;
				do {				// 计算合法转移
					if (can[s] >= 0 && can[i ^ s] >= 0) {
						vidsub[v].pb(mp(can[s], can[s ^ i]));
					}
					s = (s-1) & i;
				} while (s != i);
				rep (j, 0, tot-1) {
					if ((i & bin(j)) && can[i ^ bin(j)] >= 0) {
						vidP[v].pb(can[i ^ bin(j)]);
					}
				}
			}
		}
		treeDP(n);
		int ans = dp[n][stc - 1];
		rep (i, 1, n - tot)			//不被限制的标号随意放置，方案数为 (n-tot)!
			ans = (LL) ans * i % mo;
		return ans;
	}
};
