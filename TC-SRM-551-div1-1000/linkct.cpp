#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef pair <int, int> pii;
typedef long long int LL;
const int MAXN = 43;
const LL MOD = 1000000007LL;

class SweetFruits{
	public:
		int n, m, tot[MAXN], sweet[MAXN], g[MAXN][MAXN], maxv, C[MAXN][MAXN];
		LL select[MAXN]; vector <pii> st1, st2; vector <int> val;
		LL getInv(LL x){
			int ep = MOD - 2; LL ret = 1LL;
			while(ep){
				if(ep & 1) (ret *= x) %= MOD;
				(x *= x) %= MOD, ep >>= 1;
			} return ret;
		}
		void dfs(int cur, int ed, int cnt, int sum, vector <pii> &res){
			if(sum > maxv) return;
			if(cur > ed){
				res.push_back(pii(sum, cnt));
				return;
			}
			dfs(cur + 1, ed, cnt + 1, sum + val[cur], res);
			dfs(cur + 1, ed, cnt, sum, res);
		}
		int solveMatrixTree(int scnt){             //scnt: number of nodes which are "truly sweet"
			int i, j, k; LL ret = 1LL, cur, inv;   //Calculate the number of trees whose "truly sweet" nodes are a subset of [1, scnt], using matrix tree theorem
			for(i = 1; i <= n; ++ i)
				for(j = 1; j <= n; ++ j)
					if(i == j) g[i][j] = n - 1;
					else g[i][j] = MOD - 1;
			for(i = 1; i <= m; ++ i)
				for(j = max(i, scnt) + 1; j <= m; ++ j){
					g[i][j] = g[j][i] = 0;
					-- g[i][i], -- g[j][j];
				}
			for(i = 1; i < n; ++ i){
				for(j = i; j < n; ++ j)
					if(g[j][i]) break;
				if(j == n) return 0;
				if(j != i) for(ret = - ret, k = i; k < n; ++ k)
					swap(g[i][k], g[j][k]);
				for(j = i + 1, inv = getInv(g[i][i]); j < n; ++ j){
					if(!g[j][i]) continue;
					for(k = i, cur = inv * g[j][i] % MOD; k < n; ++ k)
						if((g[j][k] = (g[j][k] - cur * g[i][k]) % MOD) < 0)
							g[j][k] += MOD;
				}
			} ret = (ret + MOD) % MOD;
			for(i = 1; i < n; ++ i)
				(ret *= g[i][i]) %= MOD;
			return ret;
		}
		int countTrees(vector <int> val_, int mxSwt){
			int i, j, k, ans = 0; val = val_;
			n = val.size(); maxv = mxSwt;
			sort(val.begin(), val.end());
			st1.clear(); st2.clear();
			for(m = 0; m < n && val[n - m - 1] != -1; ++ m) ;
			dfs(n - m, n - (m >> 1) - 1, 0, 0, st1);
			dfs(n - (m >> 1), n - 1, 0, 0, st2);
			sort(st1.begin(), st1.end());
			sort(st2.begin(), st2.end());
			for(j = 0; j < int(st2.size()); ++ j)
				++ tot[st2[j].se];
			for(i = 0; i < int(st1.size()); ++ i){
				while(j && st2[j - 1].fi + st1[i].fi > maxv)
					-- tot[st2[-- j].se];
				for(k = 0; k <= m; ++ k)
					select[st1[i].se + k] += tot[k];
			}
			for(i = 0; i <= m; ++ i)
				for(j = C[i][0] = 1; j <= i; ++ j)
					if((C[i][j] = C[i - 1][j] + C[i - 1][j - 1]) >= MOD)
						C[i][j] -= MOD;
			for(i = 0; i <= m; ++ i){
				sweet[i] = solveMatrixTree(i);
				for(j = 0; j < i; ++ j)
					if((sweet[i] = (sweet[i] - LL(C[i][j]) * sweet[j]) % MOD) < 0)
						sweet[i] += MOD;
				ans = ((select[i] % MOD) * sweet[i] + ans) % MOD;
			} return ans;
		}
};
