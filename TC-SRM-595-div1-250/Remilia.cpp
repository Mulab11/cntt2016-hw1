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
using namespace std;
const int maxn=1005;
int ans,n,blt[maxn],vis[55];
ll qpow(ll a,int b){
	ll ret=1;
	for (;b;b>>=1,a=a*a) if (b&1) ret=ret*a;
	return ret;
}

/*
看一下每个点最后是被那个操作染的。
pow一下就好了啊。
*/

class LittleElephantAndIntervalsDiv1{
public:
	ll getNumber(int m,vector<int>l,vector<int>r){
		n=l.size();
		rep(i,1,n) rep(j,l[i-1],r[i-1]) blt[j]=i;
		rep(i,1,m) vis[blt[i]]=1;
		rep(i,1,n) if (vis[i]) ans++;
		return qpow(2,ans); 
	}
};
