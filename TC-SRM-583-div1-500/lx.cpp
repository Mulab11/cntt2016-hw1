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

const int N = 53;

class TurnOnLamps {
private :
	int fa[N], deg[N];
	inline int findSet(int x) {
		return fa[x] == x ? x : fa[x] = findSet(fa[x]);
	}
public :
	int minimize(vector<int> roads, string start, string nec) {
		int n = roads.size() + 1;
		rep (i, 0, n - 1)  fa[i] = i;
		rep (i, 0, n - 2) {
			if (nec[i] == '0') {
				fa[i + 1] = roads[i];
			}
		}
		rep (i, 0, n - 2) {
			if (start[i] == '0') {
				deg[findSet(i + 1)]++;
				deg[findSet(roads[i])]++;
			}
		}
		int ans = 0;
		rep (i, 0, n - 1) {
			if (fa[i] == i && (deg[i] & 1))
				ans++;
		}
		return ans >> 1;
	}
};
