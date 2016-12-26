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

/*
离散， f[u][d]表示到u这个点，高度是d的最小代价
最短路即可
*/


const int maxn=55;
vector<string>mp;
vector<int>h;
int dsr[maxn],n,m;
ll dist[maxn][maxn];
bool vis[maxn][maxn];
bool upd(ll &x,ll y){
	if (y==-1) return 0;
	if (x==-1||y<x) return x=y,1;
	return 0;
}
void dijkstra(){
	rep(i,1,m){
		ll v=dist[0][i];
		rep(j,1,n-1) if (mp[0][j]=='Y')
			rep(k,1,i) upd(dist[j][k],v+abs(h[j]-dsr[k]));
	}
	rep(_,1,(n-1)*m){
		ll mn=-1,px,py;
		rep(i,1,n-1) rep(j,1,m) if (!vis[i][j]&&upd(mn,dist[i][j])) px=i,py=j;
		if (mn==-1) return;
		vis[px][py]=1;
		rep(j,1,n-1) if (mp[px][j]=='Y')
			rep(k,1,py) if (!vis[j][k])
				upd(dist[j][k],mn+abs(h[j]-dsr[k]));
	}
}
struct SkiResorts{
	ll minCost(vector<string>road,vector<int>alt){
		n=road.size();
		rep(i,0,alt.size()-1) dsr[++m]=alt[i];
		sort(dsr+1,dsr+m+1);
		m=unique(dsr+1,dsr+m+1)-dsr-1;
		mp=road,h=alt;
		memset(dist,-1,sizeof dist);
		rep(i,1,m) dist[0][i]=abs(dsr[i]-alt[0]),vis[0][i]=1;
		dijkstra();
		ll ans=-1;
		rep(i,1,m) upd(ans,dist[n-1][i]);
		return ans;
	}
};
