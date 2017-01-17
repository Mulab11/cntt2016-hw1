#include <bits/stdc++.h>

using namespace std;

const int N = 20;

class YetAnotherBoardGame{
	public:
		int n,m,a[N],b[N],f[N][N],ans;
		int minimumMoves(vector <string> board){
			ans = 0x7fffffff;
			n = board.size();
			m = board[0].size();
			for (int i = 0;i < n;i++)
				for (int j = 0;j < m;j++)
					f[i+1][j+1] = (board[i][j] == 'B') ? 1 : 0;
			for (int i = 0;i < (1<<m);i++){
//
				int cnt = 0;
				for (int j = 1;j <= m;j++){
					if ((1<<j>>1)&i) {
						b[j] = 1;cnt++;
						f[1][j  ] ^= 1;
						f[1][j-1] ^= 1;
						f[1][j+1] ^= 1;
						f[2][j  ] ^= 1;
						f[0][j  ] ^= 1;						
					}
				}
				dfs(2,0,cnt);
				for (int j = 1;j <= m;j++){
					if ((1<<j>>1)&i) {
						b[j] = 0;
						f[1][j  ] ^= 1;
						f[1][j-1] ^= 1;
						f[1][j+1] ^= 1;
						f[2][j  ] ^= 1;
						f[0][j  ] ^= 1;						
					}
				}	
//
				cnt = 0;
				for (int j = 1;j <= m;j++){
					if ((1<<j>>1)&i) {
						b[j] = 2;cnt++;
						f[1][j-1] ^= 1;
						f[1][j+1] ^= 1;
						f[2][j  ] ^= 1;
						f[0][j  ] ^= 1;						
					}
				}
				dfs(2,0,cnt);
				for (int j = 1;j <= m;j++){
					if ((1<<j>>1)&i) {
						b[j] = 0;
						f[1][j-1] ^= 1;
						f[1][j+1] ^= 1;
						f[2][j  ] ^= 1;
						f[0][j  ] ^= 1;						
					}
				}			
			}
			if (ans == 0x7fffffff) ans = -1;
			return ans;
		}
		void dfs(int x,int y,int dep){
			if (x > n) {
				for (int i = 1;i <= m;i++)
					if (f[n][i] == 0) return;
				ans = min(ans,dep);
				return;
			}
			/*
				if (dep == 48 && y == m-5 && x == n){
					for (int i = 1;i <= n;i++){
						for (int j = 1;j <= m;j++)
							printf("%d ",f[i][j]);
						printf("\n");
					}
					printf("A\n");
				}		
				*/	
			if (y > m) {dfs(x+1,0,dep);return;}
			if (y == 0){
				a[x] = 1;
				dfs(x,y+1,dep);
				a[x] = 2;
				dfs(x,y+1,dep);
				a[x] = 0;
			}
			else{	
				if (f[x-1][y] == 0){
					if (b[y] > 0 && a[x] != b[y]) return;	
					bool flag = b[y] == 0;
					if (a[x] == 1){
						b[y] = 1;
						f[x ][y ] ^= 1;
						f[x][y-1] ^= 1;
						f[x][y+1] ^= 1;						
						f[x-1][y] ^= 1;
						f[x+1][y] ^= 1;
						dfs(x,y+1,dep+1);
						if (flag) b[y] = 0;
						f[x ][y ] ^= 1;
						f[x][y-1] ^= 1;
						f[x][y+1] ^= 1;						
						f[x-1][y] ^= 1;
						f[x+1][y] ^= 1;
					}
					else{
						b[y] = 2;
						f[x][y-1] ^= 1;
						f[x][y+1] ^= 1;						
						f[x-1][y] ^= 1;
						f[x+1][y] ^= 1;
						dfs(x,y+1,dep+1);
						if (flag) b[y] =0;
						f[x][y-1] ^= 1;
						f[x][y+1] ^= 1;						
						f[x-1][y] ^= 1;
						f[x+1][y] ^= 1;						
					}
				}
				else dfs(x,y+1,dep);
			}
		}
}A;

