#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
const LL MOD = 1000000007LL;
const int MAXN = 55, INF = 1000000000;

class EqualSums{
public:
	int n, val[MAXN * 2], mn[MAXN * 2], mx[MAXN * 2], f[MAXN * 2];
	int find(int x){
		if(x == f[x]) return x;
		int fa = find(f[x]);
		val[x] += val[f[x]];
		return f[x] = fa;
	}
	bool merge(int u, int v, int w){
		int u_ = find(u), v_ = find(v), dt = w + val[v] - val[u];
		if(u_ == v_) return val[u_] == dt;
		f[u_] = v_, val[u_] = dt;
		mn[v_] = min(mn[v_], mn[u_] + dt);
		mx[v_] = max(mx[v_], mx[u_] + dt);
		return true;
	}
	int count(vector <string> g){
		int i, j; n = g.size();
		LL ans = 1LL, ans_ = 1LL;
		memset(val, 0, sizeof(val));
		for(i = 0; i < 2 * n; ++ i){ //0..n-1 denote row[i], n..2n-1 denote -column[i-n]; mn denotes minimum of row[], mx denotes maximum of -column[]
			f[i] = i;
			if(i < n) mn[i] = 0, mx[i] = -INF;
			else mn[i] = INF, mx[i] = 0;
		}
		for(i = 0; i < n; ++ i)
			for(j = 0; j < n; ++ j)
				if(g[i][j] != '-' && !merge(i, j + n, g[i][j] - '0'))
					return 0;
		for(i = 0; i < 2 * n; ++ i){
			if(find(i) != i) continue;
			mx[i] = mn[i] - mx[i]; //minimum of column[] when minimum of row[] is set to 0
			if(mx[i] < 0) return 0;
			(ans *= (mx[i] + 1)) %= MOD; //Raise row[] and decrease column[] to get other solutions
			(ans_ *= mx[i]) %= MOD; //Number of solutions without any row[] equal to 0
		} return (ans - ans_ + MOD) % MOD;
	}
};
