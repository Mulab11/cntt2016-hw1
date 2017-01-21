// BEGIN CUT HERE

// END CUT HERE
#line 5 "SparseFactorial.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
const ll inf=(1e6)+3;


ll ret[inf];
ll l[inf];

class SparseFactorial{
	ll minn[inf],div;
	ll tmp0[2];
	void doit(ll p,int k,ll n){
		memset(l,-1,sizeof(l));
		for (ll i=0;i<=p/2;++i) l[i*i%p]=i;
		for (ll i=0;i<n;++i){
			if (l[i%p]==-1){ret[i]=inf;continue;}
			tmp0[0]=l[i%p];
			tmp0[1]=(p-tmp0[0])%p;
			int sz=2-(tmp0[0]==tmp0[1]);
			ll res;
			for (ll cnt=k,j=0;cnt;++j){
				res=j/sz*p+tmp0[j%sz];
				ll tmp=i-res*res;
				for (;tmp%p==0&&cnt;tmp/=p) --cnt;
			}
			ret[i]=res;
		}
		for (ll j=0;j<div;++j) minn[j]=max(minn[j],ret[j%n]);
	}
	ll calc(ll n){
		ll ret=0;
		for (ll i=0;i<div;++i)
			ret+=max(0LL,(n-i+div)/div-(minn[i]*minn[i]-i+div)/div);
		return ret;
	}
	public:
	long long getCount(long long lo, long long hi, long long divisor){
		ll tmp=div=divisor;
		memset(minn,0,sizeof(minn));
		for (ll i=2;i<=tmp;++i)if (tmp%i==0){
			int k=0;ll x=1;
			for (;tmp%i==0;tmp/=i,x*=i) ++k;
			doit(i,k,x);
		}
		else if (i*i>tmp) i=tmp-1;
		return calc(hi)-calc(lo-1);
	}
	ll calc_t(ll n){return calc(n);}
	void debug(){
		printf("%lld\n",minn[2]);
	}
};

//this is for test
/*
SparseFactorial test;
int main(){
	printf("%lld\n",test.getCount(1, 1000000000000ll, 943471));
//	printf("%lld\n",test.calc_t(6));
//	test.debug();
	return 0;
}
*/
//test end
