#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <ctime>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <typeinfo>

using namespace std;    

const int MOD = 1000000007;

const int MAXN = 100 + 10;
const int MAXM = MAXN * MAXN + 10;

class KingdomAndCities
{
	public:

	int fac[MAXM], inv[MAXM];

	int fpow(int a, int p)
	{
		if(p == 0) return 1;
		int t = fpow(a, p / 2);
		t = (long long)t * t % MOD;
		if(p & 1) return (long long)a % MOD * t % MOD;
		else return t;
	}

	int sqr(int x)
	{
		return (long long)x * x % MOD;
	}

	int getInv(int x)
	{
		return fpow(x, MOD - 2);
	}

	void init()
	{
		fac[0] = 1;
		for(int i = 1; i < MAXM; i++)
			fac[i] = (long long)fac[i - 1] * i % MOD;
		inv[MAXM - 1] = getInv(fac[MAXM - 1]);
		for(int i = MAXM - 2; i >= 0; i--)
			inv[i] = (long long)inv[i + 1] * (i + 1) % MOD;
	}

	int getC(int n, int m)
	{
		if(m < 0 || m > n) return 0;
		return (long long)fac[n] * inv[m] % MOD * inv[n - m] % MOD;
	}

	int f[MAXN][MAXN];

	void workF(int n, int k)
	{
		for(int i = 0; i <= n; i++)
			for(int j = 0; j <= k; j++)
			{
				long long tmp = getC(i * (i - 1) / 2, j);
				for(int x = 1; x <= i - 1; x++)
					for(int y = 0; y <= j; y++)
						tmp = (tmp - (long long)getC(i - 1, x - 1) * f[x][y] % MOD * getC((i - x) * (i - x - 1) / 2, j - y) % MOD) % MOD;
				tmp = (tmp + MOD) % MOD;
				f[i][j] = tmp;
			}
	}

	int calc0(int n, int k)
	{
		return f[n][k];
	}

	int calc1(int n, int k)
	{
		long long ret = 0;
		int inv2 = getInv(2);
		if(n - 1 >= 0 && k - 2 >= 0)
		{
			ret = (ret + (long long)f[n - 1][k - 2] * getC(n - 1, 2) % MOD) % MOD;
			for(int x = 1; x <= n - 1 - 1; x++)
				for(int y = 0; y <= k - 2; y++)
				{
					long long tmp = getC(n - 1, x);
					tmp = tmp * f[x][y] % MOD;
					tmp = tmp * f[n - 1 - x][k - 2 - y] % MOD;
					tmp = tmp * x % MOD;
					tmp = tmp * (n - 1 - x) % MOD;
					tmp = tmp * inv2 % MOD;
					ret = (ret + tmp) % MOD;
				}
		}
		return ret;
	}

	int calc2(int n, int k)
	{
		long long ret = 0;
		int inv2 = getInv(2), inv3 = getInv(3);
		if(n - 2 >= 0 && k - 3 >= 0)
		{
			ret = (ret + (long long)f[n - 2][k - 3] * (n - 2) % MOD * (n - 2) % MOD) % MOD;
			for(int a = 1; a <= n - 2 - 1; a++)
				for(int x = 0; x <= k - 3; x++)
				{
					int b = n - 2 - a, y = k - 3 - x;
					long long tmp = getC(n - 2, a);
					tmp = tmp * f[a][x] % MOD;
					tmp = tmp * f[b][y] % MOD;
					tmp = tmp * a % MOD * b % MOD;
					ret = (ret + tmp) % MOD;
				}
		}
		if(n - 2 >= 0 && k - 4 >= 0)
		{
			ret = (ret + (long long)f[n - 2][k - 4] * sqr(getC(n - 2, 2)) % MOD) % MOD;
			for(int a = 1; a <= n - 2 - 1; a++)
				for(int x = 0; x <= k - 4; x++)
				{
					int b = n - 2 - a, y = k - 4 - x;
					long long tmp = getC(n - 2, a);
					tmp = tmp * f[a][x] % MOD;
					tmp = tmp * f[b][y] % MOD;
					tmp = tmp * (sqr(getC(n - 2, 2)) - sqr((getC(a, 2) + getC(b, 2)) % MOD)) % MOD;
					tmp = tmp * inv2 % MOD;
					ret = (ret + tmp) % MOD;
				}
			for(int a = 1; a <= n - 2 - 2; a++)
				for(int b = 1; b <= n - 2 - a - 1; b++)
					for(int x = 0; x <= k - 4; x++)
						for(int y = 0; y <= k - 4 - x; y++)
						{
							int c = n - 2 - a - b, z = k - 4 - x - y;
							long long tmp = (long long)getC(n - 2, a + b) * getC(a + b, a) % MOD;
							tmp = tmp * f[a][x] % MOD;
							tmp = tmp * f[b][y] % MOD;
							tmp = tmp * f[c][z] % MOD;
							tmp = tmp * (n - 2) % MOD * a % MOD * b % MOD * c % MOD;
							tmp = tmp * inv3 % MOD;
							ret = (ret + tmp) % MOD;
						}
		}
		return ret;
	}

	int howMany(int N, int M, int K)
	{
		if(K < N - 1)
			return 0;

		init();
		workF(N, K);

		if(M == 0)
			return calc0(N, K);
		else if(M == 1)
			return calc1(N, K);
		else if(M == 2)
			return calc2(N, K);

		return 0;
	}
};

