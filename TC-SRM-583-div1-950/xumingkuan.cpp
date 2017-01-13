#include <cstring>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <cctype>
#include <cassert>
using namespace std;

class RandomPaintingOnABoard
{
private:
	int n, m;
	int a[25][25];//prob
	int sum;//sum of a[i][j]
	int res[25];//res[i]: sum of: column i, row (not chosen)
	int f[1500][2];//f(i)[j][k]: first i columns, sum of res = j, size of set % 2 = k
public:
	double expectedSteps(vector<string> prob)
	{
		if(prob.size() <= prob[0].size())
		{
			n = prob.size();
			m = prob[0].size();
			for(int i = 0; i < n; i++)
				for(int j = 0; j < m; j++)
					a[i][j] = prob[i][j] - '0';
		}
		else
		{
			n = prob[0].size();
			m = prob.size();
			for(int i = 0; i < n; i++)
				for(int j = 0; j < m; j++)
					a[i][j] = prob[j][i] - '0';
		}
		sum = 0;
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				sum += a[i][j];
		double ans = 0;
		for(int s = 0; s < (1 << n); s++)//enumerate rows
		{
			int now = 0;//sum in chosen rows
			for(int i = 0; i < m; i++)
			{
				res[i] = 0;
				for(int j = 0; j < n; j++)
					if(s & (1 << j))
						now += a[j][i];
					else
						res[i] += a[j][i];
			}
			memset(f, 0, sizeof(f));
			int start = 0;//number of rows % 2
			for(int i = 0; i < n; i++)
				if(s & (1 << i))
					start ^= 1;
			f[0][start] = 1;
			int totres = 0;//max sum of res
			for(int i = 0; i < m; i++)
				for(int j = (totres += res[i]); j >= res[i]; j--)
					if(res[i])
						for(int k = 0; k <= 1; k++)
							f[j][k] += f[j - res[i]][!k];
					else//res[i] == 0
						f[j][0] = f[j][1] = f[j][0] + f[j][1];
			for(int i = 0; i <= totres; i++)
				if(now + i)//not empty set
					ans += (double)(f[i][1] - f[i][0]) * sum / (now + i);
		}
		return ans;
	}
};

