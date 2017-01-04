/*
转移显然可以写成多项式乘法的形式。并且当k >= n时可以当成k%n来对待，
所以先求出1~n的转移的多项式A，把A^{m/n}和1~m%n转移的多项式乘起来就好了。
注意，一个位置假如是从两个相同的位置转移的，只能加一次。
*/
#include <bits/stdc++.h>

using namespace std;

const int mo = int(1e9) + 7;

class PenguinEmperor
{
public:
	int n,f[1000],tmp[1000];

	void mul(int *a,int *b,int *c)
	{
		static int sav[1000];
		memset(sav,0,sizeof sav);
		for(int i = 0;i < n;i ++)
			for(int j = 0;j < n;j ++)
				sav[i + j] = (sav[i + j] + a[i] * 1ll * b[j]) % mo;
		for(int i = 0;i < n;i ++) c[i] = (sav[i] + sav[i + n]) % mo;
	}

	int countJourneys(int numCities, long long daysPassed)
	{
		n = numCities;
		memset(f,0,sizeof f);
		f[0] = 1;
		for(int i = 1;i <= n;i ++)
		{
			memset(tmp,0,sizeof tmp);
			for(int j = 0;j < n;j ++)
			{
				int u = (j + i) % n,v = (j - i + n) % n;
				tmp[j] = f[u];
				if (u != v) tmp[j] = (tmp[j] + f[v]) % mo; //一个位置从相同位置转移只能加一次
			}
			memcpy(f,tmp,sizeof f);
		}
		memset(tmp,0,sizeof tmp);
		tmp[0] = 1;
		for(long long v = daysPassed / numCities;v;v >>= 1)
		{
			if (v & 1) mul(tmp,f,tmp);
			mul(f,f,f);
		}
		for(int i = 1;i <= daysPassed % n;i ++) //多出来还要另外乘
		{
			memset(f,0,sizeof f);
			for(int j = 0;j < n;j ++)
			{
				int u = (j + i) % n,v = (j - i + n) % n;
				f[j] = tmp[u];
				if (u != v) f[j] = (f[j] + tmp[v]) % mo;
			}
			memcpy(tmp,f,sizeof f);
		}
		return tmp[0];
	}
};
