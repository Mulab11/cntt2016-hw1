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
const int N = 55;

class ColorfulWolves {
private :
	int cost[N][N];
	int d[N], n;
	bool vis[N];
public :
	//最短路
	int getmin(vector<string> col) { 
		n = col.size();
		rep (i, 0, n-1) rep (j, 0, n-1) {
			if (col[i][j] == 'N') {
				cost[i][j] = inf;
			} else {
				int v = 0;
				rep (k, 0, j-1) 
					v += col[i][k] == 'Y';
				cost[i][j] = v;
			}
		}
		fill(d, d + n, inf);
		d[0] = 0;
		int u = 0;
		while (u != -1) {
			rep (i, 0, n-1) upmin(d[i], d[u] + cost[u][i]);
			vis[u] = 1;
			u = -1;
			rep (i, 0, n-1) {
				if (!vis[i] && d[i] < inf && (u == -1 || d[i] < d[u])) {
					u = i;
				}
			}
		}
		return d[n-1] < inf ? d[n-1] : -1;
	}
};
