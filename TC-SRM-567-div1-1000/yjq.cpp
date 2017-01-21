#include <bits/stdc++.h>

#define MOD 1000000009

using namespace std;

int n, w; 

const int MAXN = 60;

bool vis[MAXN][MAXN];

map<vector<int>, int> tmp[MAXN];

int hi[MAXN] ;


int Dfs(int cur,vector<int> h) {
		if (cur < 0) return 1;
		if (tmp[cur].find(h) != tmp[cur].end()) return (tmp[cur].find(h)) -> second;
		int wtf = 0;
		for(int i = 0; i < w; i ++) {
				bool flag = 1;
				for(int j = 0; j < w; j ++) {
						int cur = hi[cur] - abs(i - j);
						flag &= ((h[j] < cur && cur >= 0) == vis[cur][j]) ; 
				}
				if (flag) {
						vector<int> t2 = h;
						for(int j = 0; j < w; j ++) t2[j] = max(t2[j], hi[cur] - abs(i - j));
						(wtf += Dfs(cur - 1, t2)) %= MOD ; 
				}
		}
		tmp[cur][h] = wtf ; 
		return wtf ; 
}

class Mountains {
		public:
				int countPlacements(vector<int> H, vector<string> mp) {
						n = mp.size();
						w = mp[0].length();

						for(int i = 0;i < n;i ++) for(int j = 0;j < w;j ++) vis[i][j] = (mp[i][j] == 'X') ;
						for(int i = 0;i < n;i ++) hi[i] = H[i] - 1;

						vector<int> res;
						res.clear();
						res.resize(w, -1); 
						return Dfs(n - 1, res);
				}
};
