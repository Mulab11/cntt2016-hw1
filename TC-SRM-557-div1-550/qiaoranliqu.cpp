#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>
#include<cmath>
#include<string>

#define ls (t<<1)
#define rs ((t<<1)+1)
#define mid ((l+r)>>1)
#define fi first
#define se second
#define mk make_pair
#define pb push_back

#define N 55
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k,A[N][N],B[N][N],vis[N],can[N][N],flag[N],ID[N],tot,Q[N],match[N];
void bfs(int x)
{
		memset(vis,0,sizeof(vis));
		Q[Q[0]=1]=x;
		vis[x]=1; 
		int l,i;
		for (l=1;l<=Q[0];++l)
		{
			 int p=Q[l];
			 for (i=0;i<n;++i)
			 	if (A[p][i])
			 	{
			 			can[x][i]=1;
			 			if (!vis[i]) Q[++Q[0]]=i,vis[i]=1;
			 	}
		}
}
int dfs(int x)
{
		int i;
		for (i=1;i<=tot;++i)
			if (B[x][i]&&!vis[i])
		{
				vis[i]=1;
				if (!match[i]||dfs(match[i]))
				{
					match[i]=x;
					return 1;	
				}
		}
		return 0;
}
class Incubator{
	public:
		int maxMagicalGirls(vector <string> love)
		{
			n=love.size();
			for (i=0;i<n;++i)
				for (j=0;j<n;++j)
				  A[i][j]=love[i][j]=='Y';
			for (i=0;i<n;++i) //求每个点能否到自己 
			{
					bfs(i);
					if (can[i][i]) flag[i]=1;
			}
			for (i=0;i<n;++i) if (!flag[i]) ID[++tot]=i;
			for (i=1;i<=tot;++i)
				for (j=1;j<=tot;++j) if (can[ID[i]][ID[j]]) B[i][j]=1;
			for (k=1;k<=tot;++k) //传递闭包做一下. 
				for (i=1;i<=tot;++i)
					for (j=1;j<=tot;++j)
						B[i][j]|=B[i][k]&B[k][j];
			int ans=0;
			for (i=1;i<=tot;++i)
			{
					memset(vis,0,sizeof(vis));
					if (dfs(i)) ++ans;
			}
			return tot-ans;
		}
};

