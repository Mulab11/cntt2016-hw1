#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

int f[1 << 13][140];
bool g[1 << 13];
// f[s][u]: 集合为 s，恰好用了 u 个 A 钥匙时，最多用了多少个 B 钥匙（以最小化通用钥匙）

class KeyDungeonDiv1
{
public:
	int maxKeys(vector<int> V0, vector<int> V1, vector<int> V2, vector<int> V3, vector<int> V4, vector<int> V5)
	{
#define dmin(a, b) ((a) < (b) ? (a) : (b))
#define cmax(a, b) ((a) < (b) ? (a) = (b) : 0)
		int n = V0.size();
		int *v0 = V0.data();
		int *v1 = V1.data();
		int *v2 = V2.data();
		int *v3 = V3.data();
		int *v4 = V4.data();
		int *v5 = V5.data();
		// 如果开启的门的集合给定，最终的钥匙也确定了
		// 因此只需要判断每个集合能否到达
		int ans = 0;
		// 清空数组
		for(int s = 0; s != (1 << n); ++s) memset(f[s], -1, 131 << 2);
		f[0][0] = 0;
		g[0] = 1;
		for(int s = 0; s != (1 << n); ++s) if(g[s])
		{
			int need_A = 0, need_B = 0;
			int have_A = v5[0], have_B = v5[1], have_C = v5[2];
			// 先统计当前状态默认 3 种钥匙的数量
			for(int i = 0; i != n; ++i) if(s & (1 << i))
			{
				need_A += v0[i];
				need_B += v1[i];
				have_A += v2[i];
				have_B += v3[i];
				have_C += v4[i];
			}
			cmax(ans, have_A - need_A + have_B - need_B + have_C);
			// 进行 DP
			for(int u = 0; u <= 130; ++u) if(f[s][u] >= 0)
			{
				// 当前的 3 种钥匙数量
				const int used_A = u, used_B = f[s][u];
				const int A = have_A - used_A, B = have_B - used_B, C = have_C - (need_A + need_B - used_A - used_B);
				int a, b;
				// 考虑转移给下一个还没开启的门
				for(int i = 0; i != n; ++i) if(~s & (1 << i))
				{
					a = dmin(A, v0[i]);
					b = dmin(B, v1[i]);
					if(v0[i] - a + v1[i] - b > C) continue;	// 挂掉了
					g[s | (1 << i)] = 1;
					cmax(f[s | (1 << i)][used_A + a], used_B + b);
				}
			}
		}
		return ans;
	}
}   user;
