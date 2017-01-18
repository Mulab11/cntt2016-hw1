#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 1010
using namespace std;
struct ppp
{int x,y,w;};
vector<ppp>E,EE;
struct FoxTheLinguist
{
	int mn[N],bef[N];
	int vis[N],A[N];
	int ZHULIU(int n)
	{
		int ret=0;
		while(1)
		{
			int i,j,x,y,tn=-1;
			memset(mn,0x3f,sizeof(mn));
			memset(vis,0,sizeof(vis));
			memset(A,-1,sizeof(A));
			EE.clear();
			for(i=0;i<E.size();i++)
			{
				if(E[i].w<mn[E[i].y])
				mn[E[i].y]=E[i].w,bef[E[i].y]=E[i].x;
			}
			for(i=0;i<n;i++)
			if(mn[i]==0x3f3f3f3f) return -1;
			int ti=0;
			for(i=0;i<n;i++)
			{
				ret+=mn[i];
				x=i;ti++;
				while(x!=n&&!vis[x]) vis[x]=ti,x=bef[x];
				if(x==n||vis[x]!=ti) continue;
				tn++;
				A[x]=tn;
				for(y=bef[x];y!=x;y=bef[y])
				A[y]=tn;
			}
			if(tn==-1) return ret;
			for(i=0;i<=n;i++)
			if(A[i]==-1) tn++,A[i]=tn;
			for(i=0;i<E.size();i++)
			if(A[E[i].x]!=A[E[i].y])
			EE.push_back((ppp)
			{A[E[i].x],A[E[i].y],E[i].w-mn[E[i].y]});
			E=EE;
			n=tn;
		}
	}
	int minimalHours(int n, vector <string> courseInfo)
	{
		string S="";
		int i,j,x,y,z;
		for(i=0;i<courseInfo.size();i++)
		S+=courseInfo[i];
		for(i=0;i<S.size();i+=12)
		{
			x=(S[i]-65)*10+S[i+1]-48;
			y=(S[i+4]-65)*10+S[i+5]-48;
			z=(S[i+7]-48)*1000+(S[i+8]-48)*100+(S[i+9]-48)*10+S[i+10]-48;
			E.push_back((ppp)
			{x,y,z});
		}
		for(i=0;i<n;i++)
		for(j=1;j<=9;j++)
		E.push_back((ppp)
		{i*10+j,i*10+j-1,0});
		for(i=0;i<n;i++)
		E.push_back((ppp)
		{n*10,i*10,0});
		return ZHULIU(n*10);
	}
};