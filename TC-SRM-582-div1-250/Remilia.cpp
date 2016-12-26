#include <bits/stdc++.h>

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
const int maxn=55;
struct enemy{
	int sth;
	ll cnt;
	enemy(int s=0,ll c=0){sth=s,cnt=c;}
	bool operator <(const enemy&x)const{return sth<x.sth;}
}a[maxn],tmp[maxn];

/*
二分答案，然后排个序xjb判判就好了。
*/

class SpaceWarDiv1{
public:
	ll minimalFatigue(vector<int>ms,vector<int>es,vector<ll>ec){
		int n=ms.size(),m=es.size();
		rep(i,0,m-1) a[i]=enemy(es[i],ec[i]);
		sort(a,a+m);
		sort(ms.begin(),ms.end());
		if (ms[n-1]<a[m-1].sth) return -1;
		ll l=0,r=0;
		rep(i,0,m-1) r+=ec[i];
		while (l<r){
			ll mid=l+r>>1;
			rep(i,0,m-1) tmp[i]=a[i];
			drp(i,n-1,0){
				ll rem=mid;
				drp(j,m-1,0){
					if (tmp[j].sth>ms[i]) continue;
					if (rem<=tmp[j].cnt){tmp[j].cnt-=rem;break;}
						else rem-=tmp[j].cnt,tmp[j].cnt=0;
				}
			}
			bool f=1;
			rep(i,0,m-1) if (tmp[i].cnt){f=0;break;}
			if (f) r=mid;else l=mid+1;
		}
		return l;
	}
};
