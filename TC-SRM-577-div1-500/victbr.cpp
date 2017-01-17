#include <bits/stdc++.h>

using namespace std;

const int N = 17,inf = 1000;

class EllysChessboard{
	public:
		int u[N*N],v[N*N],len;
		int n,m,a[N][N],f[N][N][N][N];
		int minCost(vector <string> board){
			n = board.size();
			m = board[0].size();
			for (int i = 0;i < n;i++)
				for (int j = 0;j < m;j++)
					if (board[i][j] == '#'){
						a[i+j][i-j+m] = 1;
						u[++len] = i+j;
						v[  len] = i-j+m;
					}
			for (int i = 0;i <= 16;i++)
				for (int j = 0;j <= 16;j++)
					for (int k = 0;k <= 16;k++)
						for (int l = 0;l <= 16;l++)
							if (i != j || k != l)
							f[i][j][k][l] = inf;
		//	for (int i = 1;i <= len;i++) printf("%d %d\n",u[i],v[i]);				
			for (int i = 0;i <= n+m-2;i++)
				for (int x = 0;i+x <= n+m-2;x++)
					for (int j = 0;j < n+m;j++)
						for (int y = 0;j+y < n+m;y++)
							if (f[x][i+x][y][j+y] <= 1000){
							for (int k = 1;k <= len;k++)
								if (x > u[k] || u[k] > i+x || y > v[k] || v[k] > j+y){
									int i2 = min(x,u[k]),x2 = max(i+x,u[k]);
									int j2 = min(y,v[k]),y2 = max(j+y,v[k]);
									int ans = 0;
								//	if (k == 2 && x == 5 && y == 7 && i == 0 && j == 0) printf("%d %d %d %d\n",i2,x2,j2,y2);
								//	if(i2 == 4 && x2 == 5 && j2 == 7 && y2 == 10) printf("%d %d %d %d %d %d\n",x,x+i,y,j+y,u[1],v[1]);	
									for (int l = 1;l <= len;l++)
										if ((x > u[l] || u[l] > i+x || y > v[l] || v[l] > j+y) && (i2 <= u[l] && u[l] <= x2 && j2 <= v[l] && v[l] <= y2)){
										
											ans += max(abs(v[l]-j-y),max(abs(v[l]-y),max(abs(u[l]-x),abs(u[l]-i-x))));
										}	
							//		if(i2 == 3 && x2 == 4 && j2 == 2 && y2 == 4) cout << ans << endl;
									f[i2][x2][j2][y2] = min(f[x][i+x][y][j+y]+ans,f[i2][x2][j2][y2]);
								}
							}
			int i = u[1],x = u[1],j = v[1],y = v[1];
		//	printf("%d %d %d\n",u[1],v[1],len);
			//printf("%d\n",f[4][5][7][10]);
			for (int k = 1;k <= len;k++){
				i = min(i,u[k]);x = max(x,u[k]);
				j = min(j,v[k]);y = max(y,v[k]);
			}
			//printf("%d %d %d %d\n",i,x,j,y);
			return f[i][x][j][y];
		}
};
