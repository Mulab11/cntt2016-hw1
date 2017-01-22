#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define bin(x) (1<<(x))
#define LX_JUDGE

using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

template<typename T> inline void upmax(T &x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T &x, T y) { x > y ? x = y : 0; }

const int mo = 1e9 + 7;
const int N = 1e6 + 10;

class WolfDelaymasterHard {
private :
	int str[N * 2];
	int Lef[N], Rig[N], Len[N];
	int dp[N], dif[N], sum[N];
	inline void upd(int &x, int y) {
		(x += y) >= mo ? x -= mo : 0;
	}
	inline int inc(int x, int y) {
		return (x += y) >= mo ? x - mo : x;
	}
	inline int dec(int x, int y) {
		return (x -= y) < 0 ? x + mo : x;
	}

	int DP(int n) {
		// 转移的情况(1) 的计算
		// (1) : w...o...
		{
			int lasto = -1, lastw = -1, lastow = -1, lastwo = -1;
			rep (i, 0, n*2) {
				if (i % 2 == 0) {
					int p = i / 2;
					Lef[p] = -1;
					if (lastw != -1) {
						int a = max((i - lastw + 1) / 2, 1);
						int b = min(i - lastw - 1, (i - lastow - 1) / 2);
						if (lastwo != -1) {
							a = max(a, i - lastwo);
						}
						if (a <= b) {
							Lef[p] = p - b;
							Rig[p] = p - a;
						}
					}
				}
				if (str[i] == 1) {
					lastw = i;
					lastow = lasto;
					lastwo = -1;
				} else if (str[i] == 2) {
					lasto = i;
					if (lastwo == -1) {
						lastwo = i;
					}
				}
			}
		}
		// 转移的情况(2) 的计算
		// (2) : ...o..
		{
			int nxto = n*2, nxtw = n*2;
			down (i, n*2, 0) {
				if (str[i] == 1)  nxtw = i;
				if (str[i] == 2)  nxto = i;
				if (i % 2 == 0) {
					int len = min((nxtw - i) / 2, nxto - i);
					Len[i / 2] = i / 2 + len;
				}
			}
		}
		// DP
		{
			int dsum = 0;
			dp[0] = 1;
			rep (i, 0, n) {
				if (Lef[i] != -1) {
					upd(dp[i], dec(sum[Rig[i] + 1], sum[Lef[i]]));
				}
				upd(dsum, dif[i]);
				upd(dp[i], dsum);
				sum[i + 1] = inc(sum[i], dp[i]);
				dif[i + 1] = inc(dif[i + 1], dp[i]);
				upd(dif[Len[i] + 1], mo - dp[i]);
			}
		}
		return dp[n];
	}
public :
	// DP，优化
	// 一个合法的方案可以被划分为一段段 www...ooo...
	// 定义 f[i] 表示前 i 个划分为若干段的方案数
	// 考虑转移，若 f[i] 能自 f[j] 转移过来，那么 (j+1, i) 有两种情况：
	// 1. (j+1, i) 中 w 的那一段至少出现了一个 'w'  
	// 2. (j+1, i) 中 w 的那一段均为 '?'  
	// 观察发现，第一种转移在固定 i 之后，它能接受的转移 j 是一段区间，可以用前缀和优化
	// 第二种转移在固定 j 之后，j 更新到的状态是一段区间，可以使用前缀和优化  
	// 时间复杂度 O(n)
	int countWords(int n, int wlen, int w0, int wm, int wa,
			int olen, int o0, int om, int oa) {
		int x = w0;
		rep (i, 1, wlen) {
			str[x] = 1;
			x = ((LL) x * wm + wa) % n;
		}
		x = o0;
		rep (i, 1, olen) {
			str[x] = 2;
			x = ((LL) x * om + oa) % n;
		}
		int ans = DP(n / 2);
		return ans;
	}
};
