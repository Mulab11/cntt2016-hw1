#include <bits/stdc++.h>

using namespace std;

int n, m ; 

const int MAXN = 60 ; 

int cnt[MAXN][26];
bool vis[MAXN] ;


bool check(int x) {
		memset(vis, 0, sizeof vis) ; 
		for(int t = 0; t < 26; t ++) {
				for(int i = 0; i < 26; i ++) {
						bool flag = 1;
						for(int j = 0; j < n && flag; j++) flag &= (vis[j] || cnt[j][i] <= cnt[x][i]) ; 
						if(flag) for(int j = 0; j < n; j ++) if (!vis[j] && cnt[j][i] < cnt[x][i]) vis[j] = 1;
				}
		}
		for(int i = 0; i < n; i ++) {
				if (!vis[i]) return 0 ; 
		}
		return 1; 
}
class StringGame {
		public:;
			   vector<int> getWinningStrings(vector<string> ss) {
					   n = ss.size(), m = ss[0].length();
					   for(int i = 0; i < n; i ++) {
							   for(int j = 0; j < m; j++) cnt[i][ss[i][j] - 'a'] ++;
					   }
					   vector<int> ans;
					   for(int i = 0; i < n; i++) if (check(i)) ans.push_back(i) ; 
					   return ans;
			   }
};
