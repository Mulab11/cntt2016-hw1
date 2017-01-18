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
int p[MAXN];
int n;
int t[MAXN],tv,tn;
struct MagicMolecule
{
	int maxMagicPower(vector<int>v,vector<string>mp)
	{
		int i,j,k;
		n=v.size();
		for(i=0;i<n;i++)
		{
			p[i]=i;
		}
		int re=-1;
		for(k=1;k<=n*n*n;k++)
		{
			random_shuffle(p,p+n);
			tv=tn=0;
			for(i=1;i<=n;i++)
			{
				bool flag=1;
				for(j=1;j<=tn;j++)
				{
					if(mp[p[i]][t[j]]=='N')
					{
						flag=0;
						break;
					}
				}
				if(flag)
				{
					t[++tn]=p[i];
					tv+=v[p[i]];
				}
			}
			if(tn*3>=n*2)
			{
				re=max(re,tv);
			}
		}
		return re;
	}
};