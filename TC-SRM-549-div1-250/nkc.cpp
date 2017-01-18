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
#define MAXN 5010
#define MAXM 1010
#define INF 1000000000
#define MOD 1000000007
#define eps 1e-8
#define ll long long
struct vec
{
	int to;
	int fro;
};
vec mp[MAXN];
int tai[MAXN],cnt;
int n,m;
int h1[MAXN],r1[MAXN],h2[MAXN],r2[MAXN];
int bf[MAXN];
int vis[MAXN];
int T;
inline void be(int x,int y)
{
	mp[++cnt].to=y;
	mp[cnt].fro=tai[x];
	tai[x]=cnt;
}
bool find(int x)
{
	int i,y;
	for(i=tai[x];i;i=mp[i].fro)
	{
		y=mp[i].to;
		if(bf[y]==x||vis[y]==T)
		{
			continue ;
		}
		vis[y]=T;
		if(!bf[y]||find(bf[y]))
		{
			bf[y]=x;
			return 1;
		}
	}
	return 0;
}
struct PointyWizardHats
{
	int getNumHats(vector<int>_h1,vector<int>_r1,vector<int>_h2,vector<int>_r2)
	{
		int i,j;
		n=_h1.size();
		m=_h2.size();
		for(i=1;i<=n;i++)
		{
			h1[i]=_h1[i-1];
			r1[i]=_r1[i-1];
		}
		for(i=1;i<=m;i++)
		{
			h2[i]=_h2[i-1];
			r2[i]=_r2[i-1];
		}
		for(i=1;i<=n;i++)
		{
			for(j=1;j<=m;j++)
			{
				if(r1[i]<r2[j]&&1.0*h1[i]/r1[i]>1.0*h2[j]/r2[j])
				{
					be(i,j);
				}
			}
		}
		int re=0;
		for(i=1;i<=n;i++)
		{
			T++;
			re+=find(i);
		}
		return re;
	}
};