#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 2010
#define M 20010
using namespace std;
struct Graph
{
	int s,e;
	int to[M],nxt[M],pre[N],w[M],c[M],cnt;
	Graph()
	{
		memset(pre,0,sizeof(pre));
		cnt=1;
	}
	void AE(int ff,int tt,int ww,int cc)
	{
		cnt++;
		to[cnt]=tt;
		nxt[cnt]=pre[ff];
		pre[ff]=cnt;
		w[cnt]=ww;
		c[cnt]=cc;
	}
	void ae(int ff,int tt,int ww,int cc)
	{
		AE(ff,tt,ww,cc);
		AE(tt,ff,0,-cc);
	}
	int d[N],q[N*10],bef[N];
	bool zai[N];
	bool spfa()
	{
		int h=1,t=1;
		memset(d,0x3f,sizeof(d));
		q[1]=s;d[s]=0;
		int i,j,x,y;
		while(h<=t)
		{
			x=q[h];h++;zai[x]=false;
			for(i=pre[x];i;i=nxt[i])
			if(w[i])
			{
				j=to[i];
				if(d[j]>d[x]+c[i])
				{
					bef[j]=i;
					d[j]=d[x]+c[i];
					if(!zai[j])
					{
						t++;q[t]=j;
						zai[j]=true;
					}
				}
			}
		}
		if(d[e]==0x3f3f3f3f) return false;
		return true;
	}
	int doit(int &ch)
	{
		int minn=707185547;
		int x=e,i;
		while(x!=s)
		{
			i=bef[x];
			minn=min(minn,w[i]);
			x=to[i^1];
		}
		ch-=minn;x=e;
		while(x!=s)
		{
			i=bef[x];
			w[i]-=minn;
			w[i^1]+=minn;
			x=to[i^1];
		}
		return minn*d[e];
	}
	int fyl(int x)
	{
		int ret=0;
		while(spfa())
		ret+=doit(x);
		if(x!=0) return -1;
		return ret;
	}
}G;
struct CurvyonRails
{
	int n,m;
	int c(int x,int y,int k)
	{
		return (x*m+y)*3+k;
	}
	int getmin(vector <string> field)
	{
		n=field.size(),m=field[0].size();
		int i,j;
		G.s=n*m*3;G.e=n*m*3+1;
		int tot1=0,tot2=0;
		for(i=0;i<n;i++)
		for(j=0;j<m;j++)
		if(field[i][j]!='w')
		{
			if((i+j)&1)//按黑白格拆点 
			{
				tot1++;
				G.ae(G.s,c(i,j,0),2,0);
				if(field[i][j]=='C')//关键点 
				{
					G.ae(c(i,j,0),c(i,j,1),1,0);
					G.ae(c(i,j,0),c(i,j,2),1,0);
					G.ae(c(i,j,0),c(i,j,1),1,1);
					G.ae(c(i,j,0),c(i,j,2),1,1);
				}
				else//非关键点 
				{
					G.ae(c(i,j,0),c(i,j,1),2,0);
					G.ae(c(i,j,0),c(i,j,2),2,0);
				}
				if(j) G.ae(c(i,j,1),c(i,j-1,1),1,0);
				if(j<m-1) G.ae(c(i,j,1),c(i,j+1,1),1,0);
				if(i) G.ae(c(i,j,2),c(i-1,j,2),1,0);
				if(i<n-1) G.ae(c(i,j,2),c(i+1,j,2),1,0);
			}
			else//同理建白点 
			{
				tot2++;
				G.ae(c(i,j,0),G.e,2,0);
				if(field[i][j]=='C')
				{
					G.ae(c(i,j,1),c(i,j,0),1,0);
					G.ae(c(i,j,2),c(i,j,0),1,0);
					G.ae(c(i,j,1),c(i,j,0),1,1);
					G.ae(c(i,j,2),c(i,j,0),1,1);
				}
				else
				{
					G.ae(c(i,j,1),c(i,j,0),2,0);
					G.ae(c(i,j,2),c(i,j,0),2,0);
				}
			}
		}
		if(tot1!=tot2) return -1;
		return G.fyl(2*tot1);//跑费用流 
	}
};