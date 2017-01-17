#include <bits/stdc++.h>

using namespace std;

typedef long long ll; 

class PyramidSequences{
	public:
		int g;
		ll ans;
		long long distinctPairs(int n, int m){
			n--;m--;
			g = gcd(n,m);
			ans = (ll)n/g*m/g*(g-1);
			ans += ((ll)n/g+1)*(m/g+1)/2;
			return ans;
		}
		int gcd(int x,int y){
			int z = x%y;
			while (z){
				x = y;y = z;z = x % y;
			}
			return y;
		}
};   
