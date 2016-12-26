// by ξ

#include <bits/stdc++.h>

#define For(i,l,r) for(int _r=r,i=l;i<=_r;++i)
#define rep(i,l,r) for(int _r=r,i=l;i<_r;++i)

using namespace std;

typedef int Arr[20000];

const int inf=1e9,dx[]={1,-1,0,0},dy[]={0,0,1,-1};

int n,m,idx,S,T,tot=1,ID[66][66],DI[66][66];
char s[66][66];

Arr he,ne,g,dis,pp,ee;

struct TheTilesDivOne{
	void Add(int u,int v){
		pp[++tot]=v;ne[tot]=he[u];he[u]=tot;ee[tot]=1;
		pp[++tot]=u;ne[tot]=he[v];he[v]=tot;
	}
	
	int bfs(){
		For(i,1,idx)dis[i]=inf;dis[S]=0;
		int l=0,r=1;
		for(g[l]=S;l<r;++l){
			int u=g[l];
			for(int e=he[u];e;e=ne[e])if(ee[e]>0){
				int v=pp[e];
				if(dis[v]>dis[u]+1){
					dis[g[r++]=v]=dis[u]+1;
					if(v==T)return 1;
				}
			}
		}return 0;
	}
	
	int dinic(int u,int ff){
		if(u==T || ff<=0)return max(ff,0);
		int an=0;
		for(int e=he[u];e;e=ne[e])if(dis[pp[e]]==dis[u]+1){
			int tmp=dinic(pp[e],min(ff,ee[e]));
			ee[e]-=tmp;ee[e^1]+=tmp;
			ff-=tmp;an+=tmp;
			if(!ff)return an;
		}
		return an?an:(dis[u]=-1,0);
	}
	
	int MaxFlow(){
		int an=0;
		for(;bfs();)an+=dinic(S,inf);
		return an;
	}
	
	int find(vector<string> board){
		// 拆点三列，奇数列白点、黑点、偶数列白点
		// 相邻点连边，黑点拆点限流，跑最大流
		n=board.size();m=board[0].length();
		rep(i,0,n)rep(j,0,m)s[i+1][j+1]=board[i][j];
		For(i,1,n)For(j,1,m)if(s[i][j]=='.')ID[i][j]=++idx;
		For(i,1,n)For(j,1,m)if(!(i+j&1) && s[i][j]=='.')DI[i][j]=++idx,Add(ID[i][j],DI[i][j]);
		T=++idx;
		For(i,1,n)For(j,1,m)if(s[i][j]=='.')
		if(i+j&1)
			if(i&1)Add(S,ID[i][j]);else Add(ID[i][j],T);
		else rep(d,0,4){
			int x=i+dx[d],y=j+dy[d];
			if(x && x<=n && y && y<=m && s[x][y]=='.'){
				if(x&1)Add(ID[x][y],ID[i][j]);
					else Add(DI[i][j],ID[x][y]);
			}
		}
		return MaxFlow();
	}
};
