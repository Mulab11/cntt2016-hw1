#include <bits/stdc++.h>

using namespace std;

const int limit = 50000;

bool f[limit + 100];
int d[1000005],bas[1000005],co[1005];

class TheDivisionGame
{
public:
	void first_get_prime()
	{	
		for(int i = 2;i <= limit;i ++)
			for(int j = i;j <= limit / i;j ++)
				f[i * j] = 1;
	}

	long long countWinningIntervals(int L, int R)
	{
		/*
		sg[n]=n的质因子个数（重复算多个）。那么现在问题就变成求出L~R这些数的sg了，可以发现，除了最大的质因子外，
		其他的质因子必然<=sqrt(R)，那么我们可以枚举2~sqrt(R)的质数，然后L/i~R/i这样枚举，复杂度大概是3*10^6这样，
		顺便可以记录<=sqrt(R)这些质因子的乘积，
		那么就可以顺便判断是否有>sqrt(n)的质因子了，剩下的事情就简单了。维护sg的前缀和，开个桶记录一下即可。
		*/
		first_get_prime();
		for(int i = 0;i <= R - L;i ++) bas[i] = 1;
		for(int i = 2;i <= limit;i ++)
			if (!f[i])
				for(int j = L / i + bool(L % i);j <= R / i;j ++)
				{
					int ref = i * j,c = 0,mu = 1;
					for(;ref % i == 0;ref /= i) ++ c,mu *= i;
					d[i * j - L] += c,bas[i * j - L] *= mu;
				}
		long long ans = 0;
		co[0] = 1;
		for(int i = 0,csg = 0;i <= R - L;i ++)
		{
			if (L + i != bas[i]) ++ d[i]; //有一个>sqrt(n)的质因子
			csg ^= d[i];
			ans += (R - L - i + 1);
			ans -= co[csg];
			co[csg] ++;
		}
		return ans;
	}
};
