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

const int MOD = 1000000007;
const int MAXN = 50 + 10;

class TwoConvexShapes
{
	public:
	int n, m, ans;
	char g[MAXN][MAXN];
	bool ok[MAXN][MAXN];
	int f[MAXN][MAXN];

	void workOk()
	{
		memset(ok, true, sizeof(true));
		for(int i = 1; i <= n; i++)
			for(int j = 0; j <= m; j++)
			{
				ok[i][j] = true;
				for(int k = 1; k <= j && ok[i][j]; k++)
					if(g[i][k] == 'W')
						ok[i][j] = false;
				for(int k = j + 1; k <= m && ok[i][j]; k++)
					if(g[i][k] == 'B')
						ok[i][j] = false;
			}
	}

	void calc()
	{
		workOk();
		memset(f, 0, sizeof(f));
		f[0][0] = 1;
		for(int i = 1; i <= n; i++)
			for(int j = 0; j <= m; j++)
				if(ok[i][j])
					for(int k = 0; k <= j; k++)
						f[i][j] = (f[i][j] + f[i - 1][k]) % MOD;
		for(int i = 0; i <= m; i++)
			ans = (ans + f[n][i]) % MOD;
	}

	void excludeLR()
	{
		workOk();
		for(int i = 0; i <= m; i++)
		{
			bool flag = true;
			for(int j = 1; j <= n && flag; j++)
				if(!ok[j][i])
					flag = false;
			ans -= flag;
		}
	}
	void exclude()
	{
		workOk();
		for(int i = 0; i <= n; i++)
		{
			bool flag = true;
			for(int j = 1; j <= i && flag; j++)
				if(!ok[j][m])
					flag = false;
			for(int j = i + 1; j <= n && flag; j++)
				if(!ok[j][0])
					flag = false;
			ans -= flag;
		}
		for(int i = 0; i <= n; i++)
		{
			bool flag = true;
			for(int j = 1; j <= i && flag; j++)
				if(!ok[j][0])
					flag = false;
			for(int j = i + 1; j <= n && flag; j++)
				if(!ok[j][m])
					flag = false;
			ans -= flag;
		}
		bool flag = true;
		for(int i = 1; i <= n && flag; i++)
			if(!ok[i][m])
				flag = false;
		ans += flag;
		flag = true;
		for(int i = 1; i <= n && flag; i++)
			if(!ok[i][0])
				flag = false;
		ans += flag;
	}

	int countWays(vector<string> grid)
	{
		n = grid.size();
		m = grid[0].size();
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= m; j++)
				g[i][j] = grid[i - 1][j - 1];
		calc();
		excludeLR();
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= m; j++)
				g[i][m + 1 - j] = grid[i - 1][j - 1];
		calc();
		excludeLR();
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= m; j++)
				g[n + 1 - i][j] = grid[i - 1][j - 1];
		calc();
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= m; j++)
				g[n + 1 - i][m + 1 - j] = grid[i - 1][j - 1];
		calc();

		exclude();

		return ans;
	}
};

