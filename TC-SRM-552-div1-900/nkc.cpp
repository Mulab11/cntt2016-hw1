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
#define MAXN 1000010
#define MAXM 1010
#define INF 1000000000
#define MOD 1000000007
#define eps 1e-8
#define ll long long
ll mx;
bool np[MAXN];
ll tot;
ll p[MAXN];
void su()
{//线性筛 
	ll i,j;
	for(i=2;i<=mx;i++)
	{
		if(!np[i])
		{
			p[++tot]=i;
		}
		for(j=1;j<=tot&&p[j]*i<=mx;j++)
		{
			np[i*p[j]]=1;
			if(!(i%p[j]))
			{
				break;
			}
		}
	}
}
ll find(ll x)
{//二分出解 
	ll l=1,r=tot;
	ll re=0;
	while(l<=r)
	{
		ll mid=l+r>>1;
		if(p[mid]<=x)
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
ll dp(ll x,ll n)
{//搜索 
	if(x>tot||p[x]>n)
	{//递归出口 
		return 1;
	}
	if(p[x]*p[x+1]>n)
	{
		return find(n)-x+2;
	}
	ll now;
	ll re=dp(x+1,n);
	for(now=p[x];now<=n;now*=p[x]*p[x])
	{//枚举指数 
		re+=dp(x+1,n/now);
	}
	return re;
}
struct HolyNumbers
{
	ll count(ll n,int _mx)
	{
		mx=_mx;
		su();
		return dp(1,n);
	}
};

/*

*/