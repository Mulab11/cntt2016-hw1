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

const int mod = 1234567891;

inline void upd(LL &x, LL y) {
	(x += y) >= mod ? x -= mod : 0;
}

int m;

struct matrix {
	LL e[122][122];
	matrix(int f = 0) {
		memset(e, 0, sizeof(e));
		if (f) rep (i, 0, m) e[i][i] = 1;
	}
	matrix operator * (const matrix &b) const {
		static matrix res;
		memset(res.e, 0, sizeof(res.e));
		rep (i, 0, m) rep (k, 0, m) {
			rep (j, 0, m) {
				upd(res.e[i][j], e[i][k] * b.e[k][j] % mod);
			}
		}
		return res;
	}
};

matrix qpow(matrix x, LL n) {
	matrix ans = 1;
	while (n) {
		if (n & 1) ans = ans * x;
		x = x * x;
		n >>= 1;
	}
	return ans;
}

inline int inmod(int x, int m) {
	if (x < 0)  x += m;
	if (x >= m) x -= m;
	return x;
}

class TheBrickTowerHardDivOne {
private :
	int C, tot;
	int Id[122], Cnt[122], num[122];
	int hashId[23333];

	void Dfs(int step, int used, int *a) {
		if (step == 4) {
			int v = 0, c = 0;
			rep (i, 0, 3) {
				c += a[i] == a[inmod(i+1, 4)];
				v = v * 4 + a[i];
			}
			hashId[v] = ++tot;
			Id[tot] = v;
			Cnt[tot] = c;
			num[tot] = used;
			return ;
		}
		rep (i, 0, used-1) {
			a[step] = i;
			Dfs(step + 1, used, a);
		}
		if (used < C) {
			a[step] = used;
			Dfs(step + 1, used + 1, a);
		}
	}

	inline int getId(int *a) {
		static int b[4];
		int cur = -1, x = 0;
		rep (i, 0, 3) {
			b[i] = -1;
			rep (j, 0, i-1) if (a[i] == a[j]) {
				b[i] = b[j];
				break ;
			}
			if (b[i] < 0) b[i] = ++cur;
			x = x * 4 + b[i];
		}
		return hashId[x];
	}

	LL trans[122][9];

	void Dfs2(int step, int used, int w, int *a) {
		if (step == 8) {
			int x = getId(a + 4), c = 0;
			rep (i, 0, 3) {
				c += a[i] == a[i + 4];
				c += a[i + 4] == a[inmod(i+1, 4) + 4];
			}
			if (c <= 7) upd(trans[x][c], w);
			return ;
		}
		rep (i, 0, used-1) {
			a[step] = i;
			Dfs2(step + 1, used, w, a);
		}
		if (used < C) {
			a[step] = used;
			w = (LL) w * (C - used) % mod;
			Dfs2(step + 1, used + 1, w, a);
		}
	}

	inline int getId(int x, int y) {
		return x * tot + y;
	}

	matrix my, ans;

public :
	//计数，DP，矩阵乘法
	int find(int C, int K, LL H) {
		this->C = C;
		{
			int a[8];
			memset(a, -1, sizeof(a));
			Dfs(0, 0, a);
			rep (i, 1, tot) {
				memset(trans, 0, sizeof(trans));
				int x = Id[i];
				down (j, 3, 0) {
					a[j] = x % 4;
					x /= 4;
				}
				Dfs2(4, num[i], 1, a);
				rep (j, 1, tot) rep (k, 0, K) {
					rep (v, 0, K-k) {
						upd(my.e[getId(v + k, j)][getId(v, i)], trans[j][k]);
					}
				}
			}
		}
		m = tot * (K + 1);
		rep (i, 0, m) {
			my.e[0][i] = 1;
		}
		ans = qpow(my, H);
		LL res = 0;
		rep (i, 1, tot) {
			LL tmp = ans.e[0][getId(Cnt[i], i)];
			rep (j, 1, num[i]) tmp = tmp * (C-j+1) % mod;
			res += tmp;
		}
		return res % mod;
	}
};
