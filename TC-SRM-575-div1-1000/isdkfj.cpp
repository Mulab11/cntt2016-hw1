#include <bits/stdc++.h>

using namespace std;

const int N=500005,M=2500005,inf=0x3f3f3f3f;
const int dx[]={0,-1,0,1},dy[]={1,0,-1,0};
int s,t,fst[N],to[M],nxt[M],tt,w[M],d[N],q[N];
void ad(int x,int y,int z){
	nxt[++tt]=fst[x];fst[x]=tt;to[tt]=y;w[tt]=z;
	nxt[++tt]=fst[y];fst[y]=tt;to[tt]=x;w[tt]=0;
}
bool bfs(){//找增广路 
	memset(d,0,(t+1)<<2);
	int l=0,r=0;q[0]=s;d[s]=1;
	while(l<=r){
		int x=q[l++];
		for(int i=fst[x];i;i=nxt[i])
		if(w[i]>0&&!d[to[i]]){
			d[to[i]]=d[x]+1;
			q[++r]=to[i];
		}
	}
	return d[t]>0;
}
int dfs(int x,int a){//dfs增广 
	if(x==t||!a)return a;
	int flow=0,f;
	for(int i=fst[x];i;i=nxt[i])
	if(d[to[i]]==d[x]+1&&(f=dfs(to[i],min(a,w[i])))>0){
		flow+=f;a-=f;
		w[i]-=f;w[i^1]+=f;
		if(a==0)break;
	}
	return flow;
}
int n,m,f[505][505],g[505][505],tot;

class TheTilesDivOne {
public:
	int find(vector <string> board) {
		n=board.size();
		m=board[0].size();
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j)
			f[i][j]=board[i-1][j-1]=='X'?0:(((i+j)%2==0)?1:2);//初始化 
		tt=1;
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j)
				if(f[i][j]){
					g[i][j]=++tot;//标号 
					if(f[i][j]==1){
						++tot;
						ad(tot-1,tot,1);//黑色点限流1 
					}
				}
		s=tot+1;t=tot+2;
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j){
				if((i&1)&&f[i][j]==2){//源点向奇数行的白点连边 
					int id=g[i][j];
						for(int k=0,x,y;k<4;++k){
						x=i+dx[k];y=j+dy[k];
						if(f[x][y]==1)ad(id,g[x][y],1);
					}
					ad(s,id,1);
				}
				if(f[i][j]==1){//向四周连边 
					int id=g[i][j]+1;
					for(int k=0,x,y;k<4;++k){
						x=i+dx[k];y=j+dy[k];
						if((x&1)==0&&f[x][y]==2)ad(id,g[x][y],1);
					}
				}
				if((i&1)==0&&f[i][j]==2)ad(g[i][j],t,1);//偶数行的白点向汇点连边 
			}
		int ans=0;
		while(bfs())ans+=dfs(s,inf);//网络流 
		return ans;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
