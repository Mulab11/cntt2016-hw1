#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>
#include <cctype>
#include <queue>
#include <map>
using namespace std;
const int MAXN = 32;
class FoxAndFlowerShopDivOne
{
	private:
	int n, m;//n*m grid
	int to2[MAXN * MAXN * 2];//to2[i]: [log2(i)]
	int s[2][MAXN][MAXN];//prefix sum, 1-based
	int f[MAXN][12][MAXN * MAXN * 2];//f[i][k][j]: row 1~i, L - P = j - MAXN * MAXN + (0 ~ (1 << k) - 1), max flowers
	int g[MAXN][12][MAXN * MAXN * 2];//g[i][k][j]: column 1~i, ..
	int rmq(const int f[][MAXN * MAXN * 2], int l, int r)//range maximum query
	{
		if(l < MAXN * MAXN - n * m)
			l = MAXN * MAXN - n * m;
		if(r > MAXN * MAXN + n * m)
			r = MAXN * MAXN + n * m;
		if(l > r)
			return -1;
		const int tmp = to2[r - l + 1];
		return max(f[tmp][l], f[tmp][r - (1 << tmp) + 1]);
	}
	public:
	int theMaxFlowers(vector<string> flowers, int maxDiff)
	{
		n = flowers.size();
		m = flowers[0].size();
		memset(to2, 0, sizeof(to2));
		for(int i = 1; (1 << i) <= n * m * 2 + 1; i++)
			to2[1 << i] = 1;
		for(int i = 1; i <= n * m * 2 + 1; i++)
			to2[i] += to2[i - 1];
		const int maxk = to2[n * m * 2 + 1];
		memset(s, 0, sizeof(s));
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
			{
				s[0][i + 1][j + 1] = s[0][i][j + 1] + s[0][i + 1][j] - s[0][i][j] + (flowers[i][j] == 'L');
				s[1][i + 1][j + 1] = s[1][i][j + 1] + s[1][i + 1][j] - s[1][i][j] + (flowers[i][j] == 'P');
			}
		memset(f, -1, sizeof(f));
		memset(g, -1, sizeof(g));
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				for(int ii = i + 1; ii <= n; ii++)
					for(int jj = j + 1; jj <= m; jj++)//enumerate rectangle #1
					{
						const int nowL = s[0][ii][jj] - s[0][i][jj] - s[0][ii][j] + s[0][i][j];
						const int nowP = s[1][ii][jj] - s[1][i][jj] - s[1][ii][j] + s[1][i][j];
						if(f[ii][0][nowL - nowP + MAXN * MAXN] < nowL + nowP)
							f[ii][0][nowL - nowP + MAXN * MAXN] = nowL + nowP;
						if(g[jj][0][nowL - nowP + MAXN * MAXN] < nowL + nowP)
							g[jj][0][nowL - nowP + MAXN * MAXN] = nowL + nowP;
					}
		for(int i = 1; i <= n; i++)
		{
			for(int j = MAXN * MAXN - n * m; j <= MAXN * MAXN + n * m; j++)//row i -> row 1~i
				if(f[i][0][j] < f[i - 1][0][j])
					f[i][0][j] = f[i - 1][0][j];
			for(int k = 1; k <= maxk; k++)//init rmq
				for(int j = MAXN * MAXN - n * m; j + (1 << k) - 1 <= MAXN * MAXN + n * m; j++)
					f[i][k][j] = max(f[i][k - 1][j], f[i][k - 1][j + (1 << (k - 1))]);
		}
		for(int i = 1; i <= m; i++)
		{
			for(int j = MAXN * MAXN - n * m; j <= MAXN * MAXN + n * m; j++)//column i -> column 1~i
				if(g[i][0][j] < g[i - 1][0][j])
					g[i][0][j] = g[i - 1][0][j];
			for(int k = 1; k <= maxk; k++)//init rmq
				for(int j = MAXN * MAXN - n * m; j + (1 << k) - 1 <= MAXN * MAXN + n * m; j++)
					g[i][k][j] = max(g[i][k - 1][j], g[i][k - 1][j + (1 << (k - 1))]);
		}
		int ans = -1;
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				for(int ii = i + 1; ii <= n; ii++)
					for(int jj = j + 1; jj <= m; jj++)//enumerate rectangle #2
					{
						const int nowL = s[0][ii][jj] - s[0][i][jj] - s[0][ii][j] + s[0][i][j];
						const int nowP = s[1][ii][jj] - s[1][i][jj] - s[1][ii][j] + s[1][i][j];
						//#2 is either on the right of #1 or below #1.
						const int rectangle1 = max(
							!i ? -1 : rmq(f[i], nowP - nowL + MAXN * MAXN - maxDiff, nowP - nowL + MAXN * MAXN + maxDiff), 
							!j ? -1 : rmq(g[j], nowP - nowL + MAXN * MAXN - maxDiff, nowP - nowL + MAXN * MAXN + maxDiff));
						if(rectangle1 >= 0 && ans < nowL + nowP + rectangle1)//legal, update answer
							ans = nowL + nowP + rectangle1;
					}
		//total time complexity: O(n^2m^2)
		return ans;
	}
};

