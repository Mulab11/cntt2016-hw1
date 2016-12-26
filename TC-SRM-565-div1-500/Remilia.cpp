#include<bits/stdc++.h>

#define rep(x,a,b) for (int x=a;x<=(int)b;x++)
#define drp(x,a,b) for (int x=a;x>=(int)b;x--)
#define cross(x,a) for (int x=hd[a];~x;x=nx[x])
#define ll long long
#define inf (1<<29)
#define PII pair<int,int>
#define PDD pair<double,double>
#define mk(a,b) make_pair(a,b)
#define fs first
#define sc second
#define pb push_back
#define VI vector<int>

using namespace std;

const int maxn=31638,maxm=1000005;
int mn[maxn+5],prm[maxn],cnt;
int val[maxm],fac[maxm],num[70];

/*
sg(n)=lambda(n)
筛出[L,R]的lambda即可
*/

struct TheDivisionGame{
	ll countWinningIntervals(int l,int r){
		rep(i,2,maxn){
			if (!mn[i]) prm[mn[i]=++cnt]=i;
			rep(j,1,cnt){
				int k=i*prm[j];
				if (k>maxn) break;
				mn[k]=j;
				if (j==mn[i]) break;
			}
		}
		rep(i,l,r) val[i-l+1]=i;
		rep(i,1,cnt){
			int p=prm[i],x=l/p*p;
			if (x<l) x+=p;
			while (x<=r){
				while (val[x-l+1]%p==0) fac[x-l+1]++,val[x-l+1]/=p;
				x+=p;
			}
		}
		rep(i,1,r-l+1) if (val[i]!=1) fac[i]++;
		ll ans=(ll)(r-l+1)*(r-l+2)/2,pre=0;
		num[pre]=1;
		rep(i,1,r-l+1){
			pre^=fac[i];
			ans-=num[pre];
			num[pre]++;
		}
		return ans;
	}
};
