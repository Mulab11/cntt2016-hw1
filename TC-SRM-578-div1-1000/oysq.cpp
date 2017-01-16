// BEGIN CUT HERE

// END CUT HERE
#line 5 "DeerInZooDivOne.cpp"
#include <bits/stdc++.h>

using namespace std;

#define SZ(x) (int)(x).size()
#define pb push_back
#define mp make_pair
#define fi first
#define se second

typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<double> VD;
typedef long long ll;
typedef pair<int,int> pii;

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(x > y) x = y;}

const int N = 51;

int n;
std::vector<int> adj[N + 9], nex[N + 9];
int f[N + 1][N + 1][N + 1][N + 1];// f[u][ufa][v][vfa] 表示以u为根的子树(u的父亲为ufa)和v为根的子树(v的父亲为vfa)的最大的同构联通块，其中u对应v
std::set<std::pair<pii, pii>> s;// s 表示u, ufa, v, vfa是否遍历过

std::vector<int> p, q;

const int V = N, E = V * V, INF = 0x3f3f3f3f;

struct graph {// 最小费用最大流
	int sz, head[V + 9], to[E + 9], f[E + 9], c[E + 9], ne[E + 9];
	void init() {
		sz = 1, memset(head, 0, sizeof head);
	}
	void addedge(int u, int v, int _f, int _c) {
		to[sz] = v, f[sz] = _f, c[sz] = _c, ne[sz] = head[u], head[u] = sz++;
		to[sz] = u, f[sz] = 0, c[sz] = -_c, ne[sz] = head[v], head[v] = sz++;
	}
	int inv(int x) {
		return ((x - 1) ^ 1) + 1;
	}
	int dis[V + 9], fr[V + 9];
	bool spfa(int S, int T) {
		std::queue<int> q;
		static bool in[V + 9];
		memset(in, false, sizeof in);
		memset(dis, INF, sizeof dis);
		dis[S] = 0;
		in[S] = true;
		q.push(S);
		while(!q.empty()) {
			int x = q.front();
			in[x] = false;
			q.pop();
			for(int i = head[x]; i; i = ne[i]) {
				if(f[i] && dis[to[i]] > dis[x] + c[i]) {
					dis[to[i]] = dis[x] + c[i];
					fr[to[i]] = i;
					if(!in[to[i]]) {
						in[to[i]] = true;
						q.push(to[i]);
					}
				}
			}
		}
		return dis[T] < INF;
	}
	int calc(int S, int T) {
		int flow = INF;
		for(int i = T; i != S; i = to[inv(fr[i])]) {
			chkmin(flow, f[fr[i]]);
		}
		int cost = 0;
		for(int i = T; i != S; i = to[inv(fr[i])]) {
			f[fr[i]] -= flow;
			f[inv(fr[i])] += flow;
			cost += c[fr[i]];
		}
		return flow * cost;
	}
	int maxflowmincost(int S, int T) {
		int ret = 0;
		while(spfa(S, T))
			ret += calc(S, T);
		return ret;
	}
}g;

void dfs(int x, int fa, std::vector<int> &p) {
	p.pb(x);
	for(auto y : adj[x])
		if(y != fa) {
			nex[x].pb(y), nex[y].pb(x);
			dfs(y, x, p);
		}
}

void dp(int x, int xfa, int y, int yfa) {
	if(s.count(mp(mp(x, xfa), mp(y, yfa)))) return ;
	s.insert(mp(mp(x, xfa), mp(y, yfa)));
	int &v = f[x][xfa][y][yfa];
	for(auto u : nex[x])
		if(u != xfa)
			for(auto v : nex[y])
				if(v != yfa)
					dp(u, x, v, y);
	// x和y的子树进行二分图最大权匹配来转移
	g.init();
	int S = n, T = n + 1;
	for(int i = 0; i < SZ(nex[x]); ++i)
		if(nex[x][i] != xfa) g.addedge(S, i, 1, 0);
	for(int i = 0; i < SZ(nex[y]); ++i)
		if(nex[y][i] != yfa) g.addedge(i + SZ(nex[x]), T, 1, 0);
	for(int i = 0; i < SZ(nex[x]); ++i) {
		int u = nex[x][i];
		if(u != xfa)
			for(int j = 0; j < SZ(nex[y]); ++j) {
				int v = nex[y][j];
				if(v != yfa) g.addedge(i, j + SZ(nex[x]), 1, -f[u][x][v][y]);
			}
	}
	v = -g.maxflowmincost(S, T) + 1;
}

struct DeerInZooDivOne {
    int getmax(vector <int> a, vector <int> b) {
		n = SZ(a) + 1;
		for(int i = 0; i < n; ++i) adj[i].clear();
		for(int i = 0; i < n - 1; ++i) adj[a[i]].pb(b[i]), adj[b[i]].pb(a[i]);

		int ans = 0;
		for(int i = 0; i < n - 1; ++i) {// 枚举将两个联通块分开的边
			p.clear(), q.clear(), s.clear();
			for(int j = 0; j < n; ++j) nex[j].clear();// nex 表示去掉第i条边后的边集
			dfs(a[i], b[i], p), dfs(b[i], a[i], q);// 分别取出边两侧的点
			for(int j = 0; j < SZ(p); ++j) {
				int u = p[j];
				std::vector<int> ufas = nex[u];
				ufas.pb(n);// n 表示没有父亲
				for(auto ufa : ufas)
					for(int k = 0; k < SZ(q); ++k) {
						int v = q[k];
						std::vector<int> vfas = nex[v];
						vfas.pb(n);// 同上
						for(auto vfa : vfas) {
							// fprintf(stderr, "%d %d %d %d\n", u, ufa, v, vfa);
							dp(u, ufa, v, vfa);// 枚举两个根以及方向
							chkmax(ans, f[u][ufa][v][vfa]);
						}
					}
			}
		}
		return ans;
    }
};
