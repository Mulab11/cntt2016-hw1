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
const int MOD = 1000000007;

class TwoConvexShapes
{
	private:
	int n, m, a[55][55];//n*m 1-based grid
	int f[55][55], le[55], ri[55];
	inline int opposite(int col)
	{
		return 3 ^ col;
	}
	public:
	int countWays(vector<string> grid)
	{
		n = grid.size();
		m = grid[0].size();
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				a[i + 1][j + 1] = grid[i][j] == 'W' ? 1 : grid[i][j] == 'B' ? 2 : 3;
		int ans = 0;
		for(int col = 1; col <= 2; col++)//color: white-black / black-white
		{
			bool ok = true;
			int totle = 0, totri = m;
			for(int i = 1; i <= n; i++)
			{
				le[i] = 0;
				ri[i] = m;
				for(int j = 1; j <= m; j++)
					if(a[i][j] == opposite(col))
					{
						ri[i] = j - 1;
						break;
					}
				for(int j = m; j >= 1; j--)
					if(a[i][j] == col)
					{
						le[i] = j;
						break;
					}
				if(le[i] > ri[i])//not convex
				{
					ok = false;
					break;
				}
				//col-[le[i], ri[i]]-opposite(col)
				if(le[i] > totle)
					totle = le[i];
				if(ri[i] < totri)
					totri = ri[i];
			}
			if(!ok)
				continue;
			memset(f, 0, sizeof(f));//f[i][j]: row i, col 1 ~ (<=j)
			for(int i = 0; i <= m; i++)
				f[0][i] = 1;
			for(int i = 1; i <= n; i++)
				for(int j = le[i]; j <= m; j++)
					f[i][j] = (f[i][j - 1] + (j <= ri[i] ? f[i - 1][j] : 0)) % MOD;
			ans = (ans + f[n][m]) % MOD;
			memset(f, 0, sizeof(f));//f[i][j]: row i, col 1 ~ (>=j)
			for(int i = 0; i <= m; i++)
				f[0][i] = 1;
			for(int i = 1; i <= n; i++)
				for(int j = ri[i]; j >= 0; j--)
					f[i][j] = (f[i][j + 1] + (j >= le[i] ? f[i - 1][j] : 0)) % MOD;
			ans = (ans + f[n][0]) % MOD;
			//WWBB
			//WWBB
			//WWBB
			//WWBB remove duplication like this
			if(totri >= totle)
				ans = (ans - (totri - totle + 1) + MOD) % MOD;
			//WWWW
			//WWWW
			//BBBB
			//BBBB remove duplication like this
			
			//WWWW
			//WWWW
			//WWWW
			//WWWW and avoid removing this twice
			int up = 1, down = n;
			for(int i = 1; i <= n; i++)
				for(int j = 1; j <= m; j++)
				{
					if(a[i][j] == col && i > up)
						up = i;
					if(a[i][j] == opposite(col) && i - 1 < down)
						down = i - 1;
				}
			if(down >= up)
				ans = (ans - (down - up + 1) + MOD) % MOD;
		}
		return ans;
	}
};

