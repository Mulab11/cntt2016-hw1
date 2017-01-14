#include <bits/stdc++.h>

using namespace std;

const int maxn = 40 * 40,mo = int(1e9) + 9;

class ColorfulBuilding
{
public:
	int f[maxn][maxn],g[maxn][maxn],n;//f[c][j],c:当前的改变次数，j:当前序列的开头
	int col[maxn],cpi[maxn][2];//每个位置的颜色

	void decode(vector<string> color,int ty)
	{
		int l = 0;
		for(auto i : color) for(auto j : i) cpi[l ++][ty] = j;
		n = l;
	}

	void relabel()
	{
		static int ap[300][300];
		memset(ap,255,sizeof ap);
		int co = 0;
		for(int i = 0;i < n;i ++)
		{
			int &tmp = ap[cpi[i][0]][cpi[i][1]];
			if (tmp == -1) tmp = (co ++);
			col[i] = tmp;
		}
	}

	int pow(int a,int b)
	{
		int tmp = 1;
		for(;b;b >>= 1,a = a * 1ll * a % mo)
			if (b & 1) tmp = tmp * 1ll * a % mo;
		return tmp;
	}

	int count(vector<string> color1,vector<string> color2,int L)
	{
		decode(color1,0),decode(color2,1);		
		relabel();
		static int fac[maxn],rfac[maxn];
		fac[0] = 1;
		for(int i = 1;i <= n;i ++) fac[i] = fac[i - 1] * 1ll * i % mo;
		rfac[n] = pow(fac[n],mo - 2);
		for(int i = n;i;i --) rfac[i - 1] = rfac[i] * 1ll * i % mo;
		f[0][n - 1] = g[0][n - 1] = 1; //g[c][j]=f[i][j]/(n-j-1)!
		for(int c = 0;c < L;c ++)
		{
			static int s[maxn],sc[maxn];//一个用来存储颜色=i的j的g[c][j]的和，另一个是g[c-1][j]的和
			memset(s,0,sizeof s),memset(sc,0,sizeof sc);
			int alls = 0;//sc的和
			for(int i = n - 1;i >= 0;i --)
			{
				if (i != n - 1) 
				{
					//对于颜色相同的j，没有增加改变次数
					f[c][i] = (s[col[i]] + (alls - sc[col[i]] + mo) % mo) % mo * 1ll * fac[n - (i + 2)] % mo;
					g[c][i] = f[c][i] * 1ll * rfac[n - i - 1] % mo;
				}
				s[col[i]] = (s[col[i]] + g[c][i]) % mo;
				if (c) sc[col[i]] = (sc[col[i]] + g[c - 1][i]) % mo,alls = (alls + g[c - 1][i]) % mo;
			}
		}
		int ans = 0;
		for(int i = 0;i < n;i ++) ans = (ans + f[L - 1][i] * 1ll * fac[n - 1] % mo * rfac[n - i - 1] % mo) % mo; //i前面的东西可以随便放到后面
		return ans;
	}
};
