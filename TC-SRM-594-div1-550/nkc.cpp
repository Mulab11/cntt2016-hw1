#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 2510
#define M 20010
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
int dx[4]=
{0,0,1,-1},dy[4]=
{1,-1,0,0};
struct FoxAndGo3
{
	int n,m;
	int c(int i,int j)
	{
		return i*m+j;
	}
	int maxEmptyCells(vector <string> board)
	{
		n=board.size();m=board[0].size();
		int i,j,k,x,y;
		G.s=n*m;G.e=n*m+1;
		int tot=n*m;
		for(i=0;i<n;i++)
		for(j=0;j<m;j++)
		{
			if(board[i][j]=='o')//所有白格向周围的空格连边 
			{
				G.ae(G.s,c(i,j),1);//源点向所有白格连边 
				for(k=0;k<4;k++)
				{
					x=i+dx[k];y=j+dy[k];
					if(x<0||x>=n||y<0||y>=m||board[x][y]!='.') continue;
					G.ae(c(i,j),c(x,y),1);
				}
			}
			else if(board[i][j]=='.')
			G.ae(c(i,j),G.e,1);//空格向汇点连边 
			else tot--;
		}
		return tot-G.dinic();//答案为白格+空格-最小割 
	}
};