#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;

const int mod = 1e9 + 7;
int f[2][55][4], g[2][55][4];
// f：左边黑色，右边白色，分界点是 j，可以递增或递减的情况为 s
// g：左边白色，右边黑色，……

struct Result {int bl, br, wl, wr;};
Result pre(const string& s)
{
	Result res = (Result) {mod, -mod, mod, -mod};
	for(int i = 0; i != (int) s.size(); ++i)
	{
		if(s[i] == 'B') res.bl = min(res.bl, i), res.br = max(res.br, i);
		if(s[i] == 'W') res.wl = min(res.wl, i), res.wr = max(res.wr, i);
	}
	return res;
}

class TwoConvexShapes
{
public:
	int countWays(vector<string> inp)
	{
		// 每一行一定有一个分界点，并且这个分界点是单调不降/不升的
		// 分界点左边是黑/白，右边是白/黑
		const int N = inp.size(), M = inp[0].size();
		bool d = 0;
		Result row = pre(inp[0]);
		// [0, i), [i, M)
		for(int i = 0; i <= M; ++i)
		{
			if(row.br < i && i <= row.wl) f[d][i][3] = 1;
			if(row.wr < i && i <= row.bl) g[d][i][3] = 1;
		}
		for(int _ = 1; _ != N; ++_)
		{
			d ^= 1;
			memset(f[d], 0, sizeof f[d]);
			memset(g[d], 0, sizeof g[d]);
			row = pre(inp[_]);
			for(int i = 0; i <= M; ++i)
			{
				const bool A = row.br < i && i <= row.wl;
				const bool B = row.wr < i && i <= row.bl;
				for(int j = 0; j <= M; ++j)
					for(int k = 1; k <= 3; ++k)
					{
						if(A) (f[d][i][k & (i == j ? 3 : (i < j ? 1 : 2))] += f[!d][j][k]) %= mod;
						if(B) (g[d][i][k & (i == j ? 3 : (i < j ? 1 : 2))] += g[!d][j][k]) %= mod;
					}
			}
		}
		int A = 0;
		for(int i = 0; i <= M; ++i) for(int k = 1; k <= 3; ++k) A = ((unsigned) A + (unsigned) f[d][i][k] + (unsigned) g[d][i][k]) % mod;
		// 计算重复的部分
		// 一定存在一行，上面颜色全部相同，下面颜色全部相同
		// [0, i), [i, N)
		for(int i = 0; i != N; ++i)
		{
			int s = 3;
			for(int j = 0; j != i; ++j)
			{
				row = pre(inp[j]);
				if(row.bl <= row.br) s &= 1;
				if(row.wl <= row.wr) s &= 2;
			}
			for(int j = i; j != N; ++j)
			{
				row = pre(inp[j]);
				if(row.wl <= row.wr) s &= 1;
				if(row.bl <= row.br) s &= 2;
			}
			A = (A - __builtin_popcount(s) + mod) % mod;
		}
		return A;
	}
}	user;
