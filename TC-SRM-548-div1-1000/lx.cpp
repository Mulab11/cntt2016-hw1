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

const int mo = 1e9 + 7;

inline void upd(int &x, int y) {
	(x += y) >= mo ? x -= mo : 0;
}
inline int inc(int x, int y) {
	return (x += y) >= mo ? x - mo : x;
}
inline int dec(int x, int y) {
	return (x -= y) < 0 ? x + mo : x;
}
inline int sqr(int x) {
	return (LL) x * x % mo;
}

class KingdomAndCities {
private :
	int binom[2505][2505];
	int E[52];
	int f[52][52];
public :
	//组合计数，递推
	// 没有 m 的限制时是经典计数问题
	// m 非常小，暴力枚举特殊点的连边情况
	int howMany(int n, int m, int K) {
		E[1] = 0;
		rep (i, 1, n-1)  E[i + 1] = E[i] + i;
		if (K < n-1 || K > E[n])  return 0;
		if (n <= 2)  return !m ? 1 : 0;
		binom[0][0] = 1;
		rep (i, 1, E[n]) {
			binom[i][0] = 1;
			rep (j, 1, i) {
				binom[i][j] = inc(binom[i - 1][j - 1], binom[i - 1][j]);
			}
		}
		rep (i, 1, n) rep (j, 0, K) {
			f[i][j] = binom[E[i]][j];
			rep (a, 1, i-1) {
				int w = binom[i - 1][a - 1];
				rep (b, a-1, j) {
					int p = f[a][b];
					int q = binom[E[i - a]][j - b];
					upd(f[i][j], mo - (LL) w * q % mo * p % mo);
				}
			}
		}
		if (!m) {
			return f[n][K];
		} else if (m == 1) {
			int res = (LL) f[n - 1][K - 2] * binom[n - 1][2] % mo;
			rep (i, 1, n-2) {
				int p = (LL) i * (n - 1 - i) * binom[n - 2][i - 1] % mo;
				rep (j, i-1, K-2) {
					int q = (LL) f[i][j] * f[n - i - 1][K - 2 - j] % mo;
					upd(res, (LL) p * q % mo);
				}
			}
			return res;
		} else {
			if (K < 3) return 0;
			int res = (LL) f[n - 2][K - 3] * sqr(n - 2) % mo;
			rep (i, 1, n-3) {
				int p = 2ll * i * (n - 2 - i) * binom[n - 3][i - 1] % mo;
				rep (j, i-1, K-3) {
					int q = (LL) f[i][j] * f[n - i - 2][K - j - 3] % mo;
					upd(res, (LL) p * q % mo);
				}
			}
			if (K >= 4) {
				upd(res, (LL) f[n - 2][K - 4] * sqr(binom[n - 2][2]) % mo);
				rep (i, 1, n-3) {
					int p = (LL) binom[n - 3][i - 1] * (sqr(i) * sqr(n - i - 2) + 2 * i * (n - i - 2) * (binom[i][2] + binom[n - i - 2][2])) % mo;
					rep (j, i-1, K-4) {
						int q = (LL) f[i][j] * f[n - 2 - i][K - j - 4] % mo;
						upd(res, (LL) p * q % mo);
					}
				}
				rep (i, 1, n-3) rep (j, 1, n-i-3) {
					int p = 2ll * binom[n - 3][i + j] * binom[i + j - 1][i - 1] % mo * i * j * (n - i - j - 2) * (n - 2) % mo;
					rep (x, i-1, K-4) rep (y, j-1, K-4-x) {
						int q = (LL) f[i][x] * f[j][y] % mo * f[n - i - j - 2][K - 4 - x - y] % mo;
						upd(res, (LL) p * q % mo);
					}
				}
			}
			return res;
		}
	}
};
