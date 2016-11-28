#include <algorithm>
using namespace std;
const int p = 555555555;
int c[3000][3000];
class XorBoard
{
public:
	int count(int n, int m, int mr, int mc, int s)
	{
		for(int i = 0; i < 3000; i++) //计算组合数 
		{
			c[i][0] = c[i][i] = 1;
			for(int j = 1; j < i; j++)
				c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % p;
		}
		int ans = 0;
		for(int i = mr & 1; i <= mr; i += 2)
		{
			for(int j = mc & 1; j <= mc; j += 2)
			{
				if(i * m + j * n - i * j * 2 != s) //枚举奇数次操作的行数i与列数j 
					continue;
				ans = (((long long)c[n][i] * c[(mr - i) / 2 + n - 1][n - 1] % p) * ((long long)c[m][j] * c[(mc - j) / 2 + m - 1][m - 1] % p) + ans) % p;
			}
		}
		return ans;
	}
};
