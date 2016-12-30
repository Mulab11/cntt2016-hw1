#include <algorithm>
using namespace std;
const int inf = 1000000000;
class StringWeight
{
public:
	int f[51][27][27];
	int Sum(int a, int b)
	{
		return (a + b - 1) * (b - a) / 2;
	}
	int getMinimum(vector<int> l)
	{
		int n = l.size(), sum[51] = {0}, ans = inf;
		for(int i = 0; i < n; i++)
			sum[i + 1] = sum[i] + l[i];
		for(int i = 0; i <= n; i++)
		{
			for(int j = 0; j <= 26; j++)
			{
				for(int k = 0; k <= 26; k++)
					f[i][j][k] = inf;
			}
		}
		f[0][0][0] = 0;
		for(int i = 0; i < n; i++)
		{
			for(int u = 0; u <= 26; u++) //仍未结束的字母数 
			{
				for(int v = 0; v <= 26; v++) //已经结束的字母数 
				{
					if(f[i][u][v] == inf)
						continue;
					int len = min(l[i], 26); //当前串包含的字母数 
					if(len > 26 - v)
						continue;
					for(int p = 0; p <= 26; p++) //枚举转移 
					{
						for(int q = v; q <= 26; q++)
						{
							int a = 0, b = 0;
							if(p >= u) //开始新字母 
							{
								a = p - u;
								if(a > 26 - u - v)
									continue;
								if(a + q - v > len)
									continue;
								b = min(min(len - (a + q - v), q - v), u); //结束尽量多的字母 
								a += b;
							}
							else //结束已有字母 
							{
								b = u - p;
								if(b > u || b > q - v)
									continue;
								if(q - v > len)
									continue;
								a = min(min(len - (q - v), q - v - b), u - b);
								b += a;
							}
							if(a + q - v - b > 26 - u - v)
								continue;
							if(b + len - a - b - (q - v - b) > u)
								continue;
							int w = Sum(sum[i], sum[i] + b) - Sum(sum[i + 1] - a, sum[i + 1]); //贪心在前面结束，从后面开始 
							if(l[i] > len && b == u) //添加重复的字母 
								w += l[i] - len;
							f[i + 1][p][q] = min(f[i + 1][p][q], f[i][u][v] + w);
						}
					}
				}
			}
		}
		for(int i = 0; i <= 26; i++) //枚举末状态用过的字母数 
			ans = min(ans, f[n][0][i]);
		return ans;
	}
};