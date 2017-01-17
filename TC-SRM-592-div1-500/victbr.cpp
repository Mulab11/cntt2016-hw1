#include <bits/stdc++.h>


using namespace std;
typedef long long ll;
const int mod = 1000000007,N = 60,M = 1900+110;

class LittleElephantAndPermutationDiv1{
	public:
		int ans,f[N][N][M];
		int getNumber(int n, int m){
			f[0][0][0] = 1;
			for (int i = 0;i < n;i++)
				for(int j = 0;j <= i;j++)
					for (int k = 0;k <= 1900;k++)
						if (f[i][j][k]){
							f[i+1][j][k+i+1] = add(f[i+1][j][k+i+1],f[i][j][k]);
							f[i+1][j][k+i+1] = add(f[i+1][j][k+i+1],(ll)f[i][j][k]*j%mod); 
							if (j > 0) f[i+1][j-1][k+i+1+i+1] = add(f[i+1][j-1][k+i+1+i+1],(ll)f[i][j][k]*j%mod*j%mod);//Â©´òÒ»¸öj-1 
							f[i+1][j+1][k] = add(f[i+1][j+1][k],f[i][j][k]);
							f[i+1][j][k+i+1] = add(f[i+1][j][k+i+1],(ll)f[i][j][k]*j%mod);
						}
			for (int i = m;i <= 1900;i++)
				ans = add(ans,f[n][0][i]);
			for (int i = 1;i <= n;i++) ans = (ll)ans*i%mod;
			return ans;
		}
		int add(int x,int y){
			x += y;
			while (x >= mod) x -= mod;
			return x;
		}
};
