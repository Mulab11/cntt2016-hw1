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

/*
可知链长度一定<=2
是三角形或菊花
*/

const int maxn=55;
ll qpow(ll a,ll b){
	ll ret=1;
	for (;b;b>>=1,a=a*a) if (b&1) ret=ret*a;
	return ret;
}
ll ans=0;
int n,m,d[maxn];
int mp[maxn][maxn];
struct PenguinSledding{
	ll countDesigns(int n,vector<int>cp1,vector<int>cp2){
		m=cp1.size();
		rep(i,0,m-1) d[cp1[i]]++,d[cp2[i]]++,mp[cp1[i]][cp2[i]]=mp[cp2[i]][cp1[i]]=1;
		rep(i,1,n) rep(j,i+1,n) if (mp[i][j]) rep(k,j+1,n) if (mp[i][k]&&mp[j][k]) ans++;
		ans+=m+1;
		rep(i,1,n) ans+=qpow(2,d[i])-d[i]-1;
		return ans;
	}
};
