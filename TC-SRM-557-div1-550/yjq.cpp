#include <bits/stdc++.h>

using namespace std;

int n ; 

const int MAXN = 60 ;

bool mp[MAXN][MAXN], vis[MAXN] ;

int fr[MAXN] ; 


int Hungary(int x) {
		for(int i = 0;i < n;i ++)
				if (!vis[i] && mp[x][i]) {
						vis[i] = 1;
						if (!fr[i] || Hungary(fr[i] - 1)) {
								fr[i] = x + 1;
								return 1;
						}
				}
		return 0;
}
class Incubator {
		public:

				int maxMagicalGirls(vector<string> board) {
						n = board.size();
						for(int i = 0;i < n;i ++) for (int j = 0; j < n; j ++) mp[i][j] = (board[i][j] == 'Y') ; 
						for(int k = 0;k < n;k ++) for(int i = 0;i < n;i ++) for(int j = 0;j < n;j ++) mp[i][j] |= mp[i][k] & mp[k][j]; 
						int ans = n;
						for(int i = 0;i < n;i ++, memset(vis, 0, sizeof vis) ) {
								memset(vis,0,sizeof vis);
								ans -= Hungary(i);
						}
						return ans;
				}
};
