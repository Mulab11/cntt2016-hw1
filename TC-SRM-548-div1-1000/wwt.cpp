/*
设f[n][c][sta]表示1所处的联通块大小为n，边数为c，sta表示点2是否在联通块中，g[sta][n][c]表示随便连的方案。经典容斥即可。
*/
#include <bits/stdc++.h>

using namespace std;

const int maxn = 55,maxm = 2505,mo = int(1e9) + 7;

class KingdomAndCities
{
public:
	int c[maxm][maxm],g[3][maxn][maxn],f[maxn][maxn][2];

	int pow(int a,int b)
	{
		int tmp = 1;
		for(;b;b >>= 1,a = a * 1ll * a % mo)
			if (b & 1) tmp = tmp * 1ll * a % mo;
		return tmp;
	}

	int howMany(int n,int m,int k_lim)
	{
		for(int i = 0;i <= 2500;i ++)
		{
			c[i][0] = 1;
			for(int j = 1;j <= i;j ++) c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mo;
		}
		for(int i = 0;i <= n;i ++)
			for(int e = 0;e <= k_lim;e ++)
			{
				g[0][i][e] = c[c[i][2]][e];
				if (i && e >= 2) g[1][i][e] = g[0][i - 1][e - 2] * 1ll * c[i - 1][2] % mo;
				if (i > 1)
				{ 
					if (e >= 4) g[2][i][e] = g[0][i - 2][e - 4] * 1ll * pow(c[i - 2][2],2) % mo;
					if (e >= 3) g[2][i][e] = (g[2][i][e] + g[0][i - 2][e - 3] * 1ll * pow(i - 2,2)) % mo;
				}
			}
		for(int i = 1;i <= n;i ++)
			for(int e = 0;e <= k_lim;e ++)
				for(int sta = 0;sta <= bool(m > 1);sta ++)
				{
					int &curf = f[i][e][sta];
					curf = g[bool(m) + sta][i][e];
					for(int j = 1;j < i;j ++)
						for(int k = 0;k <= e;k ++)
							for(int psta = 0;psta <= sta;psta ++)
							{
								int coef = f[j][k][psta];
								if (sta && !psta) coef = coef * 1ll * c[i - 2][j - 1] % mo;
								if (sta && psta)
								{
									if (j > 1) coef = coef * 1ll * c[i - 2][j - 2] % mo; else coef = 0;
								}
								if (!sta && !psta) coef = coef * 1ll * c[i - 1][j - 1] % mo;
								curf = (curf - coef * 1ll *  g[sta - psta][i - j][e - k] % mo + mo) % mo;
							}
				}
		return f[n][k_lim][m == 2];
	}
};
