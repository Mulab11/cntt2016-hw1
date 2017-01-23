#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000009;

class Mountains{
public:
	map <string, int> dp[11]; string glo;
	int n, w; vector <int> ht; vector <string> vis;
	inline void update(int &a, int b){if((a += b) >= MOD) a -= MOD;}
	int dfs(int dep){ //Just brutely search...
		if(dep < 0) return 1;
		if(dp[dep].find(glo) != dp[dep].end()) //... with some memorization
			return dp[dep][glo];
		int i, j, val = 0; string tmp = glo;
		for(i = 0; i < w; ++ i){
			for(j = 0; j < w; ++ j){
				if((vis[dep][j] == 'X') == (ht[dep] - abs(i - j) <= glo[j])) break;
				glo[j] = max(int(glo[j]), ht[dep] - abs(i - j));
			} if(j == w) update(val, dfs(dep - 1));
			glo = tmp;
		} return dp[dep][glo] = val;
	}
	int countPlacements(vector <int> ht_, vector <string> vis_){
		ht = ht_, vis = vis_;
		n = ht.size(), w = vis[0].length();
		for(int i = 0; i < w; ++ i) glo += '\0';
		return dfs(n - 1);
	}
};
