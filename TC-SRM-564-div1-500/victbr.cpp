#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
class AlternateColors2{
	public:
		long long ans;
		long long countWays(int n, int k){
			if (k > n) return 0;
			ans = 0;
			if (k%3 == 1) 
				ans += ((ll)n-k)*(n-k-1)/2;
				
			for (int i = 0;i <= k;i++){
				int mx = min(i-1,k-i),mn = max(-1,k-i*2);
				if (mn < mx) ans += mx-mn;
			}
			for (int i = 0;i <= k;i++){
				if (!((k-i)&1)) continue;
				int b = k-i >> 1;
				if (i > b) continue;
				ans += (n-k)*2;
			}
			return ans;
		}
};
