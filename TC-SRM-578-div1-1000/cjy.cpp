#include<bits/stdc++.h>
using namespace std;
int n,i,ans,j,a[55][55],b[55][55],lx[55],ly[55],slack[55],vx[55],vy[55],c[55],s,d,X,oo=1e9;
vector<int> E[55];
int link(int x)
{
	vx[x]=1;
	for(int i=1;i<=n;i++)if(!vy[i])if(lx[x]+ly[i]!=a[x][i]) slack[i]=min(slack[i],lx[x]+ly[i]-a[x][i]);else if(vy[i]=1,!c[i]||link(c[i]))return c[i]=x;
	return 0;
}
int solve(int x,int f,int _x,int _f,int G)//KM
{
	for(auto y : E[x])for(auto z : E[_x])if(y!=f&&y!=G&&z!=_f)b[y][z]=solve(y,x,z,_x,G);
	for(memset(a,i=0,sizeof(a)),memset(c,0,sizeof(c)),memset(ly,0,sizeof(ly));i<E[x].size();i++)for(j=0;j<E[_x].size();j++)if(E[x][i]!=f&&E[x][i]!=G&&E[_x][j]!=_f)a[i+1][j+1]=b[E[x][i]][E[_x][j]];
	for(n=max(E[x].size(),E[_x].size()),i=1;i<=n;i++)for(j=1,lx[i]=-oo;j<=n;j++)lx[i]=max(lx[i],a[i][j]);
	for(X=1;X<=n;X++)
	{
		for(j=1;j<=n;j++)slack[j]=oo;
		while(1)
		{
			for(i=1;i<=n;i++)vx[i]=vy[i]=0;
			if(link(X))break;
			for(d=oo,i=1;i<=n;i++)if(!vy[i])d=min(slack[i],d);
			for(i=1;i<=n;i++)if(vx[i])lx[i]-=d;
			for(i=1;i<=n;i++)if(vy[i])ly[i]+=d;else slack[i]-=d;
		}
	}
	for(s=i=1;i<=n;i++)s+=lx[i]+ly[i];
	return s;
}
void dfs2(int x,int f,int G,int F)//枚举根
{
	for(auto y : E[x])if(y!=f)dfs2(y,x,G,F);
	ans=max(ans,solve(x,0,G,F,G));
}
void dfs1(int x,int f)
{
	if(f)dfs2(f,x,x,f);
	for(auto y : E[x])if(y!=f)dfs1(y,x);
}
struct DeerInZooDivOne
{
	public:
		int getmax(vector<int> a,vector<int> b)
		{
			for(;i<a.size();i++)E[++a[i]].push_back(++b[i]),E[b[i]].push_back(a[i]);
			return dfs1(1,0),ans;
		}
};
