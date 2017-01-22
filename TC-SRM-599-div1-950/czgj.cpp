/*
	Tree state-compressed dp
	Pre-process to reduce number of states
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
const int MAXN = 63;
const int MOD = 1e9 + 7;
vector<int> state, trans[1 << 16];
vector<int> id, G[MAXN];
bool valid[1 << 16];
int H[MAXN];
int dp[MAXN][1 << 16];
int n, m;
int find(int x){ // find x in id
	return lower_bound(id.begin(), id.end(), x) - id.begin();
}
int fac(int n){
	int ret = 1;
	rep(i, 1, n) ret = (LL)ret * i % MOD;
	return ret;
}
void dfs(int x){
	dp[x][0] = 1;
	for (int y : G[x]){
		dfs(y);
		for (int i : state) for (int j : trans[i])
			dp[x][i] = (dp[x][i] + (LL)dp[x][i ^ j] * dp[y][j]) % MOD;
	}
	if (x != n){
		for (int i : state) rep(j, 0, m - 1)
			if ((~i >> j & 1) && (i & H[j]) == H[j])
				(dp[x][i | 1 << j] += dp[x][i]) %= MOD;
	}
}
class SimilarNames {
	public:
	int count(vector <string> st, vector <int> u, vector <int> v) {
		memset(dp, 0, sizeof dp);
		memset(H, 0, sizeof H);
		memset(valid, 0, sizeof valid);
		rep(i, 0, (1 << 16) - 1) trans[i].clear();
		rep(i, 0, 60) G[i].clear();
		id.clear();
		state.clear();
		
		n = st.size(); m = u.size();
		st.push_back(""); // add a node of empty string
		
		// make tree
		rep(i, 0, n - 1){ 
			int f = -1, l = -1;
			rep(j, 0, n) if (i != j && l < (int)st[j].length() && st[i].substr(0, st[j].length()) == st[j])
				l = st[j].length(), f = j;
			G[f].push_back(i);
		}
		
		// discretize the numbers
		rep(i, 0, m - 1) id.push_back(u[i]), id.push_back(v[i]);
		sort(id.begin(), id.end());
		id.resize(unique(id.begin(), id.end()) - id.begin());
		m = id.size();
		
		// make masks, H[u] = {v | u should be an ancestor of v}
		rep(i, 0, m - 1) H[find(u[i])] |= 1 << find(v[i]);
		
		// pre-process valid states
		red(i, (1 << m) - 1, 0){
			bool ok = 1;
			rep(j, 0, m - 1) if (i >> j & 1 && (i & H[j]) != H[j]) {ok = 0; break;}
			if (ok) {state.push_back(i); valid[i] = 1;}
		}
		// pre-process valid transfers
		for (int i : state)
			for (int j = i; j; j = (j - 1) & i)
				if (valid[j] && valid[i ^ j])
					trans[i].push_back(j);
		// run!
		dfs(n);

		return (LL)dp[n][(1 << m) - 1] * fac(n - m) % MOD;
	}
};

/*
	Annoying TLE...
*/
