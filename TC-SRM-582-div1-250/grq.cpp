#include<bits/stdc++.h>
#define sqr(x) (x)*(x)
#define ll long long
#define ull unsigned long long
#define ui unsigned int
#define vi vector<int>
#define pb push_back
#define ld long double
#define mp make_pair
#define pii pair<int,int>
#define debuge puts("isok")
#define debug(x) cout<<#x<<"="<<x<<endl
#define SS second
#define FF first
using namespace std;

bool check(vector<int> mgs, ll f,vector<pair<int,ll> > def){
	sort(mgs.begin(),mgs.end());
	for(int i=0;i<mgs.size();i++){
		ll tmp=f;
		for(int j=def.size()-1;~j;j--){
			if(def[j].FF>mgs[i])continue;
			if(tmp>def[j].SS) tmp-=def[j].SS,def[j].SS=0;
			else {def[j].SS-=tmp;break;}
		}
	}
//	for(int i=0;i<def.size();i++) printf("%lld ",def[i].SS);puts("");
	for(int i=0;i<def.size();i++) if(def[i].SS>0) return 0;
	return 1;
}
	vector<pair<int,ll> > def;
class SpaceWarDiv1{
public:
	long long minimalFatigue(vector<int> mgs, vector<int> es, vector<long long> ec){
		ll l=1,r=1ll<<60;
		def.clear();
		for(int i=0;i<es.size();i++) def.pb(mp(es[i],ec[i]));
		sort(def.begin(),def.end());
		while(l<r){
			ll mid=l+r>>1;
			if(check(mgs,mid,def)) r=mid; else l=mid+1;
		}
		debug(r);
		return (r<(1ll<<60))?r:-1;
	}
};
