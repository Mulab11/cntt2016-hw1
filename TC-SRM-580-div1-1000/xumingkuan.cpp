#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cctype>
#include <queue>
#include <map>
#include <set>
using namespace std;
const int oo = 1010101010;
class WallGameDiv1
{
private:
	int n, m;//n*m board
	int f[55][55][55][2];//f[i][l][r][s]: the cost to move the token from (i, s ? r : l) to the bottommost row when there are walls at (i~i+1, [l + !s, r - s])
	int a[55][55];//costs
	int sum[55][55];//row prefix sum, 1-based
public:
	int play(vector<string> costs)
	{
		n = costs.size();
		m = costs[0].size();
		for(int i = 0; i < n; i++)
		{
			sum[i][0] = 0;
			for(int j = 0; j < m; j++)
				sum[i][j + 1] = sum[i][j] + (a[i][j] = costs[i][j] - '0');
		}
		memset(f, 31, sizeof(f));
		for(int j = 0; j < m; j++)
			f[n - 1][j][j][0] = a[n - 1][j];
		for(int i = n - 2; i >= 0; i--)
			for(int l = 0; l < m; l++)
				for(int r = m - 1; r >= l; r--)
				{
					if(l == 0 && r == m - 1)
					{
						f[i][l][r][0] = f[i + 1][l][l][0] + a[i][l];
						f[i][l][r][1] = f[i + 1][r][r][0] + a[i][r];
					}
					else
					{
						f[i][l][r][0] = max(f[i + 1][l][l][0] + a[i][l], min(l ? f[i][l - 1][r][0] + a[i][l] : oo, r == m - 1 ? oo : f[i][l][r + 1][1] + sum[i][r + 1] - sum[i][l]));
						f[i][l][r][1] = max(f[i + 1][r][r][0] + a[i][r], min(l ? f[i][l - 1][r][0] + sum[i][r + 1] - sum[i][l] : oo, r == m - 1 ? oo : f[i][l][r + 1][1] + a[i][r]));
					}
				}
		//Rabbit places the token
		int ans = oo;
		for(int j = 0; j < m; j++)
			ans = min(ans, f[0][j][j][0]);
		return ans;
	}
};

