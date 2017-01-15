#line 2 "KingdomAndDice.cpp"  
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

const int N = 50;

class KingdomAndDice {  
public:
	double newFairness(vector <int> d1, vector <int> d2, int X) {
		std::sort(d1.begin(), d1.end());
		std::sort(d2.begin(), d2.end());
		
		int n = SZ(d1), s = 0, c = 0;
		// s -> current number of 1 win 2
		// c -> number of zeros
		for(int i = 0; i < n; ++i)
			if(d1[i]) {
				for(int j = 0; j < n; ++j)
					if(d2[j] < d1[i]) s++;
			}
			else c++;
		
		std::vector<int> num;
		// num -> used number -> key point on axis to split interval into segments
		for(int i = 0; i < n; ++i) if(d1[i]) num.pb(d1[i]);
		for(int i = 0; i < n; ++i) num.pb(d2[i]);
		num.pb(0), num.pb(X + 1);
		std::sort(num.begin(), num.end());
		
		std::vector<pii> p;
		// p.fi -> contribution, p.se -> numbers
		for(int i = 1; i < SZ(num); ++i) {
			int l = num[i - 1] + 1, r = num[i] - 1;
			if(l <= r) p.pb(mp(std::lower_bound(d2.begin(), d2.end(), l) - d2.begin(), r - l + 1));
		}
		
		std::bitset<N * N + 9> f[N + 9];
		// f[i][j] -> whether using i items can get to sum j
		f[0][0] = 1;
		for(int i = 0; i < SZ(p); ++i) {
			if(!p[i].fi) continue;
			int lim = std::min(p[i].se, n * n / p[i].fi);// bound the upper limit
			while(lim--) {
				for(int j = c; j >= 1; --j)
					f[j] |= f[j - 1] << p[i].fi;
			}
		}

		// calculate the answer
		int ans = 1e9;
		for(int i = 0; i <= n * n; ++i) {
			bool flag = false;
			for(int j = 0; j <= c; ++j)
				if(f[j][i]) {
					flag = true;
					break;
				}
			if(flag) {
				int cur = (i + s) * 2 - n * n;
				if(abs(cur) < abs(ans)) ans = cur;// if same, pick smaller answer
			}
		}
		return (double)(n * n + ans) / (2 * n * n);
	}  
};  
