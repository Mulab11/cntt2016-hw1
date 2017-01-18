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
#define MAXN 110
#define MAXM 1010
#define INF 1000000000
#define MOD 1000000007
#define eps 1e-8
#define ll long long
struct EelAndRabbit
{
	int l[MAXN],r[MAXN];
	int tls[MAXN],tln,mx;
	map<int,int>h;
	int n;
	int ans;
	int getmax(vector<int> _L,vector<int> _l)
	{
		int i,j,k;
		n=_l.size();
		for(i=1;i<=n;i++)
		{
			l[i]=_l[i-1];
			r[i]=l[i]+_L[i-1];
			tls[++tln]=l[i];
			tls[++tln]=r[i];
		}
		sort(tls+1,tls+tln+1);
		for(i=1;i<=tln;i++)
		{
			if(tls[i]!=tls[i-1])
			{
				h[tls[i]]=++mx;
			}
		}
		for(i=1;i<=n;i++)
		{
			l[i]=h[l[i]];
			r[i]=h[r[i]];
		}
		for(i=1;i<=mx;i++)
		{
			for(j=i;j<=mx;j++)
			{
				int t=0;
				for(k=1;k<=n;k++)
				{
					if((l[k]<=i&&r[k]>=i)||(l[k]<=j&&r[k]>=j))
					{
						t++;
					}
				}
				ans=max(ans,t);
			}
		}
		return ans;
	}
};