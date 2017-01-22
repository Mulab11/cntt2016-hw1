/*
	dp
	dp[i][j] : last two wolves are i and j
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
const int MAXN = 320;
const int MOD = 1000000007;
int dp[MAXN][MAXN], sdp[MAXN][MAXN]; // sdp for prefix sum
int l[MAXN], r[MAXN];
class WolfInZooDivOne {
	public:
	int getargs(int* Dst, vector<string> Src){
		int ret = 0, p;
		string s; rep(i, 0, (int)Src.size() - 1) s += Src[i]; s += ' ';
		while ((p = s.find(' ')) != string::npos){
			Dst[++ret] = atoi(s.substr(0, p).c_str()) + 1; // +1s here
			s.erase(0, p + 1);
		}
		return ret;
	}
	int count(int n, vector <string> L, vector <string> R) {
		int m = getargs(l, L), ret = 1; getargs(r, R); // ret +1s for no wolves
		memset(dp, 0, sizeof dp); memset(sdp, 0, sizeof sdp);
		dp[0][0] = 1; rep(i, 0, n) sdp[i][0] = 1; // init
		rep(i, 0, n) rep(j, i + 1, n){
			int mi = i;
			rep(k, 1, m) if (l[k] <= i && r[k] >= j) mi = min(mi, l[k] - 1); // full, can't have more wolves after mi
			(ret += dp[i][j] = sdp[mi][i]) %= MOD;
			rep(k, i, n) sdp[k][j] = (sdp[k][j] + dp[i][j]) % MOD; // brute force upd
		}
		return ret;
	}
};

/*
	Wolf: I am Dangerous!
*/
