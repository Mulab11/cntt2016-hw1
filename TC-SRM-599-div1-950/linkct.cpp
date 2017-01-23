#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef pair <int, int> pii;
typedef long long int LL;
const LL MOD = 1000000007LL;
const int MAXN = 55;

bool cmp(const string &a, const string &b){return a.length() < b.length();}
class SimilarNames{
public:
	int n, id[265005], ST, m, M, g[MAXN], nx[MAXN], to[MAXN], edgeSize, q;
	int status[6605]; LL f[MAXN][6605]; vector <pii> nxt[6605];
	void dfs(int x){
		memset(f[x], 0, sizeof(f[x]));
		int p, i, j; LL *dp = f[x], *dp2, tmp;
		dp[id[0]] = 1LL;
		for(p = g[x]; p; p = nx[p]){
			dfs(to[p]); dp2 = f[to[p]];
			for(i = ST; i; -- i){
				for(j = tmp = 0; j < int(nxt[i].size()); ++ j)
					tmp = (tmp + dp2[nxt[i][j].fi] * dp[nxt[i][j].se]) % MOD;
				dp[i] = tmp;
			}
		}
		if(!x) return;
		for(i = ST; i; -- i)
			for(j = 0; j < m; ++ j)
				if((status[i] & (1 << j)) == 0 && id[status[i] | (1 << j)])
					(dp[id[status[i] | (1 << j)]] += dp[i]) %= MOD;
	}
	void addEdge(int u, int v){
		nx[++ edgeSize] = g[u];
		to[g[u] = edgeSize] = v;
	}
	int count(vector <string> names, vector <int> info1, vector <int> info2){
		int i, j; LL ret = 1LL; n = names.size();
		sort(names.begin(), names.end(), cmp);
		for(i = 0; i < n; ++ i){
			for(j = i - 1; j >= 0; -- j)
				if(names[i].substr(0, names[j].length()) == names[j])
					break;
			if(j >= 0) addEdge(j + 1, i + 1);
			else addEdge(0, i + 1);
		}
		q = info1.size();
		vector <int> tmp = info1;
		for(i = 0; i < q; ++ i)
			tmp.push_back(info2[i]);
		sort(tmp.begin(), tmp.end());
		tmp.resize(unique(tmp.begin(), tmp.end()) - tmp.begin());
		for(i = 0; i < q; ++ i)
			info1[i] = lower_bound(tmp.begin(), tmp.end(), info1[i]) - tmp.begin();
		for(i = 0; i < q; ++ i)
			info2[i] = lower_bound(tmp.begin(), tmp.end(), info2[i]) - tmp.begin();
		for(i = ST = 0, m = tmp.size(), M = 1 << m; i < M; ++ i){
			for(j = 0; j < q; ++ j)
				if(((i & (1 << info1[j])) != 0) && ((i & (1 << info2[j])) == 0))
					break;
			if(j < q) continue;
			status[id[i] = ++ ST] = i;
			for(j = i; j; j = (j - 1) & i)
				if(id[j])
					nxt[id[i]].push_back(pii(id[j], id[i ^ j]));
			nxt[id[i]].push_back(pii(id[0], id[i]));
		}
		dfs(0);
		ret = f[0][ST];
		for(i = 1; i <= n - m; ++ i)
			ret = ret * i % MOD;
		return ret;
	}
};
