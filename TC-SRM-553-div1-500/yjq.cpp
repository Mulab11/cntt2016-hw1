#include <bits/stdc++.h>

#define MOD 1000000007

using namespace std;

int n, m ;

const int MAXN = 60 ;

int dp[MAXN][MAXN][3][2][2] ; 

int L[MAXN][MAXN], R[MAXN][MAXN] ;

int dfs(int x,int y,int sta,bool b1,bool b2) {
		if (!(b1 || b2)) return 0;
		if (x == n) {
				if (y == m && sta == 2) return 0;
				return b1 + b2;
		}
		int &cur = dp[x][y][sta][b1][b2];
		if (~cur) return cur;
		cur = 0;
		for(int cl = 0;cl <= m;cl ++) {
				if (sta == 1 && cl < y || sta == 0 && cl > y) continue;
				if (y == m && cl == 0) continue;
				int nxta = sta;
				if (cl < y) nxta = 0; else if (cl > y) nxta = 1;
				if (!x) nxta = 2;
				cur = (cur + dfs(x + 1,cl,nxta,b1 && L[x][cl],b2 && R[x][cl])) % MOD;
		}
		return cur;
}

class TwoConvexShapes {
		public:
				int countWays(vector <string> mp) {
						n = mp.size(),m = mp[0].length();
						
						memset(dp, 255, sizeof dp);

						for(int i = 0;i < n;i ++)
								for(int j = 0;j <= m;j ++) {
										L[i][j] = 1;
										for(int k = 0;k < j;k ++) if (mp[i][k] == 'W') L[i][j] = 0; 
										for(int k = j;k < m;k ++) if (mp[i][k] == 'B') L[i][j] = 0;
										R[i][j] = 1;
										for(int k = 0;k < j;k ++) if (mp[i][k] == 'B') R[i][j] = 0;
										for(int k = j;k < m;k ++) if (mp[i][k] == 'W') R[i][j] = 0;
								}
						return dfs(0,0,2,1,1);
				}
} sol ;

vector<string> gx ; 
int main() { 
		gx.push_back("B?") ;
		gx.push_back("??") ; 
		printf("%d\n", sol.countWays(gx)) ; 
}

