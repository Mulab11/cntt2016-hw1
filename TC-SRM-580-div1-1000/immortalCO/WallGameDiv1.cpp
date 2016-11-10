#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
typedef long long ll;
typedef long double ld;

int f[60], g[60][60][2], sum[60];

int range_sum(int a, int b) {return sum[max(a, b)] - sum[min(a, b) - 1];}

class WallGameDiv1
{
public:
	int play(vector<string> inp)
	{
		// 墙只能放在一列相邻两个方格的中间
		// 如果 B 希望 A 能走某一条路径，B 始终可以通过不断建立强来内定硬点
		// 那就是求从第一行每个点出发的最长简单路径
		// 似乎倒着 DP 就 OK 了？
		
		// 这个做法是错误的
		// 如果某一步转移有多个可行路径，那么 B 可以逼 A 走回头路
		// 那我们可以考虑决策，通过封闭一个区间逼迫另一个
		
		reverse(inp.begin(), inp.end());
		const int N = inp.size(), M = inp[0].size();
		if(M == 1)
		{
			int ans = 0;
			for(int i = 0; i != N; ++i) ans += inp[i][0] - '0';
			return ans;
		}
		for(int j = 1; j <= M; ++j) f[j] = inp[0][j - 1] - '0';
		for(int i = 1; i != N; ++i)
		{
			for(int j = 1; j <= M; ++j) sum[j] = sum[j - 1] + inp[i][j - 1] - '0';
			g[2][M][0] = f[1] + range_sum(1, 1);
			g[2][M][1] = f[1] + range_sum(M - 1, 1);
			g[1][M - 1][0] = f[M] + range_sum(1 + 1, M);
			g[1][M - 1][1] = f[M] + range_sum(M, M);
			// 只有这两个状态才是必须下去的
			// 考虑继续区间 DP
			for(int len = M - 2; len; len--)
				for(int l = 1, r = len; r <= M; ++l, ++r)
					for(int k = 0; k != 2; ++k)
					{
						const int p = (!k ? l : r), q = r ^ l ^ p, d = (!k ? 1 : -1);
						// 如果当前的禁止区间是 [l, r]
						// A 可以选择：走到 p-d 或 q+d
						// B 可以选择：让他走下去，或挡住
						int &ans = g[l][r][k]; ans = 1000000000;
						if(1 <= p - d && p - d <= M)
							ans = min(ans, range_sum(p - d, p - d) + max(f[p - d], g[min(p - d, q)][max(p - d, q)][k]));
						if(1 <= q + d && q + d <= M)
							ans = min(ans, range_sum(p + d, q + d) + max(f[q + d], g[min(p, q + d)][max(p, q + d)][!k]));
					}
			for(int j = 1; j <= M; ++j) f[j] = max(f[j], g[j][j][0]) + range_sum(j, j);
		}
		int ans = 100000000;
		for(int j = 1; j <= M; ++j) ans = min(ans, f[j]);
		return ans;
	}
}	user;
