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
struct PenguinSledding
{
	int d[MAXN];
	ll ans;
	bool mp[MAXN][MAXN];
	ll mi(ll x,ll y)
	{
		ll re=1;
		while(y)
		{
			if(y&1)
			{
				re*=x;
			}
			x*=x;
			y>>=1;
		}
		return re;
	}
	ll countDesigns(int n,vector<int>v1,vector<int>v2)
	{
		int i,j,k;
		for(i=0;i<v1.size();i++)
		{
			d[v1[i]]++;
			d[v2[i]]++;
			mp[v1[i]][v2[i]]=mp[v2[i]][v1[i]]=1;
		}
		int t=0;
		for(i=1;i<=n;i++)
		{
			ans+=(ll)mi(2,d[i])-1;
			t+=d[i];
		}
		ans-=v1.size();
		for(i=1;i<=n;i++)
		{
			for(j=i+1;j<=n;j++)
			{
				for(k=j+1;k<=n;k++)
				{
					if(mp[i][j]&&mp[i][k]&&mp[j][k])
					{
						ans++;
					}
				}
			}
		}
		ans++;
		return ans;
	}
};