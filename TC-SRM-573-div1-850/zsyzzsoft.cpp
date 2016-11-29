#include <algorithm>
using namespace std;
const int p = 1000000007;
class WolfPack
{
public:
	int n, m, inv[100001], c[100001];
	int Work(int *x)
	{
		sort(x, x + n);
		int ans = 0;
		for(int i = x[n - 1] - m; i <= x[0] + m; i++)
		{
			int mul = 1;
			for(int j = 0; j < n; j++)
			{
				if((m + i - x[j]) & 1)
					mul = 0;
				else
					mul = (long long)mul * c[(m + i - x[j]) / 2] % p;
			}
			ans = (ans + mul) % p;
		}
		return ans;
	}
	int calc(vector<int> x, vector<int> y, int _m)
	{
		n = x.size(), m = _m;
		for(int i = 0; i < n; i++) //坐标变换 
		{
			int tx = x[i], ty = y[i];
			x[i] = tx + ty, y[i] = tx - ty;
		}
		inv[1] = 1;
		for(int i = 2; i <= m; i++) //求逆元 
		{
			inv[i] = -(long long)(p / i) * inv[p % i] % p;
			if(inv[i] < 0)
				inv[i] += p;
		}
		c[0] = 1;
		for(int i = 1; i <= m; i++) //预处理组合数 
			c[i] = (long long)c[i - 1] * (m - i + 1) % p * inv[i] % p;
		return (long long)Work(&x[0]) * Work(&y[0]) % p; //x, y分开考虑 
	}
};