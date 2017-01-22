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

const int N = 305;

class TreeUnion {
private :
	vector<int> adj1[N], adj2[N];
	int dis1[5], dis2[5], n;
	inline void addEdge(int x, int y, vector<int> adj[]) {
		adj[x].pb(y);
		adj[y].pb(x);
	}
	void Dfs(int x, int fa, int d, vector<int> adj[], int dis[]) {
		dis[d]++;
		if (d == 4)  return ;
		rep (i, 0, adj[x].size() - 1) {
			if (adj[x][i] != fa) {
				Dfs(adj[x][i], x, d + 1, adj, dis);
			}
		}
	}
public :
	double expectedCycles(vector<string> tr1, vector<string> tr2, int K) {
		int n = 1, x;
		stringstream ss;
		rep (i, 0, tr1.size() - 1)  ss << tr1[i];
		while (ss >> x)  addEdge(x, n++, adj1);
		ss.clear();
		rep (i, 0, tr2.size() - 1)  ss << tr2[i];
		rep (i, 1, n - 1) {
			ss >> x;
			addEdge(x, i, adj2);
		}
		rep (i, 0, n - 1) {
			Dfs(i, -1, 0, adj1, dis1);
			Dfs(i, -1, 0, adj2, dis2);
		}
		rep (i, 1, 4) {
			dis1[i] >>= 1;
		}
		double ans = 0;
		rep (i, 1, K - 3) {
			ans += (double) dis1[i] * dis2[K - 2 - i] / (n * (n-1));
		}
		return ans;
	}
};
