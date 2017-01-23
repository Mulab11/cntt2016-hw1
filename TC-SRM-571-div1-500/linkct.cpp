#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
const int MAXN = 55;

class MagicMolecule{
public:
	int u[MAXN * MAXN], v[MAXN * MAXN], n, mx, m;
	vector <int> val;
	int dfs(int dep, LL st, int rm, int sum){
		if(rm > mx) return -1;
		if(dep > m) return sum;
		if(bool(st & (1LL << u[dep])) && bool(st & (1LL << v[dep])))
			return max(dfs(dep + 1, st ^ (1LL << u[dep]), rm + 1, sum - val[u[dep]]), dfs(dep + 1, st ^ (1LL << v[dep]), rm + 1, sum - val[v[dep]]));
		return dfs(dep + 1, st, rm, sum);
	}
	int maxMagicPower(vector <int> val_, vector <string> g){
		int i, j, sum = 0; val = val_;
		n = val.size(), mx = n - (2 * n - 1) / 3 - 1;
		for(i = m = 0; i < n; ++ i){
			sum += val[i];
			for(j = i + 1; j < n; ++ j)
				if(g[i][j] == 'N'){
					u[++ m] = i;
					v[m] = j;
				}
		} return dfs(1, (1LL << n) - 1, 0, sum);
	}
};
