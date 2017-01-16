// BEGIN CUT HERE

// END CUT HERE
#line 5 "CurvyonRails.cpp"
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

const int N = 25, M = 25;
const int d[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int n, m;

const int V = N * M * 3 + 2, E = 14 * N * M, INF = 0x3f3f3f3f;

int c[2];// 黑(1)白(0)点数量

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
	pii calc(int S, int T) {
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
		return mp(flow, flow * cost);
	}
	int maxflowmincost(int S, int T) {
		int ret = 0;
		int flow = 0;
		while(spfa(S, T)) {
			pii tmp = calc(S, T);
			ret += tmp.se;
			flow += tmp.fi;
		}
		if(flow < ::c[0] * 2) {// 当流量 = 白(黑)点 * 2时才有解
			return -1;
		}
		return ret;
	}
}g;

int id[N + 9][M + 9], tot;

struct CurvyonRails {
    int getmin(vector <string> field) {
		n = SZ(field);
		m = SZ(field[0]);
		g.init();
		tot = 0;
		c[0] = c[1] = 0;
		int S = n * m * 3 + 1, T = S + 1;
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < m; ++j) {
				if(field[i][j] != 'w') {
					::c[(i + j) & 1]++;
					id[i][j] = ++tot;
					int r = ++tot, c = ++tot;
					// 把每个点拆成3个点x, rx, cx
					// rx, cx分别表示行和列的匹配
					// 特殊点的位置，如果出现了两个行(列)匹配，
					// 那么会产生1的代价
					if((i + j) & 1) {
						g.addedge(S, id[i][j], 2, 0);
						if(field[i][j] == '.') {
							g.addedge(id[i][j], r, 2, 0);
							g.addedge(id[i][j], c, 2, 0);
						}
						else {
							g.addedge(id[i][j], r, 1, 0);
							g.addedge(id[i][j], r, 1, 1);
							g.addedge(id[i][j], c, 1, 0);
							g.addedge(id[i][j], c, 1, 1);
						}
					}
					else {
						g.addedge(id[i][j], T, 2, 0);
						if(field[i][j] == '.') {
							g.addedge(r, id[i][j], 2, 0);
							g.addedge(c, id[i][j], 2, 0);
						}
						else {
							g.addedge(r, id[i][j], 1, 0);
							g.addedge(r, id[i][j], 1, 1);
							g.addedge(c, id[i][j], 1, 0);
							g.addedge(c, id[i][j], 1, 1);
						}
					}
				}
			}
		}
		if(c[0] != c[1]) {// 黑白点数量要想等
			return -1;
		}
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < m; ++j) {
				if(field[i][j] != 'w' && (i + j) % 2) {
					int r1 = id[i][j] + 1, c1 = id[i][j] + 2;
					for(int k = 0; k < 4; ++k) {
						int x = i + d[k][0];
						int y = j + d[k][1];
						if(0 <= x && x < n && 0 <= y && y < m && field[x][y] != 'w') {
							int r2 = id[x][y] + 1, c2 = id[x][y] + 2;
							if(d[k][0] == 0) g.addedge(r1, r2, 1, 0);// 行匹配
							else g.addedge(c1, c2, 1, 0);// 列匹配
						}
					}
				}
			}
		}
		return g.maxflowmincost(S, T);
    }
};
