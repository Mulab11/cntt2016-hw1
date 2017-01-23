#include <bits/stdc++.h>

using namespace std;

int n, m, ax, ay, bx, by ; 

const int MAXN = 60 ; 

bool mp[MAXN][MAXN], vis[MAXN][MAXN];

int  da[MAXN][MAXN], db[MAXN][MAXN], dep[MAXN][MAXN];

int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};

void DfsA(int x, int y) {
		vis[x][y] = 1;
		for(int i = 0; i < 4; i++) {
				int tx = x + dx[i], ty = y + dy[i];
				if(mp[tx][ty] && !vis[tx][ty])
						da[tx][ty] = da[x][y] + 1, DfsA(tx, ty);
		}
}
void DfsB(int x, int y) {
		vis[x][y] = 1;
		for(int i = 0; i < 4; i++) {
				int tx = x + dx[i], ty = y + dy[i];
				if(mp[tx][ty] && !vis[tx][ty])
						db[tx][ty] = db[x][y] + 1, DfsB(tx, ty);
		}
}
int Dfs(int x, int y, bool root = 0)
{
		vis[x][y] = 1;
		dep[x][y] = 1;
		int ret = 0;
		for(int i = 0; i < 4; i++)
		{
				int tx = x + dx[i], ty = y + dy[i];
				if(mp[tx][ty] && !vis[tx][ty])
				{
						Dfs(tx, ty);
						dep[x][y] = max(dep[x][y], dep[tx][ty] + 1);
						if(root && dep[tx][ty] >= 3)
								ret++;
				}
		}
		return ret;
}
class GameInDarknessDiv1 {
		public:
				string check(vector<string> a) {
						n = a.size(), m = a[0].size();
						for(int i = 0; i < n; i++) {
								for(int j = 0; j < m; j++) {
										mp[i + 1][j + 1] = a[i][j] != '#';
										if(a[i][j] == 'A') ax = i + 1, ay = j + 1;
										else 
												if(a[i][j] == 'B')
														bx = i + 1, by = j + 1;
								}
						}
						memset(vis, 0, sizeof(vis)); 
						DfsA(ax, ay);
						memset(vis, 0, sizeof(vis));
						DfsB(bx, by);
						for(int i = 0; i < n; i++) {
								for(int j = 0; j < m; j++) {
										if(da[i][j] - db[i][j] > 1) {
												memset(vis, 0, sizeof(vis));
												if(Dfs(i, j, 1) >= 3) return "Bob wins";
										}
								}
						}
						return "Alice wins";
				}
} sol ;

string tmp[] = {"A.B..",
 "##.##",
 "##.##"} ; 
vector<string> gx ; 
int main() {
		for (int i = 0; i <3 ; i ++) gx.push_back(tmp[i]) ; 
		cout << sol.check(gx) << endl ; 
}

