#include <algorithm>
using namespace std;
class BallsSeparating
{
public:
	void Max(int &a, int b)
	{
		a = max(a, b);
	}
	int minOperations(vector<int> r, vector<int> g, vector<int> b)
	{
		int n = r.size(), sum = 0, f[51][8] = {0};
		for(int i = 0; i <= n; i++)
		{
			for(int j = 0; j < 8; j++)
				f[i][j] = -1000000000;
		}
		f[0][0] = 0;
		for(int i = 0; i < n; i++)
		{
			sum += r[i] + g[i] + b[i];
			for(int j = 0; j < 8; j++) //三种颜色都要有 
			{
				Max(f[i + 1][j | 1], f[i][j] + r[i]);
				Max(f[i + 1][j | 2], f[i][j] + g[i]);
				Max(f[i + 1][j | 4], f[i][j] + b[i]);
			}
		}
		return f[n][7] >= 0 ? sum - f[n][7] : -1;
	}
};
