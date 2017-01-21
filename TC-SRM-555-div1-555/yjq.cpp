#include <cstdio>
#define N_MAX 100000
#define P_MAX 150000
#define MOD 1000000007
#define lld "%lld"
typedef long long i64;

inline i64 mod(i64 a) { return a < MOD ? a : a % MOD; }

inline int max(int x, int y) { return x > y ? x : y; }

template <class _nt>
inline _nt I()
{
		register int c; register _nt x = 0;
		do c = getchar(); while (c < '0' || c > '9');
		do x = x * 10 - '0' + c, c = getchar(); while (c >= '0' && c <= '9');
		return x;
}
inline i64 pow(i64 a, int k)
{
		register i64 w;
		for (w = 1; k; a = mod(a * a), k >>= 1)
				if (k & 1) w = mod(w * a);
		return w;
}
int m, n, p, q, i, j, b;
i64 s, a, f[P_MAX + 1], g[P_MAX + 1], ans;
inline i64 com(int n, int k)
{
		return mod(f[n] * mod(g[k] * g[n - k]));
}
inline i64 cal(int n, int p, int k)
{
		return ((p - k) & 1) ? 0 : com(((p - k) >> 1) + n - 1, n - 1);
}
#define inv(a) pow(a, MOD - 2)
class XorBoard {
public:

int count(int H, int W, int Rcount, int Ccount, int S) {
		m = H, n = W, p = Rcount, q = Ccount, s = S ; 
		m = I<int>(), n = I<int>(), p = I<int>(), q = I<int>(), s = I<i64>();
		b = max(m + (p >> 1), n + (q >> 1));
		f[0] = 1;
		for (i = 1; i <= b; ++i)
				f[i] = mod(f[i - 1] * i);
		g[b] = inv(f[b]);
		for (i = b - 1; i >= 0; --i)
				g[i] = mod(g[i + 1] * (i + 1));
		for (i = 0, a = s, b = m; i <= m && i <= p; ++i, a -= n, b -= 2)
				if (b && a % b == 0 && (j = int(a / b), j >= 0 && j <= n && j <= q))
						ans = mod(ans + mod(com(m, i) * cal(m, p, i)) * mod(com(n, j) * cal(n, q, j)));
		printf(lld"\n", ans);
		return 0;
}
} ;
