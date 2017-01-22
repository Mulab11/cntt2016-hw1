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

const int inf = 0x3f3f3f3f;

class FlippingBitsDiv1 {
private :
	int str[305];
	int n, M, T;

	// M 较小的情况下，暴力枚举循环节长什么样
	int SolveM() {
		int rest = n % M;
		int ans = inf;
		int dp[2][2];		// dp[i][0/1] 表示从后向前处理到第 i 节，1~i 节有没有取反的方案数，滚动数组优化
		rep (s, 0, bin(M) - 1) {			//2^M 枚举
			int t = 0;
			dp[t][0] = 0;
			dp[t][1] = inf;
			rep (i, 0, rest-1) {		// 计算不足 M 位的零散部分
				dp[t][0] += ((s >> i) & 1) == str[n-rest+i];
			}
			for (int j = n-rest-M; j >= 0; j -= M) {		//对每一节进行DP
				int c1 = 0;
				rep (i, 0, M-1) {
					c1 += ((s >> i) & 1) == str[j + i];
				}
				dp[t ^ 1][0] = min(dp[t][0] + c1, dp[t][1] + c1 + 1);
				dp[t ^ 1][1] = min(dp[t][1] + M-c1, dp[t][0] + M-c1 + 1);
				t ^= 1;
			}
			upmin(ans, min(dp[t][0], dp[t][1]));
		}
		return ans;
	}
	// n / m 较小的情况下，暴力枚举哪些前缀会使用操作 2
	int SolveT() {
		static int ts[305];
		int rest = n % M;
		// 最后不足 k 位的零散部分恒定
		rep (i, n-rest, n-1)  ts[i] = str[i];
		int ans = inf;
		rep (s, 0, bin(T) - 1) {		// 2^T 枚举
			int res = 0;
			// 计算经过若干次前缀操作之后得到的串
			for (int j = n-rest, t=s, col = 0; j; j -= M, t >>= 1) {
				if (t & 1) {
					++res, col ^= 1;
				}
				rep (i, j-M, j-1) {
					ts[i] = str[i] ^ col;
				}
			}
			rep (i, 0, M-1) {			// mod M 相同的位同时处理，决定这些位取 0 或 1
				int a = 0, b = 0;
				for (int j = i; j < n; j += M) {
					ts[j] == 1 ? ++a : ++b;
				}
				res += min(a, b);
			}
			upmin(ans, res);
		}
		return ans;
	}
public :
	// 算法复合，暴力枚举，循环串
	// 复杂度 O(2^{\sqrt n}n)
	int getmin(vector<string> S, int M) {
		rep (i, 0, S.size()-1) {
			rep (j, 0, S[i].size()-1) {
				str[n++] = S[i][j] - '0';
			}
		}
		this->M = M;
		T = n / M;
		int ans = M <= T ? SolveM() : SolveT();
		return ans;
	}
};
