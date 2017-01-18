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
#define MAXN 60
#define MAXM 1010
#define INF 1000000000
#define MOD 1000000007
#define eps 1e-8
#define ll long long
int mp[MAXN][MAXN];
int n;
struct ColorfulWolves
{
	int getmin(vector<string>_mp)
	{
		int i,j,k;
		n=_mp.size();
		memset(mp,0x3f,sizeof(mp));
		for(i=0;i<n;i++)
		{
			int t=0;
			for(j=0;j<n;j++)
			{
				if(_mp[i][j]=='Y')
				{
					mp[i+1][j+1]=t++;
				}
			}
		}
		for(k=1;k<=n;k++)
		{
			for(i=1;i<=n;i++)
			{
				for(j=1;j<=n;j++)
				{
					mp[i][j]=min(mp[i][j],mp[i][k]+mp[k][j]);
				}
			}
		}
		return mp[1][n]>INF?-1:mp[1][n];
	}
};