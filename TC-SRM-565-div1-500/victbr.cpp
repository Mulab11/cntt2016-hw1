#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 33000;

class TheDivisionGame{
	public:
		bool bo[N];
		ll ans;
		int len,prime[N],a[1001000],n,b[110],c[1001000];
		long long countWinningIntervals(int L, int R){
			make_prime(32000);n = R-L+1;
			for (int i = L;i <= R;i++)
				c[i-L+1] = i;
			for (int i = 1;i <= len;i++){
				int u = L/prime[i]*prime[i];
				if (u < L) u += prime[i];
				for (int j = u;j <= R;j+=prime[i]){
					while (c[j-L+1] % prime[i] == 0){
						c[j-L+1] /= prime[i];
						a[j-L+1]++;
					}
				}
			}
			for (int i = 1;i <= n;i++)
				if (c[i] > 1) a[i]++;
			for (int i = 1;i <= n;i++)
				a[i] ^= a[i-1];
			for (int i = 0;i <= n;i++)
				b[a[i]]++;
			ans = (ll)n*(n+1)/2;
			for (int i = 0;i <= 99;i++)
				ans -= (ll)b[i]*(b[i]-1)/2;
			return ans;
		}
		void make_prime(int p){
			len = 0;
			c[1] = 0;
			for (int i = 2;i <= p;i++){
				if (bo[i] == 0) {prime[++len] = i;c[i] = 1;}
				for (int j = 1;j <= len && i*prime[j] <= p;j++){
					bo[i*prime[j]] = 1;
					c[i*prime[j]] = c[i]+1;
					if (i%prime[j] == 0) break;
				}
			}
		}
};
