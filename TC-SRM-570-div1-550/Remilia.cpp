#include<bita/stdc++.h>

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
#define VS vector<string>
#define MC(a,b) memcpy(a,b,sizeof b)
#define MS(a,b) memset(a,b,sizeof a)

using namespace std;

/*
求出一个人的期望然后乘以二就行了。

一个人有x个点， y个连通块，答案是max(2y-x-2,0)

那么背包一下就没了dp[u][k][0,1]表示u子树2y-x=k的答案。
*/

const int maxn=40;
int cnt,to[maxn<<1],nx[maxn<<1],hd[maxn],n;
void addedge(int u,int v){
	to[cnt]=v;nx[cnt]=hd[u];hd[u]=cnt++;
}
ll f[maxn][2][maxn][maxn],g[maxn][maxn],h[maxn][maxn];
void dp(int u,int fa){
	cross(i,u){
		int v=to[i];
		if (v!=fa) dp(v,u);
	}
	f[u][0][0][0]=f[u][1][1][1]=1;
	cross(i,u){
		int v=to[i];
		if (v==fa) continue;
		MS(g,0),MS(h,0);
		rep(j,0,n) rep(k,j,n){
			if (!f[v][0][j][k]) continue;
			int w=f[v][0][j][k];
			rep(_,0,n-j) rep(__,_,n-k) g[_+j][__+k]+=f[u][0][_][__]*w;
			rep(_,1,n-j) rep(__,_,n-k) h[_+j][__+k]+=f[u][1][_][__]*w;
		}
		rep(j,1,n) rep(k,j,n){
			if (!f[v][1][j][k]) continue;
			int w=f[v][1][j][k];
			rep(_,0,n-j) rep(__,_,n-k) g[_+j][__+k]+=f[u][0][_][__]*w;
			rep(_,1,n-j+1) rep(__,_,n-k) h[_+j-1][__+k]+=f[u][1][_][__]*w;
		}
		MC(f[u][0],g),MC(f[u][1],h);
	}
}
struct CentaurCompany{
	double getvalue(VI a,VI b){
		n=a.size()+1;
		memset(hd,-1,sizeof hd);
		rep(i,0,n-2) addedge(a[i],b[i]),addedge(b[i],a[i]);
		dp(1,0);
		double ans=0;
		rep(i,1,n) rep(j,i,n) ans+=max((i-1)*2-j,0)*(f[1][0][i][j]+f[1][1][i][j]);
		ans*=pow(0.5,n-1);
		return ans;
	}
};
