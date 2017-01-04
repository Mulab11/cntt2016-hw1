#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ULL;

const int maxn = 100005;
const int g[2] = {998244353,int(1e9) + 7};

bool f[maxn];
ULL pw[2][maxn];
ULL has[2][maxn];
map<pair<ULL,ULL>,int> sav;

class TheSquareRootDilemma
{
public:
	int countPairs(int N, int M)
	{
		int n = 80000,co = 0;
		for(int i = 0;i < 2;i ++)
		{
			pw[i][0] = 1;
			for(int j = 1;j <= n;j ++) pw[i][j] = pw[i][j - 1] * g[i];
		}
		//相当于问有多少a*b是平方。那么我们把a分解质因数，
		//假如一个质因子出现次数为奇数，那么标记为1，否则为0，把这个当成字符串来hash，那么就相当于有多少个字符串和他相同了。
		for(int i = 2;i <= n;i ++)
			if (!f[i])
			{
				++ co;
				for(int j = 1;j <= n / i;j ++)
				{
					int ref = i * j,fr = ref,c = 0;
					f[ref] = 1;
					for(;ref % i == 0;ref /= i) c ^= 1;
					if (c) 
						for(int k = 0;k < 2;k ++)
							has[k][fr] += pw[k][co]; 
				}
			}
		int ans = 0;
		for(int i = 1;i <= N;i ++) sav[make_pair(has[0][i],has[1][i])] ++;	
		for(int i = 1;i <= M;i ++)
			ans += sav[make_pair(has[0][i],has[1][i])];
		return ans;
	}	
};
