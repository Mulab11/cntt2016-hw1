/*
首先，原问题等价于找到另外一组v，使得原线性空间和v的线性空间相同，并且使得v的和最大。首先，令c为线性空间的基，对于v\c，
显然都可以设为线性空间下的最大值。那么对于基，由于极大线性无关组是个拟阵，所以可以贪心。
先找到最大的基，然后找个线性无关的最大的塞进去，以此类推。实际中，可以先高斯消元完，然后把原来的基异或一下最大值即可。
*/
#include <bits/stdc++.h>

using namespace std;

class XorAndSum
{
public:
	vector<long long> v;

	void gauss()
	{
		for(long long k = (1ll << 60),i = 0;k && i < v.size();k >>= 1) //消元
		{
			for(int j = i;j < v.size();j ++)
				if (v[j] & k) {swap(v[i],v[j]);break;}
			if (!(v[i] & k)) continue;
			for(int j = 0;j < v.size();j ++)
				if ((j != i) && (v[j] & k)) v[j] ^= v[i];
			++ i;
		}
	}

	long long maxSum(vector<long long> number)
	{
		v = number;
		gauss();
		for(int i = 1;i < v.size();i ++) v[0] ^= v[i]; //v[0]为最大的基
		long long ans = v[0];
		for(int i = 1;i < v.size();i ++) 
			v[i] ^= v[0],ans += v[i];
		return ans;
	}
};
