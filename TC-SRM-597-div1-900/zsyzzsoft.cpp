#include <algorithm>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1000006, mod = 1000000007;
long long fac[maxn], backfac[maxn], power[maxn], bka, bkb;
class LittleElephantAndBoard
{
public:
	void GetBack(long long a, long long b) //辗转相除
	{
		if(b == 0)
		{
			bka = 1;
			bkb = 0;
			return ;
		}
		long long c = a % b, d = a / b;
		GetBack(b, c);
		long long nbka = bkb, nbkb = bka - d * bkb;
		bka = nbka, bkb = nbkb;
	} 
	long long GetC(long long a, long long b)
	{
		
		if(a < b) return 0;
		if(b < 0) return 0;
		long long ans = (((fac[a] * backfac[b]) % mod) * backfac[a - b]) % mod;
		if(ans < 0) ans += mod;
		return ans;
	}
	long long getNumber(long long m, long long _r, long long _g, long long _b)
	{
		fac[0] = 1;
		for(long long i = 1; i < maxn; i++) //预处理阶乘 
			fac[i] = fac[i - 1] * i, fac[i] %= mod;
		for(long long i = 0; i < maxn; i++)
		{
			GetBack(fac[i], mod);
			backfac[i] = bka;
		}
		power[0] = 1;
		for(long long i = 1; i < maxn; i++) 
			power[i] = power[i - 1] * 2, power[i] %= mod;
		long long a = m - _r, b = m - _g, c = m - _b, ans = 0;
		for(long long i = 0; i <= a + 1; i++) //枚举奇数段数 
		{
			if((i - b + c) % 2) 
				continue;
			long long bs = (i + b - c) / 2;
			if(bs < 0) 
				continue;
			for(long long j = a - 1; j <= a + 1; j++)
			{
				long long nans;
				nans = (GetC(i, bs) * GetC(j, i)) % mod;
				
				nans *= GetC((m - a + i - 2) / 2, j - 1), nans %= mod;
				
				if(nans) 
					nans *= power[j - i], nans %= mod;
				if(j == a) 
					nans *= 2, nans %= mod;
				ans += nans, ans %= mod;
			}
		}
		ans *= 2;
		ans %= mod;
		if(ans < 0)
			ans += mod;
		return ans;
	}
};