#include <bits/stdc++.h>

using namespace std;

const int refer_prime[11] = {0,0,2,3,2,5,3,7,2,3,5}; //the prime whose time we need to count

struct mat
{
	int a[20][20],size;

	int* operator[](int b)
	{
		return a[b];
	}

	void init(int n)
	{
		size = n;
		memset(a,0,sizeof a);
	}

	void identity(int n)
	{
		init(n);
		for(int i = 0;i < n;i ++) a[i][i] = 1;
	}
};

int cur_mo;

mat operator *(mat a,mat b)
{
	mat tmp;
	tmp.init(a.size);
	for(int i = 0;i < a.size;i ++)
		for(int k = 0;k < a.size;k ++)
			if (a[i][k])
				for(int j = 0;j < a.size;j ++)
					if (b[k][j])
						tmp[i][j] = (tmp[i][j] + 1ll * a[i][k] * b[k][j] % cur_mo) % cur_mo;
	return tmp;
}

class MegaFactorial
{
public:
	int n,k,cprime;
	mat b[35],s[35];

	int get_rev(int a,int mo)
	{
		int tmp = 1;
		for(int b = mo - 2;b;b >>= 1,a = a * 1ll * a % mo)
			if (b & 1) tmp = tmp * 1ll * a % mo;
		return tmp;
	}

	int calc(int mo)
	{
		cur_mo = mo;
		int N = n;
		mat tmp;
		tmp.identity(k + 2);
		for(int i = 0,d = 1;;i ++,d *= cprime)
		{
			b[i].init(k + 2);//[f(i,0),f(i,1)...,f(i,k),1]
			for(int j = 0;j <= k;j ++) b[i][k + 1][j] = i; //f(i+1,k)=t(i+1)+f(i,1)+...+f(i,k)
			b[i][k + 1][k + 1] = 1;
			for(int j = 1;j <= k;j ++)
				for(int p = 1;p <= j;p ++) b[i][p][j] = 1;
			s[i].identity(k + 2); //b(t(1))*b(t(2))*...*b(t(2^i - 1))
			if (i)
			{
				for(int j = 0;j < cprime;j ++)
				{
					s[i] = s[i] * s[i - 1];
					if (j + 1 != cprime) s[i] = s[i] * b[i - 1];
				}
			}
			if (d > N / cprime) break;
		}
		for(;N;)
		{
			int up = 0,d = 1;
			for(;d <= N / cprime;d *= cprime,++ up);//find the max cprime^k <= N
			tmp = tmp * s[up] * b[up];
			N -= d;
		}
		return tmp[k + 1][k];
	}

	int countTrailingZeros(int N, int K, int base)
	{
		n = N,k = K;
		cprime = refer_prime[base];
		int div_num;//the time of the prime should be divided by div_num
		if (base == 4 || base == 9) div_num = 2; else 
			if (base == 8) div_num = 3; else 
				div_num = 1;
		int mo = int(1e9) + 9;
		return (calc(mo) - calc(div_num) + mo) % mo * 1ll * get_rev(div_num,mo) % mo; //we need to do integer division but not real division
	}
};
