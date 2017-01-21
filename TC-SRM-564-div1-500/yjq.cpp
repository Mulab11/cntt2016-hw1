#include <bits/stdc++.h>

using namespace std;

typedef long long LL ; 

class AlternateColors2 {
		private:
				LL Calc(int s, int t, int d) { 
						if (s > t) return 0 ; 
						return 1LL * (s + t) * ((t - s) / d + 1) / 2 ; 
				}
		public:
				LL countWays(int n, int k) {
						LL ans = 0;
						if(k % 3 == 1) ans += (LL)(n - k + 1) * (n - k + 2) / 2 ;
						ans += (k / 3 + (k % 3 != 1)) / 2 * (n - k + 1) * 2 ;
						ans += Calc(k / 3, (k - 2) / 2, 1) ;
						ans += Calc(0, (k - 3) / 2, 1) ;
						ans -= Calc(k % 2, k - 2 - k / 3 * 2, 2) ;
						ans += k - k / 3 - 1 ;
						return ans;
				}
};
