#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
const int mod = 1e9 + 7;
int f[2][60][2510], C2[60];
// f(i, j, k) 从 1 填到 i，全满的位置有 j 个，且权值为 k 的方案数

// 清空辅助函数
void clear(int f[60][2510], int n)
{
	for(int i = 0; i <= n; ++i)
		memset(f[i], 0, n * n << 2);
}

void inc(int& a, int b)
{
	(a += b) >= mod ? (a -= mod) : 0;
}

class LittleElephantAndPermutationDiv1
{
public:
	int getNumber(int n, int lim)
	{
		bool d = 0;
		f[d][0][0] = 1;
		int val, coef_1, coef_2, coef_3;
		int empty_1, empty_2;
		for(int i = 1; i <= n; ++i) C2[i] = i * (i - 1) / 2;
		for(int i = 1; i <= n; ++i)
		{
			clear(f[d ^= 1], i);
			for(int j = 0; j != i; ++j) if(2 * (i - 1) - j <= n)
			{
				// 空 1 和空 2 的位置个数
				empty_1 = (i - 1) - j;
				empty_2 = n - 2 * (i - 1) + j;
				
				// 1 两个位置对应的排列都是已有的
				// 那么 i 会覆盖之前的数，权值 +2i
				coef_1 = empty_1 * empty_1;
				// 2 其中一个位置是已有的，或两个配对了
				// 权值 +i
				coef_2 = 2 * empty_1 * empty_2 + empty_2;
				// 3 两个都是没有的
				// 全满位置不变，权值不变
				coef_3 = empty_2 * (empty_2 - 1);
				for(int k = 0; k <= (i - 1) * (i - 1); ++k)
					if((val = f[!d][j][k]))
					{
						inc(f[d][j + 2][k + i + i], 	(long long) val * coef_1 % mod);
						inc(f[d][j + 1][k + i],			(long long) val * coef_2 % mod);
						inc(f[d][j + 0][k],				(long long) val * coef_3 % mod);
					}
			}
		}
		int ans = 0;
		for(int i = lim; i <= n * n; ++i) inc(ans, f[d][n][i]);
		return ans;
	}
}   user;
