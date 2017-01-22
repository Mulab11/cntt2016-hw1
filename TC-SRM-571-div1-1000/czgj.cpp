/*
	geometry
	modified shortest path
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
typedef long double LD;
const int MAXN = 63;
LL sqr(LL x){
	return x * x;
}
LD dist(int x0, int y0, int x1, int y1){
	return sqrt((LD)(sqr(x0 - x1) + sqr(y0 - y1)));
}
LD d[MAXN][MAXN], lo[MAXN], hi[MAXN];
int q[MAXN];
bool inq[MAXN];
class CandyOnDisk {
	public:
	string ableToAchieve(vector <int> x, vector <int> y, vector <int> r, int sx, int sy, int tx, int ty) {
		if (sx == tx && sy == ty) return "YES";
		int n = x.size();
		rep(i, 0, n - 1) rep(j, 0, n - 1) d[i][j] = dist(x[i], y[i], x[j], y[j]);
		rep(i, 0, n - 1) lo[i] = 666, hi[i] = 233; // empty segment
		int hd = 0, tl = 0;
		rep(i, 0, n - 1){ // init
			LD dd = dist(x[i], y[i], sx, sy);
			if (dd > r[i]) continue;
			q[tl++] = i; inq[i] = 1;
			lo[i] = hi[i] = dd;
		}
		while (hd < tl){ // spfa
			int u = q[hd++ % MAXN]; inq[u] = 0;
			rep(v, 0, n - 1) if ((x[u] != x[v] || y[u] != y[v]) && d[u][v] <= r[u] + r[v] && hi[u] >= d[u][v] - r[v] && lo[u] <= d[u][v] + r[v]){
				LD low = max(d[u][v] - r[u], (LD)(0));
				LD high = min(d[u][v] + r[u], (LD)(r[v]));
				if (lo[v] > hi[v] || (low < lo[v] || high > hi[v]) && lo[v] <= high && low <= hi[v]){ // upd
					if (lo[v] > hi[v]) lo[v] = low, hi[v] = high;
					else lo[v] = min(lo[v], low), hi[v] = max(hi[v], high);
					if (!inq[v]) q[tl++ % MAXN] = v, inq[v] = 1;
				}
			}
		}
		rep(i, 0, n - 1){ // find ans
			LD D = dist(x[i], y[i], tx, ty);
			if (lo[i] <= D && D <= hi[i]) return "YES";
		}
		return "NO";
	}
};

/*
	.....before it's too late
*/
