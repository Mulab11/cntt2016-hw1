#line 2 "AlternateColors2.cpp"  
#include <bits/stdc++.h> 

using namespace std;  

#define ui unsigned
#define ll long long

#define pii std::pair<int,int>
#define mp std::make_pair
#define fi first
#define se second

#define SZ(x) (int)(x).size()
#define pb push_back

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(x > y) x = y;}


class AlternateColors2 {  
public:  
	long long countWays(int n, int k) {
		ll ans = 0;
		// 当k - 1步时，r, g, b都有剩余
		if((k - 1) % 3 == 0) ans += (ll)(n - k) * (n - k - 1) / 2;
		
		// 当k - 1步时，r和另一种颜色有剩余
		int t = (k - 1) / 3;
		if(k & 1) ans += (ll)(t / 2 + 1) * (n - k) * 2;
		else ans += (ll)(t + 1) / 2 * (n - k) * 2;

		// 当k - 1步，只有r剩余
		ans += (k - 1) / 3 + 1;// g = b
		// g != b
		for(int x = 0; x <= (k - 1) / 3; ++x)
			ans += ((k - 1 - x) / 2 - x) * 2;
		return ans;
	}  	
};  
