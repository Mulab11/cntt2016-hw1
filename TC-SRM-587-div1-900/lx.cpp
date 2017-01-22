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
const int N = 2333;

class ThreeColorability {
private :
	vector<string> EF;
	int fa[N], d[N], n, m;
	inline int findSet(int x) {
		if (fa[x] == x)  return x;
		int r = findSet(fa[x]);
		d[x] ^= d[fa[x]];
		return fa[x] = r;
	}
public :
	//二分图，贪心
	vector<string> lexSmallest(vector<string> field) {
		n = field.size();
		m = field[0].size();
		rep (i, 0, n-1)  fa[i] = i;
		rep (j, 0, m-1) {
			rep (i, 1, n-1) if (field[i][j] != '?') {
				char v = field[i][j];
				rep (k, 0, i-1) if (field[k][j] != '?') {
					char u = field[k][j];
					int x = findSet(i), y = findSet(k);
					if (x == y) {
						if ((u == v) ^ (d[i] == d[k])) {
							return EF;
						}
					} else {
						fa[x] = y;
						d[x] = d[i] ^ d[k] ^ (u != v);
					}
				}
			}
		}
		rep (i, 0, n-1) rep (j, 0, m-1) {
			if (field[i][j] == '?') {
				bool ok = 1;
				char u = 'N';
				rep (k, 0, n-1) {
					if (i != k && field[k][j] != '?') {
						char v = field[k][j];
						int x = findSet(i), y = findSet(k);
						if (x == y) {
							if ((u == v) ^ (d[i] == d[k])) {
								ok = 0;
								break ;
							}
						}
					}
				}
				if (!ok) {
					ok = 1;
					u = 'Z';
					rep (k, 0, n-1) {
						if (i != k && field[k][j] != '?') {
							char v = field[k][j];
							int x = findSet(i), y = findSet(k);
							if (x == y) {
								if ((u == v) ^ (d[i] == d[k])) {
									ok = 0;
									break ;
								}
							}
						}
					}
					if (!ok) {
						return EF;
					}
				}
				field[i][j] = u;
				rep (k, 0, n-1) {
					if (i != k && field[k][j] != '?') {
						char v = field[k][j];
						int x = findSet(i), y = findSet(k);
						if (x != y) {
							fa[x] = y;
							d[x] = d[i] ^ d[k] ^ (u != v);
						}
					}
				}
			}
		}
		return field;
	}
};
