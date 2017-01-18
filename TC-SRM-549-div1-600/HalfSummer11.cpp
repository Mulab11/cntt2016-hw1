#line 2 "MagicalHats.cpp"
#include<vector>
#include<list>
#include<map>
#include<set>
#include<deque>
#include<stack>
#include<bitset>
#include<algorithm>
#include<functional>
#include<numeric>
#include<utility>
#include<sstream>
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<cstring>
#define cl(x) memset(x, 0, sizeof(x));
#define pii pair<int, int>
#define fr first
#define sc second
#define mp make_pair
#define pb push_back
#define oo 0x3f3f3f3f
#define maxs 1595000
#define maxn 20
typedef long long ll;
using namespace std;
int n, m, w, h, limit, x[maxn], y[maxn]; // n 顶帽子，m 个硬币，limit是最多能猜的次数，w/h是方格的尺寸，x/y是帽子的横纵坐标
// sta是一个n位3进制数，第i位为0表示这个帽子没有被揭开，为1表示这个帽子被揭开，且下面是空的，为2表示这个帽子被揭开，且下面有一枚硬币
bool g[maxs], vis[maxs]; // g[sta]表示状态为sta时，是否能按照题目要求合法地摆放硬币，vis是记忆化搜索的辅助数组
int f[maxs]; // f[sta] 表示目前的状态为sta时，猜的人通过最优策略能够得到的最多硬币数
int tri[maxn]; // tri[i] = 3 ^ i
int isx, isy; // 只考虑帽子，各行/列和的奇偶性分别压成isx和isy
int dp(int sta) {
	if (vis[sta]) return f[sta];
	if (!g[sta]) return f[sta];
	vis[sta] = 1;
	int tmp = sta, cnt = 0, sum = 0;
	for (int i = 0; i < n; ++i) {
		if (tmp % 3) ++cnt; // 记录被揭开的帽子总数
		if (tmp % 3 == 2) ++sum; // 被揭开的帽子中硬币数之和
		tmp /= 3;
	}
	f[sta] = max(f[sta], sum); // 不再揭开帽子，得到的就是sum个硬币
	if (cnt == limit) return f[sta]; // 不能继续猜了
	tmp = sta;
	for (int i = 0; i < n; ++i) {
		if (tmp % 3 == 0) { // 揭开第i个帽子
			if (g[sta + tri[i]] && g[sta + 2 * tri[i]]) { // 如果第i个帽子下不放硬币/放硬币，都有合法的方案，魔术师取收益尽量小的一种方法
				f[sta] = max(f[sta], min(dp(sta + tri[i]), dp(sta + 2 * tri[i])));
			} else {
				if (g[sta + 2 * tri[i]])
					f[sta] = max(f[sta], dp(sta + 2 * tri[i])); // 否则就只能在第i个帽子下面放硬币
			}
		}
		tmp /= 3;
	}
	return f[sta];
}
class MagicalHats {
	public:
		int findMaximumReward(vector <string> board, vector <int> coins, int lim) {
			m = coins.size(); n = 0; limit = lim;
			sort(coins.begin(), coins.end()); // 得到的硬币必然是面值最小的若干枚
			isx = 0; isy = 0;
			w = board.size(); h = board[0].size();
			for (int i = 0; i < w; ++i)
				for (int j = 0; j < h; ++j)
					if (board[i][j] == 'H') {
						x[++n] = i; y[n] = j;
						isx ^= (1 << i); isy ^= (1 << j);
					}
			tri[0] = 1; for (int i = 1; i <= n; ++i) tri[i] = 3 * tri[i - 1];
			cl(g);
			for (int s = 0; s < (1 << n); ++s) { // 枚举所有硬币在帽子下的摆放情况
				if (__builtin_popcount(s) != m) continue;
				int sx = isx, sy = isy;
				for (int u = s; u; u -= (u & (-u))) { 
					int num = int(log2(u & (-u)));
					sx ^= (1 << x[num + 1]);
					sy ^= (1 << y[num + 1]);
				}
				if (sx == 0 && sy == 0) { // 若这种摆放情况满足题目条件
					for (int t = s; ; t = (t - 1) & s) { // 枚举s的子集t，表示这些硬币中，上面的帽子已经被揭开的集合
						int sta = 0;
						for (int i = 0; i < n; ++i) {
							if (t & (1 << i)) // 集合t对应sta中被揭开且下面有硬币的帽子集合
								sta += tri[i] * 2;
							if (!(s & (1 << i))) // 不在s中的帽子没有放硬币，它们上面的帽子可以揭开，也可以没有揭开，这里先按照揭开了处理
								sta += tri[i] * 1;
						}
						g[sta] = 1;
						if (! t) break;
					}
				}
			}
			for (int s = tri[n] - 1; s >= 0; --s) {
				if (! g[s]) continue;
				int tmp = s;
				for (int i = 0; i < n; ++i) { // 任何一个合法状态，把任何数位上的1变成0之后，得到的依然是合法的状态
					if (tmp % 3 == 1) g[s - tri[i]] |= g[s]; 
					tmp /= 3;
				}
			}
			if (!g[0]) return -1;
			memset(f, -0x3f, sizeof(f));
			cl(vis);
			int cnt = dp(0), ans = 0;
			for (int i = 0; i < cnt; ++ i) ans += coins[i];
			return ans;
		}
};

