#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
const int MAXN = 55;
const LL INF = 0x3f3f3f3f3f3f3f3fLL;

class SkiResorts{
public:
	LL d[MAXN][MAXN]; int n, N; bool vis[MAXN][MAXN];
	LL minCost(vector <string> g, vector <int> ht){
		int i, j, k, mp1, mp2; LL mn;
		n = g.size(), N = n * n;
		memset(d, 0x3f, sizeof(d));
		memset(vis, false, sizeof(vis));
		for(i = 0; i < n; ++ i)
			d[0][i] = abs(ht[0] - ht[i]);
		for(i = 1; i <= N; ++ i){
			for(j = 0, mn = INF; j < n; ++ j)
				for(k = 0; k < n; ++ k)
					if(!vis[j][k] && d[j][k] < mn)
						mn = d[j][k], mp1 = j, mp2 = k;
			if(mn == INF) break;
			vis[mp1][mp2] = true;
			for(j = 0; j < n; ++ j){
				if(g[mp1][j] != 'Y') continue;
				for(k = 0; k < n; ++ k)
					if(ht[k] <= ht[mp2] && d[j][k] > mn + abs(ht[j] - ht[k]))
						d[j][k] = mn + abs(ht[j] - ht[k]);
			}
		}
		for(i = 0, mn = INF; i < n; ++ i)
			if(d[n - 1][i] < mn)
				mn = d[n - 1][i];
		return mn == INF ? -1 : mn;
	}
};
