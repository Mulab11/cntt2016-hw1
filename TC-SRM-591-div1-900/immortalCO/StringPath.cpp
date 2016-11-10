#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
typedef long long ll;
typedef long double ld;

const int mod = 1e9 + 9;

int f[2][1 << 16];
int pos[10][10], cnt[20], point[20][20];

int *F, canA, canB;
bool next_type;
int next_len;
void dfs(int i, int s, int h, int cur)
{
	if(!(h & 1) && (1 << i) > canA) return;
	if(!(h & 2) && (1 << i) > canB) return;
	if(i == next_len)
	{
		// 使用转移！
		(F[s] += cur) %= mod;
		return;
	}
	if(next_type)
	{
		dfs(i + 1, s, h, (ll) cur * (26 - bool((canA | canB) & 1 << i)) % mod);
		// 就是下一个字母
		if((canA | canB) & (1 << i))
		{
			if(canA & (1 << i)) h |= 1, s |= 1 << (i << 1);
			if(canB & (1 << i)) h |= 2, s |= 2 << (i << 1);
			return dfs(i + 1, s, h, cur);
		}
	}
	else
	{
		dfs(i + 1, s, h, (ll) cur * (26 - bool(canA & 1 << i) - bool(canB & 1 << i)) % mod);
		// 枚举是哪一个字母
		if(canA & (1 << i)) dfs(i + 1, s | 1 << (i << 1), h | 1, cur);
		if(canB & (1 << i)) dfs(i + 1, s | 2 << (i << 1), h | 2, cur);
	}
}

class StringPath
{
public:
	int countBoards(int N, int M, string A, string B)
	{
		if(A[0] != B[0]) return 0;
		if(A[N + M - 2] != B[N + M - 2]) return 0;
		// 我们可以状压每一行的情况，只需要记录”是否可以作为 A[i]、B[i]”即可
		// 转移的时候，要枚举下一行的“划分”，只关心关键位置即可
		memset(pos, -1, sizeof pos);
		for(int i = 0; i != N; ++i)
			for(int j = 0; j != M; ++j)
				point[i + j][pos[i][j] = cnt[i + j]++] = i << 5 | j;
		bool d = 0;
		f[d][3] = 1;
		for(int p = 0; p < N + M - 2; ++p)
		{
			const int len = cnt[p], Set = 1 << (2 * len);
			next_type = A[p+1] == B[p+1];
			next_len = cnt[p+1];
			memset(F = f[d ^= 1], 0, Set << 2);
			for(int s = 1; s != Set; ++s) if(f[!d][s])
			{
				// 先统计附加方案数
				const int cur = (ll) f[!d][s];
				// 考虑能转移出去的集合
				canA = canB = 0;
				for(int i = 0, bit; i != len; ++i)
					if((bit = (s >> (i << 1)) & 3))
					{
						const int x = point[p][i] >> 5;
						const int y = point[p][i] & 31;
						if(pos[x+1][y] != -1)
						{
							if(bit & 1) canA |= 1 << pos[x+1][y];
							if(bit & 2) canB |= 1 << pos[x+1][y];
						}
						if(pos[x][y+1] != -1)
						{
							if(bit & 1) canA |= 1 << pos[x][y+1];
							if(bit & 2) canB |= 1 << pos[x][y+1];
						}
					}
				dfs(0, 0, 0, cur);
			}
		}
		return f[d][3];
	}
}	user;
