#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>

using namespace std;
typedef long long ll;
const int maxn = 1e5+1e2;
const int modu = 1e9+7;

class WolfPack {
	public:
		
	ll c[maxn];
	
	ll powerMod(ll a , int n)
	{
		ll res = 1;
		while(n)
		{
			if(n & 1) (res *= a) %= modu;
			a = (a * a) % modu;
			n >>= 1; 
		}
		return res;
	}
	
	ll inv(int a) {  return powerMod(a, modu-2); }
	
	ll getRes(vector<int> a, int m)
	{
		ll ans = 0;
		for(int i=a[0] - m; i<=a[0] + m ; i+=2)
		{
			ll res = 1;
			for(int j=0;j<a.size();j++)
				if(abs(a[j] - i) <= m && abs(a[j] - i - m)%2 == 0)
					(res *= c[(m - abs(a[j] - i))/2]) %= modu;
				else 
				{
					res = 0;
					break;
				}
			(ans += res) %= modu;
		}
		return (ans + modu)%modu;
	}
	
	
	int calc(vector<int> x, vector<int> y, int m) {
		
		c[0] = 1;
		for(int i=1;i<=m;i++) c[i] = (((c[i-1] * (m - i + 1)) % modu) * inv(i)) % modu;
		
		vector<int> z = x , d = x;
		for(int i=0;i<z.size();i++) z[i] = x[i] + y[i] , d[i] = x[i] - y[i];
		return (getRes(z, m) * getRes(d, m)) % modu;
	}
};
