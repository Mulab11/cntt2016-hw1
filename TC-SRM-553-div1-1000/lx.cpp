#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second
#define mp make_pair
#define pb push_back

using namespace std;
typedef long long LL;

template<typename T> inline void upmax(T & x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T & x, T y) { x > y ? x = y : 0; }

const LL inf = 1e18;
const int N = 55;

class YamanoteLine {
private :
	int minCoe, maxCoe;
	LL d[N][N * 2];
	inline void update(const int & v, const int & u, int k, int b) {
		rep (i, max(minCoe, minCoe - k), maxCoe - max(k, 0)) {
			if (d[u][i - minCoe] != inf) {
				upmin(d[v][i + k - minCoe], d[u][i - minCoe] + b);
			}
		}
	}
public :
	//差分约束模型
	//最短路
	LL howMany(int n, vector<int> s1, vector<int> t1, vector<int> l1, 
			vector<int> s2, vector<int> t2, vector<int> l2) {
		LL low = n, high = inf;
		rep (s, 0, n) {
			minCoe = -n - 1, maxCoe = n + 1;
			rep (i, 0, n) 
				fill(d[i], d[i] + maxCoe - minCoe + 2, inf);
			d[s][-minCoe] = 0;
			rep (tim, 0, n) {
				rep (i, 0, n - 1)  update(i, i + 1, 0, -1);
				update(0, n, -1, 0);
				update(n, 0, 1, 0);
				rep (i, 0, s1.size() - 1) 
					update(s1[i], t1[i], s1[i] < t1[i] ? 0 : 1, -l1[i]);
				rep (i, 0, s2.size() - 1)
					update(t2[i], s2[i], s2[i] < t2[i] ? 0 : -1, l2[i]);
			}
			if (d[s][-minCoe] < 0)  return 0;
			rep (i, minCoe, -1) {
				if (d[s][i - minCoe] != inf) {
					upmin(high, -d[s][i - minCoe] / i);
				}
			}
			rep (i, 1, maxCoe) {
				if (d[s][i - minCoe] != inf) {
					upmax(low, (-d[s][i - minCoe] + i - 1) / i);
				}
			}
		}
		if (low > high)  return 0;
		if (high == inf)  return -1;
		return high - low + 1;
	}
};
