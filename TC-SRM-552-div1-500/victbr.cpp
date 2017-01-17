#include <bits/stdc++.h>

using namespace std;

const int N = 50;

class FoxAndFlowerShopDivOne{
	public:
		int a[N][N],b[N][N],n,m,f[N][N*N],g[N][N*N],ans;
		int theMaxFlowers(vector <string> flowers, int maxDiff){
			n = flowers.size();m = flowers[0].size();ans = -1;
			memset(f,0xaf,sizeof(f));
			memset(g,0xaf,sizeof(g));
			for (int i = 1;i <= n;i++){
				for (int j = 0;j <= 1800;j++)
					f[i][j] = f[i-1][j];
				memset(a,0,sizeof(a));
				memset(b,0,sizeof(b));
				
				for (int j = 1;j <= m;j++){
					for (int k = i;k >= 1;k--){
						a[k][j] = a[k+1][j]+a[k][j-1]-a[k+1][j-1] + val1(flowers[k-1][j-1]);
						b[k][j] = b[k+1][j]+b[k][j-1]-b[k+1][j-1] + val2(flowers[k-1][j-1]);
					}
				}
				
				for (int j = 0;j <= m;j++)
					for (int k = j+1;k <= m;k++)
						for (int l = 1;l <= i;l++){
							int u = a[l][k]-a[l][j],v = b[l][k]-b[l][j];
						//	if (u > 900) return 5;
							f[i][900+u] = max(f[i][900+u],v);
						}
	//			return 0;
			}
	//	return g[m][1];
			for (int i = n;i >= 1;i--){
				for (int j = 0;j <= 1800;j++)
					g[i][j] = g[i+1][j];
				memset(a,0,sizeof(a));
				memset(b,0,sizeof(b));
				for (int j = 1;j <= m;j++){
					for (int k = i;k <= n;k++){
						a[k][j] = a[k-1][j]+a[k][j-1]-a[k-1][j-1] + val1(flowers[k-1][j-1]);
						b[k][j] = b[k-1][j]+b[k][j-1]-b[k-1][j-1] + val2(flowers[k-1][j-1]);
					}
				}
				for (int j = 0;j <= m;j++)
					for (int k = j+1;k <= m;k++)
						for (int l = i;l <= n;l++){
							int u = a[l][k]-a[l][j],v = b[l][k]-b[l][j];
						//	if (u > 0) return 0;
							g[i][900+u] = max(g[i][900+u],v);
						}
			}
			for (int i = 1;i < n;i++)
				for (int j = 0;j <= 1800;j++)
					if (f[i][j] >= 0){
					//	return j;
						for (int k = max(1800-j-maxDiff,0);k <= min(1800-j+maxDiff,1800);k++)
							ans = max(ans,f[i][j]+g[i+1][k]); 	
					}	
		//	return ans;
			
			swap(n,m);
			memset(f,0xaf,sizeof(f));
			memset(g,0xaf,sizeof(g));
			for (int i = 1;i <= n;i++){
				for (int j = 0;j <= 1800;j++)
					f[i][j] = f[i-1][j];
				memset(a,0,sizeof(a));
				memset(b,0,sizeof(b));
				
				for (int j = 1;j <= m;j++){
					for (int k = i;k >= 1;k--){
						a[k][j] = a[k+1][j]+a[k][j-1]-a[k+1][j-1] + val1(flowers[j-1][k-1]);
						b[k][j] = b[k+1][j]+b[k][j-1]-b[k+1][j-1] + val2(flowers[j-1][k-1]);
					}
				}
				
				for (int j = 0;j <= m;j++)
					for (int k = j+1;k <= m;k++)
						for (int l = 1;l <= i;l++){
							int u = a[l][k]-a[l][j],v = b[l][k]-b[l][j];
						//	if (u > 900) return 5;
							f[i][900+u] = max(f[i][900+u],v);
						}
	//			return 0;
			}
	//	return g[m][1];
			for (int i = n;i >= 1;i--){
				for (int j = 0;j <= 1800;j++)
					g[i][j] = g[i+1][j];
				memset(a,0,sizeof(a));
				memset(b,0,sizeof(b));
				for (int j = 1;j <= m;j++){
					for (int k = i;k <= n;k++){
						a[k][j] = a[k-1][j]+a[k][j-1]-a[k-1][j-1] + val1(flowers[j-1][k-1]);
						b[k][j] = b[k-1][j]+b[k][j-1]-b[k-1][j-1] + val2(flowers[j-1][k-1]);
					}
				}
				for (int j = 0;j <= m;j++)
					for (int k = j+1;k <= m;k++)
						for (int l = i;l <= n;l++){
							int u = a[l][k]-a[l][j],v = b[l][k]-b[l][j];
						//	if (u > 0) return 0;
							g[i][900+u] = max(g[i][900+u],v);
						}
			}
			for (int i = 1;i < n;i++)
				for (int j = 0;j <= 1800;j++)
					if (f[i][j] >= 0){
					//	return j;
						for (int k = max(1800-j-maxDiff,0);k <= min(1800-j+maxDiff,1800);k++)
							ans = max(ans,f[i][j]+g[i+1][k]); 	
					}										
			return ans;
		}
		int val1(char c){
			if (c == 'P') return 1;
			if (c == 'L') return -1;
			return 0;
		}
		int val2(char c){
			if (c == 'P') return 1;
			if (c == 'L') return 1;
			return 0;
		}
};
