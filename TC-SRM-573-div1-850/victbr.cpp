#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int mod = 1e9+7,N = 60,M = 100000;

class WolfPack{
	public:
		int ans1,ans2;
		int n,a[N],b[N];
		int fact[M+10],finv[M+10],inv[M+10];
		int calc(vector <int> x, vector <int> y, int m){
			n = x.size();
			init();
			for (int i = 0;i < n;i++) a[i] = x[i]+y[i],b[i] = x[i]-y[i];//旋转45度 
			for (int i = -300000;i <= 300000;i++){//枚举所有情况 
				int tot = 1;
				for (int j = 0;j < n;j++){
					if ((abs(i+a[j]+m)&1)||abs(i-a[j])<=m){tot = 0;break;}
					else tot = (ll)tot*C(m,abs(i-a[j])+(m-abs(i-a[j]))/2)%mod;
				}
				ans1 = add(ans1,tot);
			}

			for (int i = -300000;i <= 300000;i++){
				int tot = 1;
				for (int j = 0;j < n;j++){
					if ((abs(i+b[j]+m)&1)||abs(i-b[j])<=m){tot = 0;break;}
					else tot = (ll)tot*C(m,abs(i-b[j])+(m-abs(i-b[j]))/2)%mod;
				}
				ans2 = add(ans2,tot);
			}
			
			return (ll)ans1*ans2%mod;
		}
		void init(){
			fact[0] = 1;
			for (int i = 1;i <= M;i++) fact[i] = (ll)fact[i-1]*i%mod;
			inv[1] = 1;
			for (int i = 2;i <= M;i++) inv[i] = mod-(ll)mod/i*inv[mod%i]%mod;
			finv[0] = 1;
			for (int i = 1;i <= M;i++) finv[i] = (ll)finv[i-1]*inv[i]%mod;
		}
		int add(int x,int y){
			x += y;
			while (x >= mod) x -= mod;
			return x;
		}
		int C(int x,int y){
			if (x < y) return 0;
			return (ll)fact[x]*finv[y]%mod*finv[x-y]%mod;
		}
};
