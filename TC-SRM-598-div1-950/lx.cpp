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

class TPS {
public :
	vector<string> adj;
	int dp[50][51][2], n;
	int treeDp(int x, int fa, bool flag) {		// x 为根的子树，父亲为 fa，是否必须放关键点
		int &ans = dp[x][fa][flag];
		if (ans == -1) {
			int sum = 0;
			int c = 0;
			rep (y, 0, n - 1) {
				if (fa != y && (adj[x][y] == 'Y')) {		//首先计算每个子树都放关键点
					c++;
					sum += treeDp(y, x, true);
				}
			}
			if (c == 0) {
				ans = flag;
			} else {
				ans = n;
				int num = n;
				rep (y, 0, n - 1) {			//允许一个子树中不放关键点，枚举之  
					if (fa != y && (adj[x][y] == 'Y')) {
						num = min(num, sum - treeDp(y, x, true) + treeDp(y, x, false));
					}
				}
				ans = min(ans, num + 1);
				if (fa != n) {
					if (flag && c == 1) {
						ans = min(ans, sum);
					} else {
						ans = min(ans, num);
					}
				}
			}
		}
		return ans;
	}
	 
	//树形DP：方案合法的充要条件：枚举根，对每个子树来说，至多一个分支中可以不放关键点。  
	int minimalBeacons(vector<string> adj) {
		memset(dp, -1, sizeof(dp));
		this->adj = adj;
		n = adj.size();
		int ans = n;
		rep (r, 0, n - 1) {			//枚举根，根一定是关键点
			ans = min(ans, treeDp(r, n, false));
		}
		return ans;
	}
};
