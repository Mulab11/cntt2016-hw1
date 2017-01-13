#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
class SemiPerfectPower
{
private:
	static const int MAXN = 430900, MAXPR = 36400, MAXM = 16900;
	int minprime[MAXN], prime[MAXPR], primenum;
	bool mu2[MAXN];//mu2[i] = mu^2(i)
	bool mu3[MAXM];//mu3[i] = if no d>1&&d^3|i exists
	vector<int> sum[MAXN];//sum[i][j] = sum(k=1~j) mu^2(i*k)
	void init(int n, int m)
	{
		primenum = 0;
		memset(minprime, 0, (n + 1) * sizeof(int));
		for(int i = 2; i <= n; i++)
		{
			if(!minprime[i])
				prime[++primenum] = minprime[i] = i;
			for(int j = 1; i * prime[j] <= n; j++)
			{
				minprime[i * prime[j]] = prime[j];
				if(i % prime[j] == 0)
					break;
			}
		}
		memset(mu2, true, (n + 1) * sizeof(bool));
		for(int i = 2; i * i <= n; i++)
			for(int j = 1; i * i * j <= n; j++)
				mu2[i * i * j] = false;
		memset(mu3, true, (m + 1) * sizeof(bool));
		for(int i = 2; i * i * i <= m; i++)
			for(int j = 1; i * i * i * j <= m; j++)
				mu3[i * i * i * j] = false;
		for(int i = 1; i <= n; i++)
		{
			sum[i].resize(n / i + 1);
			sum[i][0] = 0;
			for(int j = 1; i * j <= n; j++)
				sum[i][j] = sum[i][j - 1] + mu2[i * j];
		}
	}
	int floorsqrt(long long x)
	{
		return (int)(sqrt((long double)x) * (1 + 1e-18));
	}
	int floorcbrt(long long x)
	{
		return (int)(pow((long double)x, (long double)1 / 3.0) * (1 + 1e-18));
	}
	int gcd(int a, int b)
	{
		return !b ? a : gcd(b, a % b);
	}
	long long ans;
	long long mn, mx;
	void search(long long x, long long d, int mu)
	{
		if(x == 1)
		{
			ans += mu * (sum[d][mx / d] - sum[d][mn / d]);
			return;
		}
		search(x / minprime[x], d, mu);
		search(x / minprime[x], d * minprime[x], -mu);
	}
	long long solve(long long n)//count [1, n]
	{
		ans = 0;
		for(int i = 1; (long long)i * i * i <= n; i++)
			if(mu2[i])
				ans += floorsqrt(n / i) - i;
		for(int i = 1; (long long)i * i * i * i <= n; i++)
			if(mu3[i])
				for(int j = 1; j * j * j <= i; j++)
				{
					int t = gcd(i, j * j);
					if(mu2[i / t])
					{
						mn = i / (j * j / t);
						mx = floorcbrt(n / i) / (j * j / t);
						search(i / t, 1, 1);//search divisors of (i / t), reduce a 'log' in time complexity.
					}
				}
		return ans;
	}
public:
	long long count(long long L, long long R)//total time complexity: O(R^(1/3)*log(R)).
	{
		init(floorcbrt(R) + 1, floorsqrt(floorsqrt(R)) + 1);
		return solve(R) - solve(L - 1);
	}
};

