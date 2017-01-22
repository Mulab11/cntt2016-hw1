#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second
#define LX_JUDGE

using namespace std;
typedef long long LL;

const int mo = 1e9 + 9;
const int N = 19;

inline int qpow(int x,int n)
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

int mod;
int K;

struct matrix
{
	int e[N][N];

	matrix() {}
	matrix(int f)
	{
		memset(e, 0, sizeof(e));
		if (f) 
		{
			rep (i, 0, K)
				e[i][i] = f;
		}
	}

	inline matrix operator * (const matrix & b) const
	{
		static matrix ret;
		memset(ret.e, 0, sizeof(ret.e));
		rep (i, 0, K) rep (k, 0, K) if (e[i][k])
		{
			rep (j, 0, K) if (b.e[k][j])
				ret.e[i][j] = ((LL) e[i][k] * b.e[k][j] + ret.e[i][j]) % mod;
		}
		return ret;
	}
};

int pow_p[33];
matrix A[33], B[33];
matrix step, ans;

int work(int n, int K, int p)
{
	int m = 0;
	pow_p[0] = 1;
	for (int t = n; t /= p; ++m)
		pow_p[m + 1] = pow_p[m] * p;

	::K = K;

	rep (s, 0, m) 
	{
		A[s].e[0][0] = 1;
		rep (i, 1, K)
			A[s].e[0][i] = s;
		rep (i, 1, K) rep (j, i, K)
			A[s].e[i][j] = 1;
	}

	B[0] = 1;

	rep (s, 1, m)
	{
		B[s] = B[s - 1];
		rep (i, 1, p - 1)
			B[s] = B[s] * A[s - 1] * B[s - 1];
	}

	ans = 1;

	while (~m)
	{
		step = B[m] * A[m];
		while (n >= pow_p[m])
		{
			ans = ans * step;
			n -= pow_p[m];
		}
		--m;
	}

	return ans.e[0][K];
}

const int p[] = {0, 0, 2, 3, 2, 5, 3, 7, 2, 3, 5};
const int ord[] = {0, 0, 1, 1, 2, 1, 1, 1, 3, 2, 1};

class MegaFactorial
{
public:
	int countTrailingzeros(int n, int K, int B)
	{
		mod = mo;
		int ans = work(n, K, p[B]);
		if (ord[B] > 1)
		{
			mod = ord[B];
			ans = ((LL) ans + mo - work(n, K, p[B])) * qpow(ord[B], mo - 2) % mo;
		}
		return ans;
	}
};


