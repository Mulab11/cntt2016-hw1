#include <bits/stdc++.h>

using namespace std;
const int N = 60,mod = 1e9+7;

class TwoConvexShapes{
	public:
		bool check[N][N][2],check2[N][N][2];
		int n,m,f[N][N][2],ans;
		int countWays(vector <string> grid){
			memset(check,0,sizeof(check));
			memset(check2,0,sizeof(check2));
			ans = 0;
			n = grid.size();m = grid[0].size();
			for (int i = 1;i <= n;i++)
				check[i][0][0] = check[i][0][1] = 1;
			for (int i = 1;i <= n;i++)
				for (int j = 1;j <= m;j++){
					check[i][j][0] = check[i][j-1][0]&(grid[i-1][j-1]!='B');
					check[i][j][1] = check[i][j-1][1]&(grid[i-1][j-1]!='W');
				}
			for (int i = 1;i <= n;i++)
				check2[i][m+1][0] = check2[i][m+1][1] = 1;
			for (int i = 1;i <= n;i++)
				for (int j = m;j >= 1;j--){
					check2[i][j][0] = check2[i][j+1][0]&(grid[i-1][j-1]!='B');
					check2[i][j][1] = check2[i][j+1][1]&(grid[i-1][j-1]!='W');
				}
				
			memset(f,0,sizeof(f));
			for (int j = 1;j <= m;j++){
				if (check[n][j][0]&&check2[n][j+1][1]) f[n][j][0] = 1;
				if (check[n][j][1]&&check2[n][j+1][0]) f[n][j][1] = 1;
			}
			for (int i = n-1;i >= 1;i--){
				int tot[2];
				tot[0] = 0;
				tot[1] = 0;
				for (int j = m;j >= 0;j--){
					tot[0] = add(tot[0],f[i+1][j][0]);
					tot[1] = add(tot[1],f[i+1][j][1]);					
					if (check[i][j][0]&&check2[i][j+1][1]) f[i][j][0] = tot[0];
					if (check[i][j][1]&&check2[i][j+1][0]) f[i][j][1] = tot[1];
				}	
			}
			for (int i = 0;i <= m;i++)
				ans = add(ans,add(f[1][i][0],f[1][i][1]));
			
			
			memset(f,0,sizeof(f));
			for (int j = 1;j <= m;j++){
				if (check[1][j][0]&&check2[1][j+1][1]) f[1][j][0] = 1;
				if (check[1][j][1]&&check2[1][j+1][0]) f[1][j][1] = 1;
			}
			for (int i = 2;i <= n;i++){
				int tot[2];
				tot[0] = 0;
				tot[1] = 0;
				for (int j = m;j >= 0;j--){
					tot[0] = add(tot[0],f[i-1][j][0]);
					tot[1] = add(tot[1],f[i-1][j][1]);					
					if (check[i][j][0]&&check2[i][j+1][1]) f[i][j][0] = tot[0];
					if (check[i][j][1]&&check2[i][j+1][0]) f[i][j][1] = tot[1];
				}	
			}
			for (int i = 0;i <= m;i++)
				ans = add(ans,add(f[n][i][0],f[n][i][1]));
			
			
			for (int i = 1;i <= m;i++){
				bool flag[2];flag[0] = 1;flag[1] = 1;
				for (int j = 1;j <= n;j++){
					flag[0] &= check[j][i][0]&check2[j][i+1][1];
					flag[1] &= check[j][i][1]&check2[j][i+1][0];
				}
				if (flag[0]) ans = add(ans,mod-1);
				if (flag[1]) ans = add(ans,mod-1);
			}
			

			for (int i = 1;i < n;i++){
				bool flag[2];flag[0] = 1;flag[1] = 1;
				for (int j = 1;j <= i;j++){
					flag[0] &= check[j][m][0];
					flag[1] &= check[j][m][1];
				}
				for (int j = i+1;j <= n;j++){
					flag[0] &= check[j][m][1];
					flag[1] &= check[j][m][0];
				}
				if (flag[0]) ans = add(ans,mod-1);
				if (flag[1]) ans = add(ans,mod-1);					
			}
			return ans;
		}	
		int add(int x,int y){
			x += y;
			while (x >= mod) x -= mod;
			return x;
		}
};
