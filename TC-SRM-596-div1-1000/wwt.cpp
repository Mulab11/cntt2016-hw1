#include <bits/stdc++.h>

using namespace std;

const int maxn = 1000005;

typedef long long ll;

ll a[maxn],bak_a[maxn],tmp[maxn];

class SparseFactorial
{
public:
	void work(int mo,int p,int c,ll *a)
	{
		static int cnt[maxn];
		for(int i = 0;i < mo;i ++) a[i] = (1ll << 60),cnt[i] = 0;
		for(int k = 0;k < p * c;k ++) //(n-0^2)*...*(n-k*2)，枚举k，考虑对某些n的贡献，对于每个n%mo=i，需要找到最小的k，使得f(n)包含至少c个p
			for(int i = k * 1ll * k % p;i < mo;i += p)//n-k^2=0(mod p),n = k^2(mod p)
				if (cnt[i] < c)
				{
					int t = (i - k * 1ll * k % mo + mo) % mo; //n-k^2
					if (!t) cnt[i] = c; else //必然包含p^c=mo
						for(;t % p == 0;t /= p,cnt[i] ++);
					if (cnt[i] >= c) a[i] = k * 1ll * k + 1;//n>k^2
				}
	}

	ll getCount(ll lo, ll hi, ll divisor)
	{
		//a[i]，n>=a[i]且n mod divisor=i与f(n) mod divisor = 0且n mod divsor=i为充要条件
		int px = 1;
		for(int i = 2;i <= divisor;i ++)//分开每个质因子分别计算当divisor=p^k时的a[i]，然后合并a
			if (divisor % i == 0)
			{
				int mo = 1,c = 0;
				for(;divisor % i == 0;divisor /= i,mo *= i,c ++);
				work(mo,i,c,bak_a);
				for(int j = 0;j < mo * px;j ++)//n mod (mo * px)=j,n必须要>=a[j%px],bak_a[j%mo]
					tmp[j] = max(a[j % px],bak_a[j % mo]);
				for(int j = 0;j < mo * px;j ++)
					a[j] = tmp[j];
				px *= mo;
			}
		ll ans = 0;
		for(int i = 0;i < px;i ++)
		{
			ll mi = a[i] / px * px + i; //最小的合法的n mod divisor=i且f(n) mod divisor=0
			if (mi < a[i]) mi += px;
			if (hi >= mi) ans += (hi - mi) / px + 1;
			if (lo > mi) ans -= (lo - mi - 1) / px + 1;
		}
		return ans;
	}
};
