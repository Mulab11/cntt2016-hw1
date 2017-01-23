#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;

class PenguinSledding{
public:
	int d[55]; bool g[55][55];
	LL countDesigns(int n, vector <int> u, vector <int> v){
		int m = u.size(), i, j, k; LL ans = 0LL;
		memset(d, 0, sizeof(d));
		memset(g, false, sizeof(g));
		for(i = 0; i < m; ++ i){
			++ d[u[i]], ++ d[v[i]];
			g[u[i]][v[i]] = g[v[i]][u[i]] = true;
		}
		for(i = 1; i <= n; ++ i)
			ans += (1LL << d[i]) - 1;
		for(i = 1; i <= n; ++ i)
			for(j = i + 1; j <= n; ++ j)
				for(k = j + 1; k <= n; ++ k)
					if(g[i][j] && g[j][k] && g[i][k])
						++ ans;
		return ans - m + 1;
	}
};
