#include <algorithm>
using namespace std;
int n, m, ans, f[51][51];
long long x[50], y[50];
class AstronomicalRecords
{
public:
	int LCS()
	{
		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j <= m; j++)
			{
				f[i][j] = max(f[i - 1][j], f[i][j - 1]);
				if(x[i - 1] == y[j - 1])
					f[i][j] = max(f[i][j], f[i - 1][j - 1] + 1);
			}
		}
		return f[n][m];
	}
	int minimalPlanets(vector<int> a, vector<int> b)
	{
		n = a.size(), m = b.size();
		for(int i = 0; i < n; i++) //枚举所有可能的等比变换 
		{
			for(int j = 1; j < m; j++)
			{
				for(int k = 0; k < n; k++)
					x[k] = (long long)a[k] * b[j];
				for(int k = 0; k < m; k++)
					y[k] = (long long)b[k] * a[i];
				ans = max(ans, LCS()); //求最长公共子序列 
			}
		}
		return n + m - ans;
	}
};