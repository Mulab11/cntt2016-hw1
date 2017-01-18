#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 51
using namespace std;
struct ppp
{int x,y;}b[N*N];
struct GooseInZooDivOne
{
	int fa[N*N],siz[N*N];
	int find(int x)
	{
		if(fa[x]==x) return x;
		fa[x]=find(fa[x]);
		return fa[x];
	}
	static const int mod=1e9+7;
	int ksm(int d,int c)
	{
		int ret=1;
		while(c)
		{
			if(c&1) ret=(long long)ret*d%mod;
			d=(long long)d*d%mod;c/=2;
		}
		return ret;
	}
	int count(vector <string> field, int dist)
	{
		int n=field.size(),m=field[0].size();
		int i,j,x,y,cnt=0;
		for(i=0;i<n;i++)
		for(j=0;j<m;j++)
		if(field[i][j]=='v') cnt++,b[cnt]=(ppp)
		{i,j};
		for(i=1;i<=cnt;i++)
		fa[i]=i,siz[i]=1;
		for(i=1;i<=cnt;i++)
		for(j=i+1;j<=cnt;j++)
		if(abs(b[i].x-b[j].x)+abs(b[i].y-b[j].y)<=dist)
		{
			x=find(i);y=find(j);
			if(x!=y)
			{
				fa[y]=x;
				siz[x]+=siz[y];
			}
		}
		int ji=0,ou=0;
		for(i=1;i<=cnt;i++)
		if(fa[i]==i)
		{
			if(siz[i]&1) ji++;
			else ou++;
		}
		if(ji==0) return ksm(2,ou)-1;
		else return ksm(2,ji+ou-1)-1; 
	}
};