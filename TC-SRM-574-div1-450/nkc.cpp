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
struct PolygonTraversal
{
	int n;
	ll f[1<<18][18];
	ll count(int _n,vector<int>_pts)
	{
		int i,j,k;
		n=_n;
		int d=0;
		if(_pts.size()==2)
		{
			return 0;
		}
		for(i=0;i<_pts.size();i++)
		{
			_pts[i]--;
			d|=1<<_pts[i];
		}
		f[d][_pts[_pts.size()-1]]=1;
		int N=1<<n;
		for(i=0;i<N;i++)
		{
			for(j=0;j<n;j++)
			{
				if(f[i][j])
				{
					
					int l,r;
					for(l=(j+1)%n;!((i>>l)&1);l=(l+1)%n)
					{
						
					}
					for(r=(j-1+n)%n;!((i>>r)&1);r=(r-1+n)%n)
					{
						
					}
					for(k=(l+1)%n;k!=r;k=(k+1)%n)
					{
						if(!((i>>k)&1))
						{
							f[i|(1<<k)][k]+=f[i][j];
						}
					}
				}
			}
		}
		ll ans=0;
		for(i=0;i<n;i++)
		{
			if(i!=_pts[0]&&i!=(_pts[0]-1+n)%n&&i!=(_pts[0]+1)%n)
			{
				ans+=f[N-1][i];
			}
		}
		return ans;
	}
};