/*
将权值为-1的点视为白点，把问题变成去掉的权值>=limit的方案数。令f(s)表示只有s中的点只连白点的生成树数，
g(s)表示强制s中的点只连白点的方案数，那么f(s)=\sum_{s in s1} (-1)^{|s1|-|s|} * g(s1)，最终答案就是\sum_{s,val_s >= limit} f(s)。
注意到f(s)和g(s)的值只与|s|有关，那么预处理出f'(s)和g'(s)，求出g'(s)后f'(s)可以用组合数求，g'(s)可以用基尔霍夫矩阵，
那么问题变成求\sum_{siz} f'(siz) * h(siz)，
h(siz)表示权值和>=limit的子集个数，这个可以meet in the middle来做，两边都排好序，再开个桶就是o(2^(n/2)*(n/2)+n^4)。
*/
#include <bits/stdc++.h>

using namespace std;

const int maxn = 45,maxs = (1 << 20) + 5,mo = int(1e9) + 7;

typedef pair<int,int> pi;

class SweetFruits
{
public:
	pi val_s[maxs],val_e[maxs];
	int f[maxn],g[maxn],c[maxn][maxn],a[maxn],h[maxn],limit,n,m;

	void get_val()
	{
		int tot = 0,tot1 = 0,hal = ((n + 1) >> 1);
		//两边暴力把代价算出来
		for(int s = 0;s < (1 << hal);s ++)
		{
			int cur_val = 0;
			for(int i = 0;i < hal;i ++)
				if (s & (1 << i)) cur_val += a[i];
			val_s[tot ++] = pi(cur_val,__builtin_popcount(s));
		}
		sort(val_s,val_s + tot);
		for(int s = 0;s < (1 << (n - hal));s ++)
		{
			int cur_val = 0;
			for(int i = 0;i < n - hal;i ++)
				if (s & (1 << i)) cur_val += a[hal + i];
			val_e[tot1 ++] = pi(cur_val,__builtin_popcount(s));
		}
		sort(val_e,val_e + tot1);
		static int co[maxn];
		//合并时，由于排好序了，所以用单调性
		for(int i = 0,l = tot - 1;i < tot1;i ++)
		{
			for(;l >= 0 && val_e[i].first + val_s[l].first >= limit;l --) co[val_s[l].second] ++; //单调地扫
			for(int j = 0;j <= hal;j ++)
			{
				int ns = val_e[i].second + j;
				h[ns] = (h[ns] + co[j]) % mo;
			}
		}
	}

	int pow(int a,int b)
	{
		int tmp = 1;
		for(;b;b >>= 1,a = a * 1ll * a % mo)
			if (b & 1) tmp = tmp * 1ll * a % mo;
		return tmp;
	}

	int calc_limited_tree(int col) //有至少col个关键点的生成树数量，基尔霍夫矩阵
	{
		static int b[maxn][maxn];
		memset(b,0,sizeof b);
		for(int i = 0;i < n + m;i ++)
			for(int j = i + 1;j < n + m;j ++)
				if (i < col && j < n) continue; else
				{
					b[i][i] ++,b[j][j] ++,b[i][j] --,b[j][i] --;
				}
		int sig = 0,ret = 1;
		for(int i = 0;i < n + m - 1;i ++)
		{
			for(int k = i;k < n + m - 1;k ++)
				if (b[k][i])
				{
					if (i != k) sig ^= 1;
					swap(b[i],b[k]);
					break;
				}
			if (!b[i][i]) return 0;
			int rev = pow(b[i][i],mo - 2);
			for(int k = i + 1;k < n + m - 1;k ++)
				if (b[k][i])
				{
					int coef = b[k][i] * 1ll * rev % mo;
					for(int p = i;p < n + m - 1;p ++)
						b[k][p] = (b[k][p] - b[i][p] * 1ll * coef % mo + mo) % mo;
				}			
		}
		for(int i = 0;i < n + m - 1;i ++)
			ret = ret * 1ll * b[i][i] % mo;
		if (sig) ret = (mo - ret) % mo;
		return ret;
	}

	int countTrees(vector<int> sweetness,int maxSweetness)
	{
		limit = -maxSweetness;
		sort(sweetness.begin(),sweetness.end());
		for(int i = 0;i <= 40;i ++)
		{
			c[i][0] = 1;
			for(int j = 1;j <= i;j ++) c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mo;
		}
		for(int i = 0;i < sweetness.size();i ++) 
			if (sweetness[i] >= 0)
				a[n ++] = sweetness[i],limit += sweetness[i]; else ++ m;
		for(int i = 0;i <= n;i ++)
			g[i] = calc_limited_tree(i);
		for(int i = 0;i <= n;i ++) //容斥
			for(int j = i;j <= n;j ++)
			{
				int sig = 1;
				if ((j - i) & 1) sig = mo - 1;
				f[i] = (f[i] + 1ll * c[n - i][j - i] * sig % mo * g[j] % mo) % mo;
			}
		get_val();
		int ans = 0;
		for(int i = 0;i <= n;i ++)
			ans = (ans + f[i] * 1ll * h[i]) % mo;
		return ans;
	}
};
