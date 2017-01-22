/*
	Combinatorics
	Brute force
	Knapsack dp
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
const int MAXN = 60;
LL C[MAXN][MAXN], dp[MAXN];
int cnt[MAXN];
vector<int> a[MAXN];
bool mark[MAXN];
int n;
class Excavations {
	public:
	long long count(vector <int> kind, vector <int> depth, vector <int> found, int K) {
		n = kind.size();
		rep(i, 0, n) rep(j, 0, i) C[i][j] = j ? C[i - 1][j] + C[i - 1][j - 1] : 1;
		
		memset(mark, 0, sizeof mark);
		rep(i, 1, 50) a[i].clear();
		rep(i, 0, n - 1) a[kind[i]].push_back(depth[i]);
		rep(i, 1, 50) sort(a[i].begin(), a[i].end()), cnt[i] = a[i].size();
		rep(i, 0, (int)found.size() - 1) mark[found[i]] = 1;
		
		vector<int> d(depth); sort(d.begin(), d.end());
		int vn = unique(d.begin(), d.end()) - d.begin();
		LL ret = 0;
		rep(i, 0, vn){ // Fix D, let it be the depth of some not-found.
			int D = i < vn ? d[i] : 1e9, equ = 0, ge = 0;
			rep(j, 0, n - 1) if (!mark[kind[j]]) equ += (depth[j] == D), ge += (depth[j] >= D);
			if (i < vn && !equ) continue; // invalid D
			memset(dp, 0, sizeof dp); dp[0] = 1;
			rep(j, 1, 50) if (mark[j]){
				int p = lower_bound(a[j].begin(), a[j].end(), D) - a[j].begin(); // Count of buildings whose d < D
				red(k, K, 0){ // knapsack dp
					dp[k] = 0;
					rep(t, 0, k - 1)
						dp[k] += dp[t] * (C[cnt[j]][k - t] - C[cnt[j] - p][k - t]); // must choose one from p
				}
			}
			if (i == vn) ret += dp[K]; // spj
			if (i < vn) rep(j, 0, K) ret += dp[j] * (C[ge][K - j] - C[ge - equ][K - j]); // must choose one from equ
		}
		return ret;
	}
};

/*
	Futsuu desu kedo ...
	Chotto tsumaranai ...
*/

