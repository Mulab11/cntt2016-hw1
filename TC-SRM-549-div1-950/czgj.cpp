/*
	big brute force
*/
#include <bits/stdc++.h>
#define rep(i, l, r) for (int _r = r, i = l; i <= _r; ++i)
#define red(i, r, l) for (int _l = l, i = r; i >= _l; --i)
#define debug(x) cerr << #x << " = " << x << endl
#define MEM(x, y) memset(x, y, sizeof x)

using namespace std;
typedef pair<int, int> PI;
typedef vector<int> VI;
typedef vector<PI> VPI;
const int INF = 2333333;
const int NN = 233;
const int MM = 2333;
int hd[NN], cur[NN], dis[NN];
int nxt[MM], to[MM], flow[MM];
int id[NN][NN];
int n, tl;
void ae(int u, int v, int f){
	++tl; to[tl] = v; flow[tl] = f; nxt[tl] = hd[u]; hd[u] = tl;
}
void add(int u, int v, int f){
	ae(u, v, f); ae(v, u, 0);
}
bool bfs(int S, int T){
	static int q[NN], l, r;
	rep(i, 0, T) cur[i] = hd[i], dis[i] = 0;
	for (l = r = dis[S] = 1, q[1] = S; l <= r && !dis[T]; ++l)
		for (int i = hd[q[l]]; i; i = nxt[i])
			if (flow[i] && !dis[to[i]])
				dis[q[++r] = to[i]] = dis[q[l]] + 1;
	return dis[T];
}
int dfs(int p, int T, int f){
	if (p == T || !f) return f;
	int ret = 0;
	for (int& i = cur[p]; i; i = nxt[i]){
		if (flow[i] && dis[to[i]] == dis[p] + 1){
			int r = dfs(to[i], T, min(f, flow[i]));
			f -= r; ret += r;
			flow[i] -= r; flow[i ^ 1] += r;
			if (!f) return ret;
		}
	}
	return ret;
}
int Dinic(int S, int T){
	int ret = 0;
	while (bfs(S, T)) ret += dfs(S, T, INF);
	return ret;
}
int lg2[666];
VI a;
int lb, ub;
VPI vpi;
bool check(VI& b, VPI &g){
	int in[23], out[23], sumin = 0;
	rep(i, 0, n - 1) in[i] = out[i] = a[i];
	for (PI p : g) --out[p.first], --in[p.second];
	rep(i, 0, n - 1) if (in[i] < 0 || out[i] < 0) return 0;
	rep(i, 0, n - 1) sumin += in[i];
	MEM(hd, 0); tl = 1;
	const int S = 2 * n + 1, T = S + 1;
	rep(i, 0, n - 1) add(S, i, in[i]), add(i + n, T, out[i]);
	for (PI p : g) add(p.second, p.first + n, INF);
	rep(i, 0, n - 1) if (b[0] >> i & 1) add(i, T, INF);
	if (Dinic(S, T) != sumin) return 0;
	
	int P[23]; rep(i, 0, n - 1) P[i] = i;
	int cnt = 0;
	do {
		bool ok = 1;
		for (PI p : g) if (P[p.first] < P[p.second]) {ok = 0; break;}
		cnt += ok;
	} while (next_permutation(P, P + n));
	return lb <= cnt && cnt <= ub;
}
int dfs2(VI &b, VPI &g, int d){
	if (d + 1 == (int)b.size()) return check(b, g);
	int ret = 0;
	int cc = __builtin_popcount(b[d]) * __builtin_popcount(b[d + 1]);
	rep(i, 0, (1 << cc) - 1){
		int l = __builtin_popcount(i), p = 0;
		for (int x = b[d]; x; x &= (x - 1))
			for (int y = b[d + 1]; y; y &= (y - 1)){
				if (i >> p & 1) g.push_back(PI(lg2[x & -x], lg2[y & -y]));
				++p;
			}
		ret += dfs2(b, g, d + 1);
		rep(j, 1, l) g.pop_back();
	}
	return ret;
}
int dfs1(VI b, int r){
	if (r == 0) return dfs2(b, vpi, 0);
	int ret = 0;
	for (int s = r; s; s = (s - 1) & r){
		b.push_back(s);
		ret += dfs1(b, s ^ r);
		b.pop_back();
	}
	return ret;
}
class CosmicBlocks {
	public:
	CosmicBlocks(){
		rep(i, 0, 6) lg2[1 << i] = i;
	}
	int getNumOrders(vector <int> _a, int _lb, int _ub) {
		a = _a; lb = _lb; ub = _ub; n = a.size();
		return dfs1(VI(), (1 << n) - 1);
	}
};

