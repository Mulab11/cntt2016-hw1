#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second
#define bin(x) (1<<(x))
#define mp make_pair
#define pb push_back

using namespace std;
typedef long long LL;

template<typename T> inline void upmax(T & x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T & x, T y) { x > y ? x = y : 0; }

const int mo = 1e9 + 7;

inline int qpow(int x, int n) {
	int ans = 1;
	while (n) {
		if (n & 1)  ans = (LL) ans * x % mo;
		x = (LL) x * x % mo;
		n >>= 1;
	}
	return ans;
}

inline void upd(int & x, int y) {
	(x += y) >= mo ? x -= mo : 0;
}
inline int inc(int x, int y) {
	return (x += y) >= mo ? x - mo : x;
}
inline int dec(int x, int y) {
	return (x -= y) < 0 ? x + mo : x;
}

int C[41][41];

class Gauss_Elimination {
private :
	int e[41][41];

	int Gauss(int n) {
		int ans = 1;
		int i, j, k;
		for (i = 1; i <= n; ++i) {
			for (j = i; j <= n && !e[j][i]; ++j);
			if (j > n)  return 0;
			if (i != j) {
				swap(e[i], e[j]);
				ans = mo - ans;
			}
			int inv = qpow(e[i][i], mo - 2);
			for (j = i + 1; j <= n; ++j) if (e[j][i]) {
				int t = mo - (LL) e[j][i] * inv % mo;
				for (k = i; k <= n; ++k) {
					e[j][k] = ((LL) t * e[i][k] + e[j][k]) % mo;
				}
			}
			ans = (LL) ans * e[i][i] % mo;
		}
		return ans;
	}

	int build(int l1, int l2, int l3) {
		memset(e, 0, sizeof(e));
		l2 += l1, l3 += l2;
		rep (i, 0, l1 - 1) {
			e[i][i] = l3 - 1;
			rep (j, 0, l3 - 1) if (i != j) 
				e[i][j] = mo - 1;
		}
		rep (i, l1, l2 - 1) {
			e[i][i] = l2 - 1;
			rep (j, 0, l2 - 1) if (i != j)
				e[i][j] = mo - 1;
		}
		rep (i, l2, l3 - 1) {
			e[i][i] = l1;
			rep (j, 0, l1 - 1)
				e[i][j] = mo - 1;
		}
		return Gauss(l3 - 1);
	}
public :
	void count(int n, int m, int * f) {
		rep (i, 0, n) {
			f[i] = build(m, i, n - i);
			rep (j, 0, i - 1) {
				upd(f[i], mo - (LL) f[j] * C[i][j] % mo);
			}
		}
	}
} T;

class SweetFruits {
private :
	vector<int> A[21], B[21];
	int f[41], Cnt[41], a[41], n, m, Lim;

	void Dfs(int *a, int k, int now, int cnt, vector<int> *M) {
		if (now > Lim)  return ;
		if (!k) {
			M[cnt].pb(now);
		} else {
			Dfs(a + 1, k - 1, now, cnt, M);
			Dfs(a + 1, k - 1, now + (*a), cnt + 1, M);
		}
	}

	int myMerge(const vector<int> &A, const vector<int> &B) {
		LL ans = 0;
		int j = B.size() - 1;
		rep (i, 0, A.size()-1) {
			while (j >= 0 && A[i] + B[j] > Lim)  --j;
			ans += j + 1;
		}
		return ans % mo;
	}
public :
	//Meet-in-Middle, Matrix-Tree theorem
	int countTrees(vector<int> val, int Lim) {
		C[0][0] = 1;
		rep (i, 1, 40) {
			C[i][0] = 1;
			rep (j, 1, i)
				C[i][j] = inc(C[i - 1][j - 1], C[i - 1][j]);
		}
		this->Lim = Lim;
		rep (i, 0, val.size()-1) {
			if (val[i] != -1) {
				a[n++] = val[i];
			} else {
				m++;
			}
		}
		int half = n >> 1, Rhalf = n - half;
		Dfs(a, half, 0, 0, A);
		Dfs(a + half, Rhalf, 0, 0, B);
		rep (i, 0, half)   sort(A[i].begin(), A[i].end());
		rep (i, 0, Rhalf)  sort(B[i].begin(), B[i].end());
		rep (i, 0, half) rep (j, 0, Rhalf) {
			upd(Cnt[i + j], myMerge(A[i], B[j]));
		}
		T.count(n, m, f);
		int ans = 0;
		rep (i, 0, n) {
			upd(ans, (LL) Cnt[i] * f[i] % mo);
		}
		return ans;
	}
};
