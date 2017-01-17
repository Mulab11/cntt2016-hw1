#include <bits/stdc++.h>

using namespace std;

const int N = 30,K = 1500+10;

class RandomPaintingOnABoard{
	public:
		int a[N][N],f[N][K][2];
		int n,m,res[N],sum[N],S;
		double ans;
		double expectedSteps(vector<string> prob){
			n = prob.size();m = prob[0].size();
			if (n <= m){
				for (int i = 0;i < m;i++)
					for (int j = 0;j < n;j++)
						a[i+1][j+1] = prob[j][i]-'0';
				swap(n,m);		
			}
			else{
				for (int i = 0;i < n;i++)
					for (int j = 0;j < m;j++)
						a[i+1][j+1] = prob[i][j]-'0';
			}
			
			for (int i = 1;i <= n;i++)
				for (int j = 1;j <= m;j++){
					S += a[i][j];
					sum[j] += a[i][j];
					res[i] += a[i][j];
				}
					
			for (int i = 0;i < (1<<m);i++){
				int tot = 0,u = 0;
				for (int j = 1;j <= m;j++)
					if ((1<<j>>1)&i){
						u ^= 1;
						tot += sum[j];
						for (int k = 1;k <= n;k++)
							res[k] -= a[k][j];
					}
				memset(f,0,sizeof(f));
				f[0][0][u] = 1;
				for (int j = 1;j <= n;j++)
					for (int k = 0;k <= S;k++)
						for (int l = 0;l < 2;l++){
							f[j][k][l] = f[j-1][k][l];
							if (k >= res[j]) f[j][k][l] += f[j-1][k-res[j]][l^1]; 
						}
				
				for (int j = 0;j <= S;j++){
					if (j == 0) ans -= f[n][j][0]; 
					else if (j == S) ;
					else ans -= 1.0*f[n][j][0]/(1.0-(double)j/S);
					
					if (j == 0) ans += f[n][j][1]; 
					else if (j == S) ;
					else ans += 1.0*f[n][j][1]/(1.0-(double)j/S);					
				}
				for (int j = 1;j <= m;j++)
					if ((1<<j>>1)&i){
						for (int k = 1;k <= n;k++)
							res[k] += a[k][j];
					}
			}
			return fabs(ans);
			/*
				似乎是求容斥系数时正负写错了。不过由于奇数项偶数项系数正负性不同，
				所以最后求出来的绝对值一定与原答案相同。取绝对值即可。 
			*/
		}
};
