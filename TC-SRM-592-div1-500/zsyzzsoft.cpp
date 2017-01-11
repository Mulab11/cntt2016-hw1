#include <algorithm>
using namespace std;
const int p = 1000000007;
int f[51][53][2701];
class LittleElephantAndPermutationDiv1
{
public:
	void Add(int &x, int y)
	{
		x = (x + y) % p;
	}
	int getNumber(int n, int m)
	{
		f[0][0][0] = 1;
		for(int i = 0; i < n; i++) //依次填入每个数字 
		{
			for(int j = 0; j <= n; j++) //只关心填过的数字中重合位置的个数 
			{
				for(int k = 0; k <= 2500; k++) //所有重合位置的最大值之和 
				{
					Add(f[i + 1][j + 2][k + (i + 1) * 2], (long long)f[i][j][k] * (i - j) * (i - j) % p); //都填入与另一边重合的位置 
					Add(f[i + 1][j + 1][k + (i + 1)], (long long)f[i][j][k] * (i - j) * (n - i * 2 + j) * 2 % p); //其中一个填入新位置 
					Add(f[i + 1][j + 1][k + (i + 1)], (long long)f[i][j][k] * (n - i * 2 + j) % p); //填入重合的新位置 
					Add(f[i + 1][j][k], (long long)f[i][j][k] * (n - i * 2 + j) * (n - i * 2 + j - 1) % p); //都填入新位置 
				}
			}
		}
		int ans = 0;
		for(int i = m; i <= 2500; i++)
			Add(ans, f[n][n][i]);
		return ans;
	}
};