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
#define MAXM 250010
#define INF 1000000000
#define MOD 1000000007
#define eps 1e-8
#define ll long long
struct EnclosingTriangle
{
	struct pt
	{
		int x;
		int y;
		pt()
		{
			
		}
		pt(int _x,int _y)
		{
			x=_x;
			y=_y;
		}
		friend pt operator -(pt x,pt y)
		{
			return pt(x.x-y.x,x.y-y.y);
		}
		friend ll operator *(pt x,pt y)
		{
			return (ll)x.x*y.y-(ll)x.y*y.x;
		}
	};
	int n,m,N;
	int x[MAXN],y[MAXN];
	int f[MAXM];
	ll s[MAXM];
	ll ans;
	pt ps(int x)
	{
		pt re;
		if(x>=1&&x<=m)
		{
			re.x=0;
			re.y=x-1;
		}
		if(x>=m+1&&x<=m*2)
		{
			re.x=x-m-1;
			re.y=m;
		}
		if(x>=m*2+1&&x<=m*3)
		{
			re.y=m-(x-2*m-1);
			re.x=m;
		}
		if(x>=m*3+1&&x<=m*4)
		{
			re.x=m-(x-3*m-1);
			re.y=0;
		}
		return re;
	}
	bool jud(int _x,int _y)
	{
		int i;
		_x=(_x-1)%N+1;
		_y=(_y-1)%N+1;
		for(i=1;i<=n;i++)
		{
			pt X=ps(_x);
			pt Y=ps(_y);
			pt t(x[i],y[i]);
			if((t-X)*(Y-X)<0)
			{
				return 0;
			}
		}
		return 1;
	}
	ll getNumber(int _m,vector<int>_x,vector<int>_y)
	{
		int i,j,k;
		n=_x.size();
		m=_m;
		N=m*4;
		for(i=1;i<=n;i++)
		{
			x[i]=_x[i-1];
			y[i]=_y[i-1];
		}
		
		j=1;
		for(i=1;i<=N;i++)
		{
			while(jud(i,j))
			{
				j++;
			}
			f[i]=j-1;
		}
		j=1,k=1;
		for(i=1;i<=N;i++)
		{
			s[i]=s[i-1]+min(N,f[i]);
		}
		for(i=1;i<=N;i++)
		{
			
			while(f[j]<i+N&&j<=N)
			{
				j++;
			}
			while(f[k]<j&&k<=N)
			{
				k++;
			}
			if(j>N)
			{
				break;
			}
			//cerr<<i<<' '<<j<<' '<<k<<endl;
			if(k<=f[i])
			{
				ans+=s[f[i]]-s[max(i+1,k)-1]-(ll)(j-1)*(f[i]-(max(i+1,k)-1));
			}
			if(f[i]==j)
			{
				ans--;
			}
			//cerr<<ans<<endl;
		}
		return ans;
	}
};