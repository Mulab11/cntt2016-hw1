#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<iomanip>
#include<vector>
#include<map>
#include<set>
#include<bitset>
#include<queue>
#include<stack>
using namespace std;
#define MAXN 15
#define MAXM 3000010
#define INF 1000000000
#define MOD 1000000007
#define eps 1e-8
#define ll long long
int N,M,n=-1,m,K;
int LIMN;
int x[MAXN],y[MAXN];
int v[MAXN];
int nowx[MAXN],nowy[MAXN];
int f[MAXM];
bool vis[MAXM];
int mi[14];
int w(int x,int y)
{
	return x/mi[y]%3;
}
int tw(int x,int y)
{
	return mi[y]*x;
}
int dp(int d,int tim,int hid)
{
	if(vis[d])
	{
		return f[d];
	}
	int i;
	vis[d]=1;
	if(!hid)
	{
		memset(nowx,0,sizeof(nowx));
		memset(nowy,0,sizeof(nowy));
		for(i=0;i<=n;i++)
		{
			if(w(d,i)!=2)
			{
				nowx[x[i]]^=1;
				nowy[y[i]]^=1;
			}
		}
		for(i=0;i<N;i++)
		{
			if(nowx[i])
			{
				return f[d]=INF;
			}
		}
		for(i=0;i<M;i++)
		{
			if(nowy[i])
			{
				return f[d]=INF;
			}
		}
		return f[d]=0;
	}
	
	if(!tim)
	{
		for(i=0;i<=n;i++)
		{
			if(!w(d,i))
			{
				if(!dp(d+tw(2,i),tim,hid-1))
				{
					return f[d]=0;
				}
			}
		}
		return f[d]=INF;
	}
	for(i=0;i<=n;i++)
	{
		if(!w(d,i))
		{
			f[d]=max(f[d],min(dp(d+tw(1,i),tim-1,hid),dp(d+tw(2,i),tim-1,hid-1)+1));
		}
	}
	return f[d];
}
struct MagicalHats
{
	int findMaximumReward(vector<string>mp,vector<int>vs,int _K)
	{
		int i,j;
		mi[0]=1;
		for(i=1;i<=13;i++)
		{
			mi[i]=mi[i-1]*3;
		}
		K=_K;
		N=mp.size();
		M=mp[0].size();
		for(i=0;i<N;i++)
		{
			for(j=0;j<M;j++)
			{
				if(mp[i][j]=='H')
				{
					x[++n]=i;
					y[n]=j;
				}
			}
		}
		m=vs.size();
		for(i=1;i<=m;i++)
		{
			v[i]=vs[i-1];
		}
		sort(v+1,v+m+1);
		int t=dp(0,K,m);
		if(t>20)
		{
			return -1;
		}
		int re=0;
		for(i=1;i<=t;i++)
		{
			re+=v[i];
		}
		return re;
	}
};

/*
.H.H.H.H.
H.H.H.H.H
.H.H.H.H.
1,1,1,1,1,1,1,1,1
9
*/