#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

bool H2[500000], H3[20000];
int *cnt[500000], pf[500000];

int Sqrt(ll n)
{
	int k = sqrtl(n);
	while((ll) k * k > n) --k;
	while((ll) (k + 1) * (k + 1) <= n) ++k;
	return k;
}
int Cbrt(ll n)
{
	int k = cbrtl(n);
	while((ll) k * k * k > n) --k;
	while((ll) (k + 1) * (k + 1) * (k + 1) <= n) ++k;
	return k;
}

ll solve(ll N)
{
	if(!N) return 0;
	ll ans = 0;
	// 只需要考虑平方和立方
	// x = a * b^2
	for(int i = 1; (ll) i * i * i < N; ++i) if(!H2[i])
	{
		ans += Sqrt(N / i) - i;
	}
	// x = a * b^2，且不能表示为上面那种形式
	for(int i = 1; (ll) (i * i) * (i * i) < N; ++i) if(!H3[i])
		for(int k = 1; k * k * k <= i; ++k)
		{
			const int g = __gcd(i, k * k);
			const int ii = i / g;
			const int kk = k * k / g;
			if(H2[ii]) continue;
			const int l = i, r = Cbrt(N / i);
			static int pf[20];
			int M = 0;
			for(int v = ii; v != 1; )
			{
				int p = pf[M++] = ::pf[v];
				while(::pf[v] == p) v /= p;
			}
			for(int S = 0; S != (1 << M); ++S)
			{
				int d = 1, meow = 1;
				for(int i = 0; i != M; ++i) if(S & 1 << i)
					d *= pf[i], meow = -meow;
				ans += meow * (cnt[d][r / kk / d] - cnt[d][l / kk / d]);
			}
		}
	return ans;
}

class SemiPerfectPower
{
public:
	ll count(ll l, ll r)
	{
		const int S3 = ceill(powl(r, (long double) 1.0 / 3)) + 10;
		const int S4 = ceill(powl(r, (long double) 1.0 / 4)) + 10;
		for(int i = 2; i * i <= S3; ++i)
			for(int v = i * i, j = v; j <= S3; j += v)
				H2[j] = 1;
		for(int i = 2; i * i * i <= S4; ++i)
			for(int v = i * i * i, j = v; j <= S4; j += v)
				H3[j] = 1;
		for(int i = 1; i <= S3; ++i)
		{
			int m = S3 / i;
			cnt[i] = new int[m + 1];
			cnt[i][0] = 0;
			for(int j = 1; j <= m; ++j)
				cnt[i][j] = cnt[i][j - 1] + !H2[i * j];
		}
		for(int i = 2; i <= S3; ++i) if(!pf[i])
			for(int j = i; j <= S3; j += i)
				pf[j] = i;
		
		ll A = solve(r);
		ll B = solve(l - 1);
		return A - B;
	}
}	user;
