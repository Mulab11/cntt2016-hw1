/*
暴力递归每个质数的幂，记n为剩下的数最大是多少，cur为当前的质数，假如n < cur^2，那么显然接下来只能塞至多一个质数，二分找能塞多少个。
复杂度？记忆化后是o(n^{3/4}/logn)，但事实上不记忆化跑得比记忆化快得多。。
*/
#include <bits/stdc++.h>

using namespace std;

class HolyNumbers
{
public:
	vector<int> get_pri(int n)
	{
		static bool pri[1000005];
		vector<int> ret;
		for(int i = 2;i <= n;i ++)
		{
			if (!pri[i]) ret.push_back(i);
			if (i <= n / i)
				for(int j = i * i;j <= n;j += i) pri[j] = 1;
		}
		return ret;
	}

	long long calc(vector<int> &pr,int cr,long long n)
	{
		if (cr == pr.size()) return 1;
		if (n / pr[cr] < pr[cr]) //接下来至多塞一个质数
			return upper_bound(pr.begin() + cr,pr.end(),n) - (pr.begin() + cr) + 1;
		long long ret = calc(pr,cr + 1,n);
		for(n /= pr[cr];n;n = n / pr[cr] / pr[cr]) //暴力枚举这个质数的次幂
			ret += calc(pr,cr + 1,n);
		return ret;  
	}

	long long count(long long upTo, int maximalPrime)
	{
		vector<int> pri = get_pri(maximalPrime);
		return calc(pri,0,upTo);
	}
};
