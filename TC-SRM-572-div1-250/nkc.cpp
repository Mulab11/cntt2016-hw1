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
#define MAXN 1010
#define MAXM 1010
#define INF 1000000000
#define MOD 1000000007
#define eps 1e-8
#define ll long long
int n;
char a[MAXN];
int f[MAXN];
int fa(int x)
{
	return f[x]==x?x:f[x]=fa(f[x]);
}
int siz[MAXN];
int ct[MAXN][MAXN];
int ans;
bool vis[MAXN];
struct NewArenaPassword
{
	int minChange(string _a,int k)
	{
		int i,j,x;
		n=_a.size();
		for(i=1;i<=n;i++)
		{
			f[i]=i;
		}
		for(i=1;i<=n;i++)
		{
			a[i]=_a[i-1];
		}
		for(i=1;i<=k;i++)
		{
			if(fa(i)!=fa(n-k+i))
			{
				f[fa(i)]=fa(n-k+i);
			}
		}
		for(i=1;i<=n;i++)
		{
			siz[fa(i)]++;
			ct[fa(i)][a[i]]++;
		}
		for(i=1;i<=n;i++)
		{
			if(!vis[fa(i)])
			{
				x=fa(i);
				int mx=0;
				for(j='a';j<='z';j++)
				{
					mx=max(mx,ct[x][j]);
				}
				ans+=siz[x]-mx;
				vis[x]=1;
			}
		}
		return ans;
	}
};
/*
topco
ropen
*/