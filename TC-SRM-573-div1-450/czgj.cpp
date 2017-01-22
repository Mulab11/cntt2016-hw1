/*
	SPFA
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
struct pack{
	LL d; int p, q; // d = dist, p = id, q = height
};
const int MAXN = 55;
LL dist[MAXN][MAXN];
queue<pack> Q;
int n;
class SkiResorts {
	public:
	long long minCost(vector <string> g, vector <int> h) {
		n = g.size();
		rep(i, 0, n - 1) dist[0][i] = abs(h[i] - h[0]);  // init
		rep(i, 0, n - 1) Q.push(pack{dist[0][i], 0, i}); // init
		rep(i, 1, n - 1) rep(j, 0, n - 1) dist[i][j] = 1ll << 60; // init
		while (!Q.empty()){ // SPFA
			pack t = Q.front(); Q.pop();
			rep(i, 0, n - 1) if (g[t.p][i] == 'Y')
				rep(j, 0, n - 1) if (h[t.q] >= h[j]){
					LL d0 = t.d + abs(h[i] - h[j]);
					if (d0 < dist[i][j]){ // relax
						dist[i][j] = d0;
						Q.push(pack{d0, i, j});
					}
				}
		}
		LL ret = 1ll << 60;
		rep(i, 0, n - 1) ret = min(ret, dist[n - 1][i]);
		return ret == (1ll << 60) ? -1 : ret;
	}
	
};

/*
	****** shitai...
		- Kagami Chan
*/
