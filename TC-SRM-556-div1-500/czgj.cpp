/*
	Dp.
	A prefix of digits[] makes a substring of lowerBound[].
	dp[l][r][flag = 0/1] = the smallest permutation of digits[0..(r-l)] that is greater than (or equal, when flag = 0) lowerBound[l..r].
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
using namespace std;
const int MAXN = 60;
string dp[MAXN][MAXN][2];
string mi[MAXN];
class LeftRightDigitsGame2 {
	public:
	string minNumber(string dg, string lb) {
		int n = dg.length();
		rep(i, 1, n) mi[i] = min(mi[i - 1] + dg[i - 1], dg[i - 1] + mi[i - 1]); // Smallest permutation of prefix[i]
		rep(i, 0, n - 1){ // Initialization, "" = fail
			dp[i][i][0] = dg[0] >= lb[i] ? dg.substr(0, 1) : "";
			dp[i][i][1] = dg[0] > lb[i] ? dg.substr(0, 1) : "";
		}
		rep(d, 1, n - 1) rep(i, 0, n - d - 1){
			int j = i + d;
			bool f = dg[d] < lb[j];
			string s1 = dp[i][j - 1][f] == "" ? "" : dp[i][j - 1][f] + dg[d]; // right
			string s2 = dg[d] < lb[i] ? "" : dg[d] == lb[i] ? dp[i + 1][j][0] == "" ? "" : dg[d] + dp[i + 1][j][0] : dg[d] + mi[d]; // left
			dp[i][j][0] = s1 == "" ? s2 : s2 == "" ? s1 : min(s1, s2);
			
			f = dg[d] <= lb[j];
			s1 = dp[i][j - 1][f] == "" ? "" : dp[i][j - 1][f] + dg[d]; // right
			s2 = dg[d] < lb[i] ? "" : dg[d] == lb[i] ? dp[i + 1][j][1] == "" ? "" : dg[d] + dp[i + 1][j][1] : dg[d] + mi[d]; // left
			dp[i][j][1] = s1 == "" ? s2 : s2 == "" ? s1 : min(s1, s2);
		}
		return dp[0][n - 1][0];
	}
};

/*
	Subete wa Steins Gate no sentaku da!
*/
