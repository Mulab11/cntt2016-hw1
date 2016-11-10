#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

// 每种字母出现位置
ll set_s[26], set_t[26];
int goal[26], d[26];

int dmod(int x) {x %= 26; return x < 0 ? x + 26 : x;}

class NextAndPrev
{
public:
	int getMinimum(int next, int prev, string s, string t)
	{
		if(s == t) return 0;
		for(int i = 0; i != (int) s.size(); ++i)
		{
			set_s[s[i] - 'a'] += 1ll << i;
			set_t[t[i] - 'a'] += 1ll << i;
		}
		// 操作只会让字母数量减小
		// 字母出现的位置集合，必然是若干个 s 并起来为一个 t
		int tot_s = 0, tot_t = 0;
		memset(goal, -1, 26 << 2);
		for(int i = 0; i != 26; ++i)
		{
			for(int j = 0; j != 26; ++j)
			{
				if((set_t[i] & set_s[j]) == 0) continue;	// 无相交
				else if((set_t[i] | set_s[j]) == set_t[i]) 	// 包含
					goal[j] = i;
				else return -1;								// 无解
			}
			if(set_s[i]) ++tot_s;
			if(set_t[i]) ++tot_t;
		}
		//字母种类数不能变多
		// 注意！！！！如果达到 26，且两个串不等，那么无解（移动必然合并）
		if(tot_s < tot_t || tot_t == 26) return -1;
		// 相当于在环上面有一些点，点向左向右移动可以获得代价
		// 点不能穿过别的点，但可以和相邻的点合并
		// 所以：每个点都必须是环上一段相邻的区间，并且顺序相同
		int n = 0;
		for(int i = 0; i != 26; ++i) if(goal[i] != -1) d[n++] = i;
		// 找到一个合法的起点，使得所有的终点递增
		// 如果合法，这样的起点一定能找到
		int ans = 1.1e9;
		for(int p = 0; p != n; ++p)
		{
			for(int i = 1; i != n; ++i)
				if(goal[dmod(d[i - 1])] > goal[dmod(d[i])])
					goto failed;
			// 由于某个方向的费用可能很大，我们得枚举强制旋转的圈数
			// 注意：不同的起点可能引起不同的费用！
			for(int mov = -10; mov <= +10; ++mov)
			{
				for(int i = 0; i != n; ++i) d[i] += 26 * mov;
				// 统计费用
				int cur = 0;
				for(int l = 0, r; l != n; l = r + 1)
				{
					const int G = goal[dmod(d[l])];
					for(r = l; r + 1 < n && G == goal[dmod(d[r + 1])]; ++r)
						;
					// 在区间 [l, r] 内的终点是同一个！
					cur += (G - min(G, d[l])) * next + (max(G, d[r]) - G) * prev;
				}
				if(cur < ans) ans = cur;
				for(int i = 0; i != n; ++i) d[i] -= 26 * mov;
			}
		failed:
			d[0] += 26; sort(d, d + n);
		}
		return ans > 1e9 ? -1 : ans;
	}
}	user;
