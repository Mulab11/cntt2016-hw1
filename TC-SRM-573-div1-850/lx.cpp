#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define LX_JUDGE

using namespace std;
typedef long long LL;

template<typename T> inline void upmax(T & x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T & x, T y) { x > y ? x = y : 0; }

const int mo = 1e9 + 7;
const int N = 2e5 + 10;

inline int qpow(int x, int n)
{
	int ans = 1;
	while (n)
	{
		if (n & 1)
			ans = (LL) ans * x % mo;
		x = (LL) x * x % mo;
		n >>= 1;
	}
	return ans;
}

class WolfPack
{
public : 
	vector<int> xs, ys;
	int fac[N], inv[N];

	inline int C(int n, int m)
	{
		return (LL) fac[n] * inv[m] % mo * inv[n - m] % mo;
	}

	int solve(const vector<int> & S, int m)
	{
		int n = S.size();
		int mi = -N, mx = N, v = S[0] & 1;
		rep (i, 0, n - 1)
		{
			if ((S[i] & 1) != v)
				return 0;
			upmax(mi, S[i] - m);
			upmin(mx, S[i] + m);
		}
		int ans = 0;
		for (int i = mi; i <= mx; i += 2)
		{
			int tmp = 1;
			rep (j, 0, n - 1)
			{
				int d = abs(i - S[j]);
				tmp = (LL) tmp * C(m, (m - d) >> 1) % mo;
			}
			(ans += tmp) >= mo ? ans -= mo : 0;
		}
		return ans;
	}

	int calc(vector<int> x, vector<int> y, int m)
	{
		rep (i, 0, x.size() - 1)
		{
			xs.pb(x[i] - y[i]);
			ys.pb(x[i] + y[i]);
		}
		fac[0] = 1;
		rep (i, 1, m)
			fac[i] = (LL) fac[i - 1] * i % mo;
		inv[m] = qpow(fac[m], mo - 2);
		down (i, m, 1)
			inv[i - 1] = (LL) inv[i] * i % mo;
		int p = solve(xs, m);
		int q = solve(ys, m);
		return (LL) p * q % mo;
	}
};
