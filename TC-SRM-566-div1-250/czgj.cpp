/*
	Easy countings
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
using namespace std;
typedef long long LL;
class PenguinSledding {
	public:
	long long countDesigns(int n, vector <int> a, vector <int> b) {
		int cnt[233], g[233][233], m = a.size(); LL ret = 1; // empty set
		memset(cnt, 0, sizeof cnt); memset(g, 0, sizeof g);
		rep(i, 0, m - 1) cnt[a[i]]++, cnt[b[i]]++, g[a[i]][b[i]] = g[b[i]][a[i]] = 1;
		rep(i, 1, n) rep(j, i + 1, n) rep(k, j + 1, n) ret += g[i][j] && g[j][k] && g[k][i]; // triangle
		rep(i, 1, n) ret += 1ll << cnt[i]; // a bunch of edges with common vertex
		return ret -= n + m; // exclude duplicates (empty set && only 1 edge) 
	}
};

/*
	Hitsuji ga ippiki
	Hitsuji ga nihiki
	Hitsuji ga sanbiki
	Hitsuji ga ippai
		- Counting Sheep
*/
