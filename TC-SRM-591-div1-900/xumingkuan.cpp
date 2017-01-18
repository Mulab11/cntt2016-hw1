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
const int MOD = 1000000009;
const int MAXN = 8;
class StringPath
{
private:
	/*  //WA
	int p26[MAXN];//p26[i] = 26^i
	int f[2][MAXN][MAXN];//f[i & 1][j][k]: anti-diagonal i, string A at j, string B at k, number of different boards of the first i anti-diagonals
	*/
	int f[2][1 << (MAXN << 1)];//f[number(i, j)][S]: j-th cell of anti-diagonal i, S[2k+l] = if there is a path of string l to the k-th cell of anti-diagonal (i - (k > j))
public:
	int countBoards(int n, int m, string A, string B)
	{
		/*  //WA
		if(A[0] != B[0] || A[n + m - 1] != B[n + m - 1])//impossible
			return 0;
		p26[0] = 1;
		for(int i = 1; i < MAXN; i++)
			p26[i] = (long long)p26[i - 1] * 26 % MOD;
		memset(f[0], 0, sizeof(f[0]));
		f[0][min(n, m) - 1][min(n, m) - 1] = 1;
		for(int i = 1; i <= n + m - 2; i++)
		{
			const int jmn = max(0, min(n, m) - 1 - i), jmx = min(min(n, m) - 1, n + m - 2 - i);
			memset(f[i & 1], 0, sizeof(f[i & 1]));
			for(int j = jmn; j <= jmx; j++)
				for(int k = jmn; k <= jmx; k++)
				{
					if(A[i] != B[i] && j == k)
						continue;
					f[i & 1][j][k] = ((long long)f[~i & 1][j][k] + f[~i & 1][j][k + 1] + f[~i & 1][j + 1][k] + f[~i & 1][j + 1][k + 1]) * p26[jmx - jmn - (j != k)] % MOD;
					printf("f[%d][%d][%d] = %d\n", i, j, k, f[i & 1][j][k]);
				}
		}
		return f[(n + m - 2) & 1][0][0];
		*/
		if(n > m)
			swap(n, m);//min(n, m) => n
		memset(f[0], 0, sizeof(f[0]));
		f[0][3 << ((n - 1) << 1)] = 1;
		int now = 0, tmp;
		for(int i = 0; i <= n + m - 2; i++)
		{
			const int jmn = max(0, n - 1 - i), jmx = min(n - 1, n + m - 2 - i);
			for(int j = jmn; j <= jmx; j++)
			{
				now = !now;
				memset(f[now], 0, sizeof(f[now]));
				for(int S = 0; S < (1 << (n << 1)); S++)
				{
					if(!(tmp = f[!now][S]))
						continue;
					#define add(a, b) a = (a + b) % MOD
					if(A[i] == B[i])
					{
						add(f[now][S | ((S & (3 << ((j + 1) << 1))) >> 2)], tmp);//choose A[i] and B[i]
						add(f[now][~(~S | (3 << (j << 1)))], (long long)tmp * 25);//choose others
					}
					else
					{
						add(f[now][~(~(S | ((S & (1 << ((j + 1) << 1))) >> 2)) | (2 << (j << 1)))], tmp);//choose A[i]
						add(f[now][~(~(S | ((S & (2 << ((j + 1) << 1))) >> 2)) | (1 << (j << 1)))], tmp);//choose B[i]
						add(f[now][~(~S | (3 << (j << 1)))], (long long)tmp * 24);//choose others
					}
				}
				/*for(int S = 0; S < (1 << (n << 1)); S++)
					if(f[now][S])
						printf("f[%d][%d][%d] = %d\n", i, j, S, f[now][S]);*/
			}
		}
		int ans = 0;
		for(int S = 3; S < (1 << (n << 1)); S += 4)
			ans = (ans + f[now][S]) % MOD;
		return ans;
	}
};

