#include <bits/stdc++.h>

using namespace std;

int n ; 

vector<int> a ; 

const int MAXN = 60 ;

bool vis[MAXN] ; 

int ans = 0 ;

int edge[MAXN * MAXN][2], cnt = 0 ; 

class MagicMolecule {
		public:

				void dfs(int now,int lst) {
						if (now > cnt) {
								int cur = 0;
								for(int i = 0;i < n;i ++)
										if (vis[i]) cur += a[i];
								ans = max(ans,cur);
								return;
						}
						if (!vis[edge[now][0]] || !vis[edge[now][1]]) {dfs(now + 1,lst);return;} 
						if (!lst) return;
						for(int i = 0;i < 2;i ++) if (vis[edge[now][i]]) {
								vis[edge[now][i]] = 0;
								dfs(now + 1,lst - 1);
								vis[edge[now][i]] = 1;
						}
				}

				int maxMagicPower(vector<int> magicPower,vector<string> magicBond) {
						memset(vis,1,sizeof vis);
						n = magicPower.size();
						a = magicPower;
						ans = -1;
						for(int i = 0;i < n;i ++)
								for(int j = i + 1;j < n;j ++)
										if (magicBond[i][j] == 'N') edge[++ cnt][0] = i,edge[cnt][1] = j;
						int m = n * 2 / 3;
						for(m = 1;3 * m < 2 * n;m ++);
						dfs(1,n - m);
						return ans;
				}
};
