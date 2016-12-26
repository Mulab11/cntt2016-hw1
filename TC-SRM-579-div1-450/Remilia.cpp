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
string s;
const int maxn=55,maxm=20;
int m,ope[maxm],cls[maxm],dur[maxm];
int hd[maxn],to[maxn<<1],nx[maxn<<1],len[maxn<<1],cnt;
void addedge(int u,int v,int w){
	to[cnt]=v;nx[cnt]=hd[u];len[cnt]=w;hd[u]=cnt++;
}
int f[(1<<16)+5][maxm],dist[maxn][maxn];
void upd(int &x,int y){
	if (x==-1||y<x) x=y;
}
int lowbit(int x){return x&-x;}
int number(int x){
	int ret=0;
	while (x) x-=lowbit(x),ret++;
	return ret;
}

/*
先求最短路，然后dp{u,mask}表示当前在点u，已经买了mask这些店，最少时间。
然后傻逼DP即可。
*/

class TravellingPurchasingMan{
public:
	int maxStores(int n,vector<string>ite,vector<string>rds){
		m=ite.size();
		memset(hd,-1,sizeof hd);
		rep(i,0,m-1){
			int x=0,p=0;
			while (p<ite[i].size()&&ite[i][p]!=' ') x=x*10+ite[i][p]-'0',p++;
			p++,ope[i]=x,x=0;
			while (p<ite[i].size()&&ite[i][p]!=' ') x=x*10+ite[i][p]-'0',p++;
			p++,cls[i]=x,x=0;
			while (p<ite[i].size()&&ite[i][p]!=' ') x=x*10+ite[i][p]-'0',p++;
			dur[i]=x,x=0;
		}
		memset(dist,-1,sizeof dist);
		rep(i,0,rds.size()-1){
			int u=0,v=0,w=0,p=0;
			while (p<rds[i].size()&&rds[i][p]!=' ') u=u*10+rds[i][p]-'0',p++;p++;
			while (p<rds[i].size()&&rds[i][p]!=' ') v=v*10+rds[i][p]-'0',p++;p++;
			while (p<rds[i].size()&&rds[i][p]!=' ') w=w*10+rds[i][p]-'0',p++;
			upd(dist[u][v],w),upd(dist[v][u],w);
		}
		rep(i,0,n-1) dist[i][i]=0;
		rep(j,0,n-1) rep(i,0,n-1) if (~dist[i][j])
			rep(k,0,n-1) if (~dist[j][k]) upd(dist[i][k],dist[i][j]+dist[j][k]);
		memset(f,-1,sizeof f);
		rep(i,0,m-1){
			if (dist[n-1][i]!=-1&&dist[n-1][i]<=cls[i])
				upd(f[1<<i][i],max(dist[n-1][i],ope[i])+dur[i]);
		}
		int ans=0;
		rep(i,1,(1<<m)-1){
			rep(j,0,m-1){
				if (f[i][j]==-1) continue;
				rep(k,0,m-1) if (!((i>>k)&1)&&dist[j][k]!=-1&&f[i][j]+dist[j][k]<=cls[k])
					upd(f[i|(1<<k)][k],max(f[i][j]+dist[j][k],ope[k])+dur[k]);
			}
		}
		rep(i,1,(1<<m)-1) rep(j,0,m-1) if (~f[i][j]) ans=max(ans,number(i));
		return ans;
	}
};
