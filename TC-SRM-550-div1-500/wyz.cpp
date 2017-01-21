// BEGIN CUT HERE

// END CUT HERE
#line 5 "CheckerExpansion.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn=50;

class CheckerExpansion{
	ll bin[maxn+2];
	char calc(ll x,ll y,int k){
//		printf("%lld %lld %d\n",x,y,k);
		if (k==1){
			if (x==0&&y==0) return 'A';
			if (x==1&&y==1) return 'B';
			if (x==2&&y==0) return 'B';
			return '.';
		}
		if (y<bin[k-1]){
			if (x==bin[k]-1) return '.';
			if (x>=bin[k]) return calc(x-bin[k],y,k-1);
			return calc(x,y,k-1);
		}
		else{
			if (x<bin[k-1]||x>=bin[k]+bin[k-1]) return '.';
			return calc(x-bin[k-1],y-bin[k-1],k-1);
		}
		return 'X';
	}
	public:
	vector <string> resultAfter(long long t, long long x0, long long y0, int w, int h){
		for (int i=0;i<=maxn;++i) bin[i]=1LL<<i;
		vector<string> ret;
		for (ll i=y0+h-1;i>=y0;--i){
			string now="";
			for (ll j=x0;j<=x0+w-1;++j)
				if (i+j<=(t-1)*2) now.push_back(calc(j,i,maxn));
				else now.push_back('.');
			ret.push_back(now);
		}
		return ret;
	}
};
