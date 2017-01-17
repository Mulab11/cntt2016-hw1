#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod = 1e9+7,N = 40,M = 40,W = 1296;

class LISNumber{
	public:
		int cnt[N],f[N][W],fact[W+10],inv[W+10],finv[W+10];
		int count(vector <int> cardsnum, int K) {
			
			fact[0] = 1;for (int i = 1;i <= W;i++) fact[i] = (ll)fact[i-1]*i%mod;
			inv[1] = 1;for (int i = 2;i <= W;i++) inv[i] = mod-(ll)mod/i*inv[mod%i]%mod;
			finv[0] = 1;for (int i = 1;i <= W;i++) finv[i] = (ll)finv[i-1]*inv[i]%mod;
			for (int i = 0;i < cardsnum.size();i++)
				cnt[i] = cardsnum[i];
			f[0][0] = 1;
			int sum = 0;
			for (int i = 0;i < 36;i++){
				for (int j = 0;j <= K;j++)
					for (int k = 0;k <= min(cnt[i],j);k++){
					int u = i+1,v = cnt[i]-k;
					if (j+v > K) continue;
					f[u][j+v] = add(f[u][j+v],(ll)f[i][j]*C(j,k)%mod*C(sum-j+k+v,v)%mod);
				}
				sum += cnt[i];
			}
			return f[36][K];
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
