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
struct TeamContest
{
	int a[MAXN],n;
	int v;
	bool used[MAXN];
	int ans;
	int worstRank(vector<int> s)
	{
		ans=1;
		int i,j,k;
		v=max(s[0],max(s[1],s[2]))+min(s[0],min(s[1],s[2]));
		for(i=3;i<s.size();i++)
		{
			a[++n]=s[i];
		}
		sort(a+1,a+n+1);
		for(i=n;i;i--)
		{
			if(used[i])
			{
				continue ;
			}
			bool flag=0;
			for(j=1;j<i;j++)
			{
				if(a[j]+a[i]>v&&!used[j])
				{
					for(k=j+1;k<i;k++)
					{
						if(!used[k])
						{
							used[i]=used[j]=used[k]=1;
							flag=1;
							ans++;
							break;
						}
					}
				}
				if(flag)
				{
					break;
				}
			}
			if(!flag)
			{
				used[i]=1;
				for(j=1;j<=n;j++)
				{
					if(!used[j])
					{
						used[j]=1;
					}
				}
				for(j++;j<=n;j++)
				{
					if(!used[j])
					{
						used[j]=1;
					}
				}
			}
		}
		return ans;
	}
};