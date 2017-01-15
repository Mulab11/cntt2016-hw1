#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

class XorCards
{
public:
	ll calc(vector<ll> a,ll x)
	{
		//求出a的线性基
		for(ll bit = (1ll << 60),i = 0;bit && i < a.size();bit >>= 1)
		{
			for(int j = i;j < a.size();j ++)
				if (a[j] & bit) {swap(a[i],a[j]);break;}
			if (!(a[i] & bit)) continue;
			for(int j = 0;j < a.size();j ++)
				if (i != j && (a[j] & bit))
					a[j] ^= a[i];
			++ i;
		}
		ll co = 0;
		for(int i = 0;i < a.size();i ++)
			if (!a[i]) ++ co; //为0的数可以随便选
		if (!x) return (1ll << co) - 1;//空集有可能计重，最后再加回去
		for(int i = 0;i < a.size();i ++)
			if ((x ^ a[i]) < x) x ^= a[i]; //判断是否能凑出x
		if (x) return 0;
		return (1ll << co); //随便选
	}

	ll numberOfWays(vector<ll> num,ll limit)
	{
		ll ans = calc(num,limit);
		for(int bit = 0;bit < 60;bit ++) //假如一个数x比limit小，那么必然存在一个位bit，使得x的前bit-1位（从高往低数）和limit相同，而x[bit]<limit[bit]，并且对于后面的位置就不用管了
		{
			if (limit & 1)
				ans += calc(num,limit ^ 1);
			limit >>= 1;
			for(int i = 0;i < num.size();i ++) num[i] >>= 1;//对于更大的bit，这一位没有用了
		}
		return ans + 1;
	}
};
