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

const int mo = 1e9 + 9;
const int N = 1311;

inline int qpow(int x, int n) {
	int ans = 1;
	while (n) {
		if (n & 1)  ans = (LL) ans * x % mo;
		x = (LL) x * x % mo;
		n >>= 1;
	}
	return ans;
}
inline void upd(int &x, int y) {
	(x += y) >= mo ? x -= mo : 0;
}
inline int dec(int x, int y) {
	return (x -= y) < 0 ? x + mo : x;
}

class ColorfulBuilding {
private :
	int last[129][129], nxt[N];
	int g[N][N], f[N][N], n;
	int fac[N], inv[N];
public :
	int count(vector<string> A, vector<string> B, int L) {
		rep (i, 0, A.size() - 1) {
			rep (j, 0, A[i].size() - 1) {
				int &pos = last[A[i][j]][B[i][j]];
				++n;
				if (pos)  nxt[pos] = n;
				pos = n;
			}
		}
		fac[0] = 1;
		rep (i, 1, n)  fac[i] = (LL) fac[i - 1] * i % mo;
		inv[n] = qpow(fac[n], mo - 2);
		down (i, n, 1)  inv[i - 1] = (LL) inv[i] * i % mo;
		f[0][0] = 1;
		rep (i, 1, n) {
			int v = inv[n - i], t = nxt[i], r = t ? fac[n - i - 1] : 0;
			f[i][0] = (LL) f[i - 1][0] * (n - i) % mo;
			rep (j, 1, L) {
				f[i][j] = f[i - 1][j - 1];
				upd(f[i][j], (LL) dec(g[i][j], g[i][j - 1]) * v % mo);
				upd(g[t][j], ((LL) f[i][j] * r + g[i][j]) % mo);
				upd(f[i][j], (LL) f[i - 1][j] * (n - i) % mo);
			}
		}
		return f[n][L];
	}
};

int main() {
#ifdef LX_JUDGE
	freopen("in.txt", "r", stdin);
#endif
	return 0;
}
