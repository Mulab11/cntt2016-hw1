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

class Stamp
{
	private:
	int n;
	int sum[3][60];//prefix sum of 'R', 'G', 'B', 1-based
	bool canPaint[60][60];//canPaint[i][j]: same color in [i, j)
	int f[60];//f[i]: paint [0, i), min pushes
	public:
	int getMinimumCost(string desiredColor, int stampCost, int pushCost)
	{
		n = desiredColor.size();
		sum[0][0] = sum[1][0] = sum[2][0] = 0;
		for(int i = 1; i <= n; i++)
		{
			sum[0][i] = sum[0][i - 1] + (desiredColor[i - 1] == 'R');
			sum[1][i] = sum[1][i - 1] + (desiredColor[i - 1] == 'G');
			sum[2][i] = sum[2][i - 1] + (desiredColor[i - 1] == 'B');
		}
		for(int i = 0; i < n; i++)
			for(int j = 1; j <= n; j++)
				canPaint[i][j] = ((sum[0][i] == sum[0][j]) + (sum[1][i] == sum[1][j]) + (sum[2][i] == sum[2][j]) >= 2);//desiredColor[i, j) has <= 1 color
		int ans = 1010101010;
		for(int L = 1; L <= desiredColor.size(); L++)//enumerate L
		{
			memset(f, 31, sizeof(f));
			f[0] = 0;
			for(int i = 1; i <= n; i++)
				for(int j = 0; j <= i - L; j++)
					if(canPaint[j][i])//paint [j, i)
						f[i] = min(f[i], f[j] + (i - j - 1) / L + 1);
			if(f[n] <= n)//legal
				ans = min(ans, f[n] * pushCost + L * stampCost);
			else
				break;//larger L won't be ok either
		}
		return ans;
	}
};

