/*
	state-compressed dp.
*/

#include <bits/stdc++.h>
using namespace std;
const int INF = 0x0F000000;
int n, m, h, c, g;
vector<pair<int, int> > hats;
int dp[2000000], pow3[15];
bool vis[2000000];

int setbit(int state, int at, int d){
	return state / pow3[at + 1] * pow3[at + 1] + d * pow3[at] + state % pow3[at];
}
int getbit(int state, int at){
	return state / pow3[at] % 3;
}

int dfs(int state, int dep, int cntc, int cntx, int cnty){
	if (vis[state]) return dp[state];
	vis[state] = 1;
	if (dep > h) return dp[state] = cntc == c && !cntx && !cnty ? 0 : INF;
	int ret = 0;
	for (int i = 0; i < h; ++i)
		if (!getbit(state, i)){
			int x = hats[i].first, y = hats[i].second;
			int r1 = INF, r2 = INF;
			if (cntc < c){ // has a coin
				r1 = dfs(setbit(state, i, 1), dep + 1, cntc + 1, cntx ^ (1 << x), cnty ^ (1 << y)) + (dep <= g);
				// if dep > g: this should not count as a guess
			}
			r2 = dfs(setbit(state, i, 2), dep + 1, cntc, cntx, cnty); // has no coin
			ret = max(ret, min(r1, r2));
		}
	return dp[state] = ret;
}
class MagicalHats {
	public:
	int findMaximumReward(vector <string> board, vector <int> val, int ng) {
		memset(vis, 0, sizeof vis); hats.clear();
		pow3[0] = 1; for (int i = 1; i <= 13; ++i) pow3[i] = pow3[i - 1] * 3;
		n = board.size(); m = board[0].size();
		int cx = 0, cy = 0;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j)
				if (board[i][j] == 'H'){
					hats.push_back(make_pair(i, j));
					cx ^= 1 << i;
					cy ^= 1 << j;
				}
		h = hats.size(); c = val.size(); g = ng;
		
		int cnt = dfs(0, 1, 0, cx, cy);
		sort(val.begin(), val.end());
		int ret = 0;
		if (cnt <= c){ // cnt != INF (has legal solution)
			for (int i = 0; i < cnt; ++i)
				ret += val[i];
		}
		else ret = -1;
		return ret;
	}
};

/*
	'Who's afraid of the Big Black?
	aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa'
		- The Big Black
*/
