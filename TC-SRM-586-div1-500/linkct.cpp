#include <bits/stdc++.h>
using namespace std;
const int MAXN = 35;

class History{
public:
	int g[MAXN][MAXN], n, m; vector <int> dyn[MAXN];
	string verifyClaims(vector <string> dynasties, vector <string> battles, vector <string> query){
		int i, j, k, u, v, tmp; string battle, ans;
		n = dynasties.size();
		for(i = 0; i < n; ++ i){
			stringstream readin(dynasties[i]);
			while(readin >> tmp)
				dyn[i].push_back(tmp);
		}
		for(i = 0; i < int(battles.size()); ++ i)
			battle += battles[i];
		memset(g, 0x3f, sizeof(g));
		for(i = 0, m = battle.length() / 6 + 1; i < m; ++ i){
			u = battle[i * 6] - 'A', v = battle[i * 6 + 3] - 'A';
			g[u][v] = min(g[u][v], dyn[u][battle[i * 6 + 1] - '0' + 1] - 1 - dyn[v][battle[i * 6 + 4] - '0']);
			g[v][u] = min(g[v][u], dyn[v][battle[i * 6 + 4] - '0' + 1] - 1 - dyn[u][battle[i * 6 + 1] - '0']);
		}
		for(i = 0; i < n; ++ i) g[i][i] = 0;
		for(k = 0; k < n; ++ k)
			for(i = 0; i < n; ++ i)
				for(j = 0; j < n; ++ j)
					if(g[i][j] > g[i][k] + g[k][j])
						g[i][j] = g[i][k] + g[k][j];
		for(i = 0; i < int(query.size()); ++ i){
			u = query[i][0] - 'A', v = query[i][3] - 'A';
			if(g[v][u] + dyn[u][query[i][1] - '0' + 1] - 1 - dyn[v][query[i][4] - '0'] < 0)
				ans += 'N';
			else if(g[u][v] + dyn[v][query[i][4] - '0' + 1] - 1 - dyn[u][query[i][1] - '0'] < 0)
				ans += 'N';
			else ans += 'Y';
		} return ans;
	}
};
