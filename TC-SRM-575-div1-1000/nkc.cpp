#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 5010
#define M 30010
#define inf 707185547
using namespace std;
struct Graph
{
	int to[M],nxt[M],pre[N],w[M],cnt;
	int s,e;
	Graph()
	{cnt=1;memset(pre,0,sizeof(pre));}
	void AE(int ff,int tt,int ww)
	{
		cnt++;
		to[cnt]=tt;
		nxt[cnt]=pre[ff];
		w[cnt]=ww;
		pre[ff]=cnt;
	}
	void ae(int ff,int tt,int ww)
	{
		AE(ff,tt,ww);
		AE(tt,ff,0);
	}
	int d[N],q[N],h,t;
	bool bfs()
	{
		memset(d,0,sizeof(d));
		h=t=1;d[s]=1;
		q[1]=s;
		int i,j,x,y;
		while(h<=t)
		{
			x=q[h];h++;
			for(i=pre[x];i;i=nxt[i])
			if(w[i])
			{
				j=to[i];
				if(d[j]) continue;
				d[j]=d[x]+1;
				t++;q[t]=j;
			}
		}
		if(d[e]) return true;
		return false;
	}
	int dfs(int x,int v)
	{
		if(x==e||v==0) return v;
		int i,j,ret=0;
		for(i=pre[x];i;i=nxt[i])
		if(w[i])
		{
			j=to[i];
			if(d[j]!=d[x]+1) continue;
			int f=dfs(j,min(w[i],v));
			v-=f;
			ret+=f;
			w[i]-=f;
			w[i^1]+=f;
			if(!v) break;
		}
		if(!ret) d[x]=-1;
		return ret;
	}
	int dinic()//网络流 
	{
		int ret=0;
		while(bfs())
		ret+=dfs(s,inf);
		return ret;
	}
}G;
struct TheTilesDivOne
{
	int n,m;
	int c(int x,int y,int k)
	{
		return (x*m+y)*2+k;
	}
	int find(vector <string> board)
	{
		n=board.size(),m=board[0].size();
		int i,j;
		G.s=n*m*2;G.e=n*m*2+1;
		for(i=0;i<n;i++)
		for(j=0;j<m;j++)
		if(board[i][j]!='X')
		{
			G.ae(c(i,j,0),c(i,j,1),1);//把每个点拆点 
			if((i+j)&1)
			{
				if(j&1) G.ae(c(i,j,1),G.e,1);//奇数列白格连向汇点 
				else G.ae(G.s,c(i,j,0),1);//源点连向偶数列白格 
			}
			else
			{
				//根据黑格奇偶性连边 
				if(j&1)
				{
					if(j) G.ae(c(i,j-1,1),c(i,j,0),1);
					if(j<m-1) G.ae(c(i,j+1,1),c(i,j,0),1);
					if(i) G.ae(c(i,j,1),c(i-1,j,0),1);
					if(i<n-1) G.ae(c(i,j,1),c(i+1,j,0),1);
				}
				else
				{
					if(j) G.ae(c(i,j,1),c(i,j-1,0),1);
					if(j<m-1) G.ae(c(i,j,1),c(i,j+1,0),1);
					if(i) G.ae(c(i-1,j,1),c(i,j,0),1);
					if(i<n-1) G.ae(c(i+1,j,1),c(i,j,0),1);
				}
			}
		}
		return G.dinic();//跑网络流 
	}
};