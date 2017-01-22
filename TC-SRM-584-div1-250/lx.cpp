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

template<typename T> inline void upmax(T & x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T & x, T y) { x > y ? x = y : 0; }

const int inf = 0x3f3f3f3f;
const int N = 50;

class Egalitarianism {
private :
	int dis[N][N], n;
public :
	int maxDifference(vector<string> adj, int d) {
		n = adj.size();
		rep (i, 0, n - 1) {
			rep (j, 0, n - 1) {
				if (adj[i][j] == 'Y') {
					dis[i][j] = d;
				} else {
					dis[i][j] = (i == j) ? 0 : inf;
				}
			}
		}
		rep (k, 0, n-1) rep (i, 0, n-1) rep (j, 0, n-1)
			upmin(dis[i][j], dis[i][k] + dis[k][j]);
		int ans = 0;
		rep (i, 0, n - 1) rep (j, 0, n - 1)
			upmax(ans, dis[i][j]);
		return ans < inf ? ans : -1;
	}
};
