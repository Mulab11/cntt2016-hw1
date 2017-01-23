#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <ctime>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <typeinfo>

using namespace std;

const int MAXN = 30 + 10;
const int MAXK = 2 * 900 + 10;

class FoxAndFlowerShopDivOne
{
	public:
	int n, m;
	int map[MAXN][MAXN], sum[MAXN][MAXN], cnt[MAXN][MAXN];
	int f[MAXN][MAXK], g[MAXN][MAXK];
	int ans;
	
	void solve(int maxDiff)
	{
		memset(sum, 0, sizeof(sum));
		memset(cnt, 0, sizeof(cnt));
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= m; j++)
				sum[i][j] = sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1] + map[i][j];
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= m; j++)
				cnt[i][j] = cnt[i][j - 1] + cnt[i - 1][j] - cnt[i - 1][j - 1] + abs(map[i][j]);
				
		memset(f, -1, sizeof(f));
		for(int i = 1; i <= n; i++)
			for(int x = 1; x <= m; x++)
				for(int y = x; y <= m; y++)
					for(int h = 1; h <= i; h++)
					{
						int x1 = h, y1 = x, x2 = i, y2 = y;
						int k = sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1 - 1] + n * m;
						int s = cnt[x2][y2] - cnt[x1 - 1][y2] - cnt[x2][y1 - 1] + cnt[x1 - 1][y1 - 1];
						f[i][k] = max(f[i][k], s);
					}
		for(int i = 1; i <= n; i++)
			for(int k = 0; k <= 2 * n * m; k++)
				if(i - 1 >= 0)
					f[i][k] = max(f[i][k], f[i - 1][k]);
			
		memset(g, -1, sizeof(g));
		for(int i = 1; i <= n; i++)
			for(int x = 1; x <= m; x++)
				for(int y = x; y <= m; y++)
					for(int h = i; h <= n; h++)
					{
						int x1 = i, y1 = x, x2 = h, y2 = y;
						int k = sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1 - 1] + n * m;
						int s = cnt[x2][y2] - cnt[x1 - 1][y2] - cnt[x2][y1 - 1] + cnt[x1 - 1][y1 - 1];
						g[i][k] = max(g[i][k], s);
					}
		for(int i = n; i >= 1; i--)
			for(int k = 0; k <= 2 * n * m; k++)
				if(i + 1 <= n)
					g[i][k] = max(g[i][k], g[i + 1][k]);
				
		for(int i = 1; i <= n - 1; i++)
			for(int k1 = 0; k1 <= 2 * n * m; k1++)
				for(int k2 = 0; k2 <= 2 * n * m; k2++)
					if(2 * n * m - maxDiff <= k1 + k2 && k1 + k2 <= 2 * n * m + maxDiff)
						if(f[i][k1] >= 0 && g[i + 1][k2] >= 0)
							ans = max(ans, f[i][k1] + g[i + 1][k2]);
	}
	
	int theMaxFlowers(vector<string> flowers, int maxDiff)
	{
		ans = -1;
		memset(map, 0, sizeof(map));
		n = flowers.size();
		m = flowers[0].size();
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= m; j++)
				if(flowers[i - 1][j - 1] == 'L')
					map[i][j] = 1;
				else if(flowers[i - 1][j - 1] == 'P')
					map[i][j] = -1;
				else
					map[i][j] = 0;
		solve(maxDiff);
		
		memset(map, 0, sizeof(map));
		n = flowers[0].size();
		m = flowers.size();
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= m; j++)
				if(flowers[j - 1][i - 1] == 'L')
					map[i][j] = 1;
				else if(flowers[j - 1][i - 1] == 'P')
					map[i][j] = -1;
				else
					map[i][j] = 0;
		solve(maxDiff);
		
		return ans;
	}
};

