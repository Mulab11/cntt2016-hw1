#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 60,mod = 1e9+7;

class KingdomAndCities{
    public:
    	int f[N][N];
		int fact[N*N],inv[N*N],finv[N*N];
    	int howMany(int n, int m, int k){
     		if (k < n-1) return 0;
    		if (n == m) return 0;   		
    		init();
			f[1][0] = 1;
			
    		for (int i = 2;i <= n;i++)
    			for (int j = 1;j <= min(k,i*(i-1)/2);j++){
    				f[i][j] = C(i*(i-1)/2,j);
					for (int l = 1;l < i;l++)
						for (int r = 0;r <= min(j,l*(l-1)/2);r++)
							f[i][j] = add(f[i][j],mod-(ll)f[l][r]*C(i-1,l-1)%mod*C((i-l)*(i-l-1)/2,j-r)%mod);
    			}
			if (m == 0) return f[n][k];
			if (m == 1){
				int ans = 0;
				ans = (ll)f[n-1][k-2]*C(n-1,2)%mod;
			//	cout << ans << endl;
				for (int i = 1;i < n-1;i++)
					for (int j = 0;j <= k-2;j++)
					ans = add(ans,(ll)f[i][j]*f[n-i-1][k-j-2]%mod*i*(n-i-1)%mod*C(n-1,i)%mod*inv[2]%mod);//左x右y<=>左y右x 
				return ans;
			}
			if (m == 2){
				int ans = 0;
				if (k-3 >= 0){
					ans = (ll)f[n-2][k-3]*(n-2)*(n-2)%mod;//两个点可以重复 
					for (int i = 1;i < n-2;i++)
						for (int j = 0;j <= k-3;j++)
						ans = add(ans,(ll)f[i][j]*f[n-i-2][k-j-3]%mod*i*(n-i-2)%mod*C(n-2,i)%mod);
				}
		//		return ans;
				if (k-4 >= 0){
					ans = add(ans,(ll)f[n-2][k-4]*C(n-2,2)%mod*C(n-2,2)%mod); 
					for (int i = 1;i < n-2;i++)
						for (int j = 0;j <= k-4;j++){
							int u = (ll)f[i][j]*f[n-2-i][k-4-j]%mod*C(n-3,i-1)%mod;
							int v = 0;
							v = add(v,(ll)i*(n-i-2)%mod*C(i,2)%mod);
							v = add(v,(ll)i*(n-i-2)%mod*C(n-i-2,2)%mod);
							v = add(v,v);
							v = add(v,(ll)i*(n-i-2)%mod*i*(n-i-2)%mod);
							ans = add(ans,(ll)u*v%mod);
						}
					for (int i = 1;i < n-2;i++)
						for (int j = 1;i+j < n-2;j++)
							for (int l = 0;l <= k-4;l++)
								for (int r = 0;l+r <= k-4;r++){
									int u = (ll)f[i][l]*f[j][r]%mod*f[n-2-i-j][k-4-l-r]%mod;
									u = (ll)u*C(n-2,i)%mod*C(n-2-i,j)%mod;
									u = (ll)u*i%mod*j%mod*j%mod*(n-2-i-j)%mod;
									ans = add(ans,u);
		
								}
				}
				return ans;
			}
			return -1;
	   	}
    	void init(){
 			fact[0] = 1;
 			for(int i = 1;i <= 2500;i++) 
 				fact[i] = (ll)fact[i-1]*i%mod;
 			inv[1] = 1;
			for(int i = 2;i <= 2500;i++) 
 				inv[i] = mod-(ll)mod/i*inv[mod%i]%mod;
 			finv[0] = 1;
 			for(int i = 1;i <= 2500;i++) 
 				finv[i] = (ll)finv[i-1]*inv[i]%mod; 			
    	}
    	int C(int x,int y){
    		if (x < y) return 0;
    		return (ll)fact[x]*finv[y]%mod*finv[x-y]%mod;
		}
		int add(int x,int y){
			x += y;
			while (x >= mod) x -= mod;
			return x;
		}
};