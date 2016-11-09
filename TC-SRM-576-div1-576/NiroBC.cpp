#include <cstdio>
#include <vector>
#include <string>
const int xn = 306, xm = 306, MOD = 1000000009;
int N, M, L, A, B, s[xn], f[xn][xm], g[xn][xm], h[xn][xm];
inline bool choose(int l, int r)
{
	return s[r] - s[l] >= A && s[r] - s[l] <= B;
}
inline int low(int x)
{
	return x < MOD ? x : x - MOD;
}
class TheExperiment
{
	public :
		int countPlacements(std::vector < std::string > Z, int M, int L, int A, int B)
		{
			N = 0;
			for (int i = 0; i < Z.size(); i++)
				for (int j = 0; j < Z[i].length(); j++)
					s[N + 1] = s[N] + Z[i][j] - 48, N++;
			::M = M;
			::L = L;
			::A = A;
			::B = B;
			h[0][0] = 1;
			for (int i = 1; i <= N; i++)
				for (int j = 0; j <= M; j++) // 这个程序总不需要注释了吧...状态转移方程都写在题解里了！
				{
					f[i][j] = 0;
					g[i][j] = 0;
					h[i][j] = low(g[i - 1][j] + h[i - 1][j]);
					for (int l = 1; l < L && l <= i; l++)
						if (choose(i - l, i))
						{
							f[i][j] = low(low(f[i][j] + f[i - l][j - 1]) + h[i - l][j - 1]);
							g[i][j] = low(g[i][j] + g[i - l][j - 1]);
						}
					if (i >= L && choose(i - L, i))
						g[i][j] = low(low(low(g[i][j] + g[i - L][j - 1]) + f[i - L][j - 1]) + h[i - L][j - 1]);
				}
			return low(g[N][M] + h[N][M]);
		}
};