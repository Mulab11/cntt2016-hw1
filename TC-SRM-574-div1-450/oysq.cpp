#line 2 "PolygonTraversal.cpp"  
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


class PolygonTraversal {  
public:
	ll f[1 << 18][18];
	long long count(int n, vector <int> p) {
		memset(f, 0, sizeof f);
		
		//initial state
		int ini = 0;
		for(int i = 0; i < SZ(p); ++i) ini |= 1 << (--p[i]);
		f[ini][p.back()] = 1;

		//dp
		for(int i = ini; i < (1 << n); ++i) {
			// a -> in, b -> out, p -> prefix sum
			static int a[18], an, b[18], bn, p[18];
			an = bn = 0;
			for(int j = 0; j < n; ++j)
				if(i >> j & 1) a[an++] = j, p[j] = 1 + (j ? p[j - 1] : 0);
				else b[bn++] = j, p[j] = j ? p[j - 1] : 0;
			for(int j = 0; j < an; ++j)
				if(f[i][a[j]])
					for(int k = 0; k < bn; ++k) {
						int x = a[j], y = b[k];
						if(x < y) std::swap(x, y);
						if(p[x - 1] - p[y] && p[x - 1] - p[y] < p[n - 1] - 1)//check if valid
							f[i | (1 << b[k])][b[k]] += f[i][a[j]];
					}
		}

		//calculate the answer
		ll ans = 0;
		for(int i = 0; i < n; ++i)
			if(i != p[0] && i != (p[0] + 1) % n && i != (p[0] - 1 + n) % n)//check if valid
				ans += f[(1 << n) - 1][i];
		return ans;
	}  
};  
