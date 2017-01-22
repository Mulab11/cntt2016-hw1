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

const int mod = 1e9 + 7;
const int N = 120;

inline void upd(int &x, int y) {
	(x += y) >= mod ? x -= mod : 0;
}

int m;

struct matrix {
	int e[N][N];
	matrix(int f = 0) {
		memset(e, 0, sizeof(e));
		if (f) rep (i, 0, m) e[i][i] = 1;
	}
	matrix operator * (const matrix &b) const {
		static matrix res;
		memset(res.e, 0, sizeof(res.e));
		rep (i, 0, m) rep (k, 0, m) {
			rep (j, 0, m) {
				upd(res.e[i][j], (LL) e[i][k] * b.e[k][j] % mod);
			}
		}
		return res;
	}
};

matrix qpow(matrix x, int n) {
	matrix ans = 1;
	while (n) {
		if (n & 1) ans = ans * x;
		x = x * x;
		n >>= 1;
	}
	return ans;
}

inline int inmod(int x, int mo) {
	if (x < 0)   x += mo;
	if (x >= mo) x -= mo;
	return x;
}

class ConversionMachine {
private :
	int num[15][15];
	matrix My, ans;
public :
	//DP，矩阵乘法
	int countAll(string w0, string w1, vector<int> cost, LL Lim) {
		int n = w0.size();
		rep (i, 0, n) rep (j, 0, n-i) {
			num[i][j] = ++m;
		}
		int tim = 0, c2 = 0, c1 = 0;
		rep (i, 0, n-1) {
			int x = w0[i] - 'a', y = w1[i] - 'a';
			int v = 0;
			while (x != y) {
				++tim, ++v;
				Lim -= cost[x];
				x = inmod(x + 1, 3);
			}
			if (v == 2)  c2++;
			if (v == 1)  c1++;
		}
		if (Lim < 0)  return 0;
		LL un = 0;
		rep (i, 0, 2)  un += cost[i];
		tim += Lim / un * 3;
		rep (i, 0, n) rep (j, 0, n-i) {
			int k = n - i - j;
			if (i > 0) My.e[num[i-1][j+1]][num[i][j]] = i;
			if (j > 0) My.e[num[i][j-1]][num[i][j]] = j;
			if (k > 0) My.e[num[i+1][j]][num[i][j]] = k;
		}
		My.e[0][0] = 1;
		My.e[0][num[0][0]] = 1;
		ans = qpow(My, tim + 1);
		return ans.e[0][num[c2][c1]];
	}
};
