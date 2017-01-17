#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
class FoxPaintingBalls{
	public:
		ll r,g,b,u;
		long long theMax(long long R, long long G, long long B, int N){
			//
				if (N == 1) return R+G+B;
			//
			ll ans = 0;u = (ll)N*(N+1)/6;
			r=R;b=B;g=G;
			if (N%3 != 1){
				ans = min(min(R/u,G/u),B/u);
			}
			else{
				ll l = 0,r = min(min(R/u,G/u),B/u);
				ll mid = (l+r+1) >> 1;
				while (l < r){
					if (check(mid)) l = mid;
					else r = mid-1;
					mid = (l+r+1)>>1;
				}
				ans = l;
			}
			return ans;
		}
		bool check(ll p){
			ll sum = r+g+b-p*u*3;
			return sum >= p;
		}
};
