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
bool col[maxn],imp[maxn];
int cnt,to[maxn<<1],nx[maxn<<1],hd[maxn],lgt[maxn<<1];
void addedge(int u,int v){
	to[cnt]=v;nx[cnt]=hd[u];hd[u]=cnt++;
}
int f[maxn][maxn],g[maxn][maxn];
int nc,n;
int upd(int &x,int y){if (x==-1||x>y) x=y;}
void dfs(int u,int fa){
	cross(i,u){
		int v=to[i];
		if (v==fa) continue;
		dfs(v,u);
	}
	memset(g,-1,sizeof g);
	g[0][0]=nc=0;
	cross(i,u){
		int v=to[i];
		if (v==fa) continue;
		++nc;
		rep(j,0,n){
			if (!~f[v][j]) continue;
			rep(k,0,n) if (~g[nc-1][k]) upd(g[nc][k+j],g[nc-1][k]+f[v][j]);
		}
	}
	drp(i,n,1) if (~g[nc][i]) upd(g[nc][i-1],g[nc][i]);
	if (imp[u]){
		if (col[u]) rep(k,0,n){
			if (!~g[nc][k]) continue;
			if (k&1) upd(g[nc][k+1],g[nc][k]+1);
			else rep(l,0,k/2) upd(f[u][k-l*2],g[nc][k]-l);
		}
		else rep(k,0,n){
			if (!~g[nc][k]) continue;
			if (k&1) rep(l,0,k/2) upd(f[u][k-l*2],g[nc][k]-l);
			else upd(g[nc][k+1],g[nc][k]+1);
		}
	}
	else{
		rep(k,0,n){
			if (!~g[nc][k]) continue;
			rep(l,0,k/2) upd(f[u][k-l*2],g[nc][k]-l);
		}
	}
}

/*
不用管的边可以缩起来
本来就黑的边可以断开
剩下的就是个简单贪心
*/

class TurnOnLamps{
public:
	int minimize(vector<int>road,string init,string import){
		n=road.size();
		memset(hd,-1,sizeof hd);
		rep(i,0,n-1) addedge(road[i],i+1),addedge(i+1,road[i]);
		rep(i,0,n-1) imp[i+1]=import[i]-'0',col[i+1]=init[i]-'0';
		memset(f,-1,sizeof f);
		dfs(0,-1);
		return f[0][0];
	}
};
