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

const int N = 51;

class TravelOnMars {
private :
	int d[N], n;
	inline int dis(int x, int y) {
		return min(abs(x - y), n - abs(x - y));
	}
public :
	int minTimes(vector<int> adj, int S, int T) {
		n = adj.size();
		queue<int> Q;
		fill(d, d + n, -1);
		d[S] = 0;
		Q.push(S);
		while (!Q.empty()) {
			int u = Q.front();
			Q.pop();
			rep (j, 0, n - 1) {
				if (d[j] == -1 && dis(u, j) <= adj[u]) {
					d[j] = d[u] + 1;
					Q.push(j);
				}
			}
		}
		return d[T];
	}
};
