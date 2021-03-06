#line 2 "HolyNumbers.cpp"  
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

const int N = 1e6;

int p[N + 9], pn;
bool notp[N + 9];

// get prime numbers
void euler(int n) {
	pn = 0, notp[1] = true;
	for(int i = 2; i <= n; ++i) {
		if(!notp[i]) p[++pn] = i;
		for(int j = 1; j <= pn && i * p[j] <= n; ++j) {
			notp[i * p[j]] = true;
			if(i % p[j] == 0) break;
		}
	}
}

// calc ans from recursion
ll calc(ll n, int m) {
	// exit condition
	if(m > pn || n < p[m]) return 1;
	// optimizing
	if((ll)p[m] * p[m] > n) return std::upper_bound(p + 1, p + pn + 1, n) - p - m + 1;
	// enumberate p ^ k
	ll ret = calc(n, m + 1);
	n /= p[m];
	while(n) ret += calc(n, m + 1), n /= (ll)p[m] * p[m];
	return ret;
}

class HolyNumbers {  
public:  
	long long count(long long upTo, int maximalPrime) {  
		euler(maximalPrime);
		return calc(upTo, 1);
	}    
};  
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           