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
ll n;
ll a,b,c;
ll t;
bool OK(ll x)
{//判断是否可行 
	if(a-t*x+b-t*x+c-t*x>=x)
	{
		return 1;
	}
	return 0;
}
struct FoxPaintingBalls
{
	ll theMax(ll _a,ll _b,ll _c,int _n)
	{
		n=_n;
		a=_a;
		b=_b;
		c=_c;
		if(n==1)
		{
			return a+b+c;//特判n==1 
		}
		if(n%3==1)
		{
			t=(n*(n+1)/2-1)/3;
		}
		else
		{
			t=n*(n+1)/6;
		}
		ll l=0,r=min(a/t,min(b/t,c/t));
		if(n%3!=1)
		{//n%3!=1直接出解 
			return r;
		}
		ll re;
		while(l<=r)
		{//二分 
			ll mid=l+r>>1;
			if(OK(mid))
			{
				re=mid;
				l=mid+1;
			}
			else
			{
				r=mid-1;
			}
		}
		return re;
	}
};