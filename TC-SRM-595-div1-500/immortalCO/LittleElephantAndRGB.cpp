#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

int n;
char str[2510];
int f[2510], g[2510];
int Lef[2510];				// 右端点不超过 i 的所有不满足条件的区间个数
int Rig[2510], sum[2510];	// 当前情况下（外面枚举了左区间），右边的所有不满足条件且开头有 i 个 G 的个数
bool good[2510][2510];

class LittleElephantAndRGB
{
public:
	ll getNumber(vector<string> input, int lim)
	{
		for(int i = 0; i != (int) input.size(); ++i)
			for(int j = 0; j != (int) input[i].size(); ++j)
				str[++n] = input[i][j];
		// DP 预处理出一个位置往前、后有多少个连续 G
		for(int i = 1; i <= n; ++i) f[i] = (str[i] == 'G' ? f[i - 1] + 1 : 0);
		for(int i = n; i >= 1; --i) g[i] = (str[i] == 'G' ? g[i + 1] + 1 : 0);
		// 有两种情况：至少有一区间就已经包含连续 lim 个 G，以及两个区间都包含。
		// 第一种情况可以直接枚举
#define CountRanges(n) (((n) * (n + 1)) >> 1)
		ll ans = 0;
		for(int l = 1; l <= n; ++l)
		{
			const int CurLeft = Lef[l - 1];
			// 左边的不满足条件的区间个数
			bool done = 0;
			for(int r = l; r <= n; ++r)
			{
				if(min(f[r], r - l + 1) >= lim) done = 1;
				if((good[l][r] = done))
				{
					// 作为左区间统计答案，则右区间间可以任意
					// 作为右区间统计答案，左区间必须非法，否则会计算重复
					ans += CountRanges(n - r) + CurLeft;
				}
				else ++Lef[r];
			}
			Lef[l] += Lef[l - 1];
		}
		// 第二种情况呢，必然是在接合部分有连续的超过 lim 个东西
		// 先枚举一下右边的区间
		for(int l = 1; l <= n; ++l)
			for(int r = l; r <= n && !good[l][r]; ++r)
				++Rig[min(g[l], r - l + 1)];
		// 枚举左边的区间右端点
		for(int r = 1; r <= n; ++r)
		{
			// 删除不合法的右边的区间
			for(int t = r; t <= n && !good[r][t]; ++t)
				--Rig[min(g[r], t - r + 1)];
			// 预处理后缀和（只需要预处理到 lim，超过无意义）
			for(int i = lim; i >= 1; --i) sum[i] = sum[i + 1] + Rig[i];
			// 枚举左边的不合法的区间
			for(int l = r; l >= 1 && !good[l][r]; --l)
				ans += (ll) sum[lim - min(f[r], r - l + 1)];
		}
		return ans;
	}
}   user;
