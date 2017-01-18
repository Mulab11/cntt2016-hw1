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
int h[MAXN];
bool OK(int x)
{
	int lst=0;
	int i;
	for(i=1;i<=n;i++)
	{
		if(h[i]+x<=lst)
		{
			return 0;
		}
		lst=max(lst+1,max(h[i]-x,1));
	}
	return 1;
}
struct KingdomAndTrees
{
	int minLevel(vector<int>_h)
	{
		int i;
		n=_h.size();
		for(i=1;i<=n;i++)
		{
			h[i]=_h[i-1];
		}
		int l=0,r=INF;
		int re;
		while(l<=r)
		{
			int mid=l+r>>1;
			if(OK(mid))
			{
				re=mid;
				r=mid-1;
			}
			else
			{
				l=mid+1;
			}
		}
		return re;
	}
};