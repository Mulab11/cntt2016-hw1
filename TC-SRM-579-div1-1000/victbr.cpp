#include <bits/stdc++.h>

using namespace std;

const int N = 80;

class RockPaperScissors{
	public:
		double ans,A[N][3],C[N][N],f[N][N][N][3],g[N][N][N];
		int n;
		double bestScore(vector<int> a,vector<int> c,vector<int> b) {
			n = a.size();
			for (int i = 0;i < n;i++){
				A[i+1][0] = a[i]/300.0;
				A[i+1][1] = c[i]/300.0;
				A[i+1][2] = b[i]/300.0;
			}

			for (int i = 0;i <= n;i++){
				C[i][0] = 1;
				for (int j = 1;j <= n;j++)
					C[i][j] = C[i-1][j]+C[i-1][j-1];
			}
			g[0][0][0] = 1;
	
			for (int t = 1;t <= n;t++)
				for (int i = t-1;i >= 0;i--)
					for (int j = t-i-1;j >= 0;j--)
						for (int k = t-i-j-1;k >= 0;k--){
							g[i+1][j][k] += g[i][j][k]*A[t][0];
							g[i][j+1][k] += g[i][j][k]*A[t][1];
							g[i][j][k+1] += g[i][j][k]*A[t][2];
							f[i][j][k][0] += g[i][j][k]*A[t][0];
							f[i][j][k][1] += g[i][j][k]*A[t][1];
							f[i][j][k][2] += g[i][j][k]*A[t][2];
					
							for (int u = 0;u < 3;u++){
								if (i)f[i][j][k][u] += f[i-1][j][k][u]*A[t][0];
								if (j)f[i][j][k][u] += f[i][j-1][k][u]*A[t][1];
								if (k)f[i][j][k][u] += f[i][j][k-1][u]*A[t][2];
							}
						}	
			for (int i = 0;i < n;i++)
				for (int j = 0;i+j < n;j++)
					for (int k = 0;i+j+k < n;k++)
						ans += max(f[i][j][k][0]*3+f[i][j][k][1],max(f[i][j][k][1]*3+f[i][j][k][2],f[i][j][k][2]*3+f[i][j][k][0]))/(C[n][i+j+k]*(n-i-j-k));	
			return ans;
		}
};
