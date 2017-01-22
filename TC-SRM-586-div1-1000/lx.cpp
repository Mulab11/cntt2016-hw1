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

class StringWeight {
private :
	inline int sum1(int x) {
		return x * (x + 1) / 2;
	}
	int dp[2][27][27];
	// dp[x][i][j] 表示处理到第 x 个串，有 i 个字符已经出现，j 个字符将来还要出现的最优代价
	int n;
public :
	// DP, 贪心
	int getMinimum(vector<int> L) {
		n = L.size();
		int tot = 0, t = 0;
		memset(dp[t], 0x3f, sizeof(dp[t]));
		dp[t][0][0] = 0;
		rep (i, 0, n-1) {
			memset(dp[t ^ 1], 0x3f, sizeof(dp[t ^ 1]));
			int len = min(L[i], 26), v = L[i] - len;
			rep (j, 0, 26) rep (k, 0, j) {
				if (dp[t][j][k] < inf) {
					int x = dp[t][j][k];
					rep (a, max(len-k, 0), min(26-j, len)) rep (b, 0, min(len, a+k)) {
						int c = max(b - k, 0);
						int p = sum1(b - c) + (b - c) * tot;
						int q = sum1(a - c) + (a - c) * (tot + L[i] - a + c);
						upmin(dp[t ^ 1][j + a][k + a - b], x + p - q + (b < k ? 0 : v));
					}
				}
			}
			tot += L[i];
			t ^= 1;
		}
		printf("%d\n", dp[t][26][0]);
		int ans = inf;
		rep (i, 0, 26) upmin(ans, dp[t][i][0]);
		return ans;
	}
};
