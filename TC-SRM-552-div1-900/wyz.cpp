// BEGIN CUT HERE

// END CUT HERE
#line 5 "HolyNumbers.cpp"

#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int maxn=(1e6)+7;

int pri[maxn],cnt_pri;
bool is_prime[maxn];

void prepare(int n){
	memset(is_prime,1,sizeof(is_prime));
	is_prime[1]=0;
	cnt_pri=0;
	for (int i=2;i<=n;++i){
		if (is_prime[i]) pri[++cnt_pri]=i;
		for (int j=1;i*pri[j]<=n;++j){
			is_prime[i*pri[j]]=0;
			if (i%pri[j]==0) break;
		}
	}
}



class HolyNumbers {
	ll solve(int u,ll n){
		if (n<1) return 0;
		if (u>cnt_pri) return 1;
		if (1LL*pri[u]*pri[u]>n)
			return upper_bound(pri+u,pri+cnt_pri+1,n)-(pri+u)+1;
		ll res=solve(u+1,n);
		for (ll k=pri[u];k<=n;k*=1LL*pri[u]*pri[u])
			res+=solve(u+1,n/k);
		return res;
	}
	public:
	long long count(long long upTo, int maximalPrime){
		prepare(maximalPrime);
		return solve(1,upTo);
	}
};
