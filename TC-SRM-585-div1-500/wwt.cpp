#include <bits/stdc++.h>

using namespace std;

const int maxn = 2 * 40 * 40,mo = int(1e9) + 7;

int c[maxn][maxn];

class LISNumber
{
public:
	int pow(int a,int b)
	{
		int tmp = 1;
		for(;b;b >>= 1,a = a * 1ll * a % mo)
			if (b & 1) tmp = tmp * 1ll * a % mo;
		return tmp;
	}

	int count(vector<int> cardsnum, int K)
	{
		int s = 0;
		for(auto p : cardsnum) s += p;
		if (K > s) return 0; //impossible
		for(int i = 0;i <= 2 * s;i ++)
		{
			c[i][0] = 1;
			for(int j = 1;j <= i;j ++) c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mo;
		}
		static int f[maxn];
		memset(f,0,sizeof f);
		for(int i = 1;i <= K;i ++)
		{
			f[i] = 1;
			for(auto p : cardsnum) f[i] = f[i] * 1ll * c[i][p] % mo; //the lis number <= i
			for(int j = 1;j < i;j ++) f[i] = (f[i] - f[j] * 1ll * c[s + i - j][i - j] % mo + mo) % mo; //add another i-j+1 cut lines.
		}
		return f[K];
	}
};
