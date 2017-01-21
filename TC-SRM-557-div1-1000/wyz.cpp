// BEGIN CUT HERE

// END CUT HERE
#line 5 "XorAndSum.cpp"

#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int maxn=55;

class XorAndSum {
	ll bin[maxn+2];
	int n;
	ll a[maxn+2];
	public:
	long long maxSum(vector<long long> number){
		for (int i=0;i<=maxn;++i) bin[i]=1LL<<i;
		n=number.size();
		ll ret=0;
		for (int i=0;i<n;++i){
			memset(a,0,sizeof(a));
			for (int j=0;j<n;++j)if (i!=j){
				ll tmp=number[j];
				for (int k=maxn;k>=0;--k){
					if ((tmp&bin[k])==0) continue;
					if (!a[k]){a[k]=tmp;break;}
					tmp^=a[k];
				}
			}
			ll tmp=number[i];
			for (int k=maxn;k>=0;--k){
				if ((tmp&bin[k])||!a[k]) continue;
				tmp^=a[k];
			}
			ret+=tmp;
			number[i]=tmp;
		}
		return ret;
	}
};
