#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 5010
using namespace std;
struct ppp
{int x,y,w;}b[N];
bool cmp(ppp x,ppp y)
{
	return x.w<y.w;
}
struct ArcadeManao
{
	int n,m;
	int c(int i,int j)
	{
		return i*m+j;
	}
	int fa[N];
	int find(int x)
	{
		if(fa[x]==x) return fa[x];
		fa[x]=find(fa[x]);
		return fa[x];
	}
	int shortestLadder(vector <string> level, int coinRow, int coinColumn)
	{
		n=level.size(),m=level[0].size();
		int i,j,k,x,y,cnt=0;
		for(i=0;i<n-1;i++)
		for(j=0;j<m;j++)
		if(level[i][j]=='X')//每个X点向右向下连边 
		{
			for(k=i+1;k<n;k++)
			if(level[k][j]=='X')
			{
				cnt++;
				b[cnt]=(ppp)
				{c(i,j),c(k,j),k-i};
				break;
			}
			if(j!=m-1&&level[i][j+1]=='X')
			cnt++,b[cnt]=(ppp)
			{c(i,j),c(i,j+1),0};
		}
		int E=n*m,S=c(coinRow-1,coinColumn-1);
		if(E==S) return 0;
		for(i=0;i<m;i++)
		cnt++,b[cnt]=(ppp)
		{c(n-1,i),E,0};
		sort(b+1,b+cnt+1,cmp);
		for(i=0;i<=E;i++)
		fa[i]=i;
		//用并查集维护答案 
		for(i=1;i<=cnt;i++)
		{
			fa[find(b[i].y)]=find(b[i].x);
			if(find(E)==find(S)) return b[i].w;
		}
	}
};