#include <algorithm>
using namespace std;
const int inf = 1000000000;
int m, tot, num[51], f[51][2501];
class KingdomAndDice
{
public:
	int n;
	double Abs(double x)
	{
		return x < 0 ? -x : x;
	}
	double newFairness(vector<int> a, vector<int> b, int x)
	{
		n = a.size();
		sort(a.begin(), a.end());
		sort(b.begin(), b.end());
		for(int i = 0; i < n; i++)
		{
			if(a[i])
			{
				for(int j = 0; j < n; j++)
					tot += a[i] > b[j];
			}
			else
				m++;
		}
		b.push_back(x + 1);
		for(int i = 1; i <= n; i++) //计算每种取值（相对位置）的空位数 
		{
			num[i] = b[i] - b[i - 1] - 1;
			for(int j = 0; j < n; j++)
				num[i] -= a[j] > b[i - 1] && a[j] < b[i];
		}
		for(int i = 1; i <= n * n; i++)
			f[0][i] = inf;
		for(int i = 1; i <= n; i++) //计算每种取值之和最少需要使用的数的个数 
		{
			for(int j = 0; j <= n * n; j++)
			{
				f[i][j] = inf;
				for(int k = 0; k <= num[i] && k * i <= j; k++)
					f[i][j] = min(f[i][j], f[i - 1][j - k * i] + k);
			}
		}
		double ans = 0.0;
		for(int i = tot; i <= n * n; i++)
		{
			if(f[n][i - tot] <= m && Abs((double)i / (n * n) - 0.5) < Abs(ans - 0.5))
				ans = (double)i / (n * n);
		}
		return ans;
	}
};