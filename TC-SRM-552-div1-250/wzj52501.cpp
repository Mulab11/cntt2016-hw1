#include<cstdio>
#include<cstring>
#include<cctype>
#include<algorithm>
#define rep(i,s,t) for(int i=s;i<=t;i++)
#define dwn(i,s,t) for(int i=s;i>=t;i--)
using namespace std;
typedef long long ll;
struct FoxPaintingBalls {
	ll theMax(ll A,ll B,ll C,int n) { 
		ll need=(ll)n*(n+1)/6,t=0;if(n%3==1) t=1;
		ll l=0,r;
		if(!need) r=A+B+C+1;
		else r=max(A,max(B,C))/need+100;
		while(l+1<r) {
			ll x=l+r>>1;
			ll la=A-need*x,lb=B-need*x,lc=C-need*x;
			if(la>=0&&lb>=0&&lc>=0&&la+lb+lc>=t*x) l=x;
			else r=x;
		}
		return l;
	}
};

