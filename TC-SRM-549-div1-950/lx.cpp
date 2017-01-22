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

const int inf = 0x3f3f3f3f;
const int N = 105;

class Network {
private : 
	struct edge { 
		int to, c, n;
	} e[N * 20];
	int head[N], tot;
	int cur[N], d[N], S, T;
	bool Bfs() {
		queue<int> Q;
		memset(d, -1, sizeof(int) * (T+1));
		d[S] = 0;
		Q.push(S);
		while (!Q.empty()) {
			int u = Q.front();
			Q.pop();
			cur[u] = head[u];
			for (int p = head[u]; p; p = e[p].n) {
				if (e[p].c && d[e[p].to] == -1) {
					d[e[p].to] = d[u] + 1;
					Q.push(e[p].to);
				}
			}
		}
		return d[T] >= 0;
	}
	int Dfs(int x, int f) {
		if (x == T)  return f;
		int a = f;
		for (int &p = cur[x]; p; p = e[p].n) {
			if (e[p].c && d[e[p].to] == d[x] + 1) {
				int t = Dfs(e[p].to, min(e[p].c, a));
				e[p].c -= t;
				e[p ^ 1].c += t;
				if (!(a -= t))  return f;
			}
		}
		d[x] = -1;
		return f - a;
	}
public :
	void init(int n) {
		memset(head, 0, sizeof(int) * (n+1));
		tot = 1;
	}
	inline void addEdge(int x, int y, int c, int d = 0) {
		e[++tot] = (edge) {y, c, head[x]}, head[x] = tot;
		e[++tot] = (edge) {x, d, head[y]}, head[y] = tot;
	}
	int Run(int s, int t) {
		S = s, T = t;
		int ans = 0;
		while (Bfs())
			ans += Dfs(S, inf);
		return ans;
	}
} my;

class CosmicBlocks {
private :
	int n, Min, Max;
	vector<int> block;
	int List[20][20], Size[10];
	int dp[bin(6)+1], adj[10];
	bool used[20], G[20][20];

	int ans;

	int DP() {
		fill(dp, dp + bin(n), 0);
		dp[0] = 1;
		rep (i, 0, bin(n)-1) if (dp[i] > 0) {
			int x = dp[i];
			rep (j, 0, n-1) if (!(i & bin(j))) {
				if ((adj[j] & i) == adj[j]) {
					dp[i | bin(j)] += x;
				}
			}
		}
		return dp[bin(n)-1];
	}

	//网络流判断合法性
	bool Valid() {
		int em = n + n, s = em + 1, t = s + 1;
		my.init(t);
		static int In[10], Out[10];
		fill(In, In + n, 0);
		fill(Out, Out + n, 0);
		rep (u, 0, n-1) rep (v, 0, n-1) {
			if (G[u][v]) {
				my.addEdge(u, v + n, inf);
				In[v]++;
				Out[u]++;
			}
		}
		int tot = 0;
		rep (u, 0, n-1) {
			int tmp = block[u] - Out[u];
			if (tmp < 0) {
				return 0;
			} else {
				my.addEdge(s, u, tmp);
				tot += tmp;
			}
		}
		rep (u, 0, n-1) {
			int tmp = block[u] - In[u];
			if (tmp < 0) {
				return 0;
			} else {
				my.addEdge(u + n, t, tmp);
			}
		}
		rep (i, 0, Size[0]-1) {
			my.addEdge(List[0][i], em, inf);
		}
		my.addEdge(em, t, inf);
		return my.Run(s, t) >= tot;
	}

	void Dfs(int step, int k, int pre) {
		if (step > 0 && Size[step - 1] == 0) 
			return ;
		if (k == n) {
			if (Size[step] == 0) return ;
			if (Valid()) {
				int w = DP();
				if (Min <= w && w <= Max) {
					++ans;
				}
			}
		}
		rep (i, pre+1, n-1) if (!used[i]) {
			List[step][Size[step]++] = i;
			used[i] = 1;
			if (step > 0) {
				int m = Size[step - 1];
				rep (j, 0, bin(m)-1) {
					rep (a, 0, m-1) if (j & bin(a)) {
						int x = List[step - 1][a];
						adj[i] |= bin(x);
						G[i][x] = 1;
					}
					Dfs(step, k + 1, i);
					Dfs(step + 1, k + 1, -1);
					rep (a, 0, m-1) if (j & bin(a)) {
						int x = List[step - 1][a];
						adj[i] ^= bin(x);
						G[i][x] = 0;
					}
				}
			} else {
				Dfs(step, k + 1, i);
				Dfs(step + 1, k + 1, -1);
			}
			used[i] = 0;
			Size[step]--;
		}
	}
public :
	//暴力枚举每一种本质不同的塔
	//网络流检验合法性
	//DP算方案数
	//统计方法数在 [L,R] 中的塔的个数
	int getNumOrders(vector<int> types, int L, int R) {
		block = types;
		Min = L, Max = R;
		n = types.size();
		Dfs(0, 0, -1);
		return ans;
	}
};
