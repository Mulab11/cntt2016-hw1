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
ll a[MAXN];
int wt;
ll st[MAXN];
int tp;
ll pop()
{
	ll t=st[tp];
	st[tp]=0;
	tp=max(tp-1,0);
	return t;
}
void push(ll x)
{
	st[++tp]=x;
}
struct Suminator
{
	int findMissing(vector<int>_a,int _wt)
	{
		int i;
		n=_a.size();
		for(i=1;i<=n;i++)
		{
			a[i]=_a[i-1];
		}
		wt=_wt;
		for(i=1;i<=n;i++)
		{//如果是0 
			if(a[i]==0||a[i]==-1)
			{
				push(pop()+pop());
			}
			else
			{
				push(a[i]);
			}
		}
		if(pop()==wt)
		{
			return 0;
		}
		while(tp)
		{
			st[tp--]=0;
		}
		for(i=1;i<=n;i++)
		{//如果非0 
			if(a[i]==0)
			{
				push(pop()+pop());
			}
			else if(a[i]==-1)
			{
				push(1000000000000000ll);
			}
			else
			{
				push(a[i]);
			}
		}
		ll now=pop();
		if(now<1000000000000000ll)
		{//答案与不确定的数无关 
			if(now==wt)
			{
				return 1;
			}
			else
			{
				return -1;
			}
		}
		else
		{
			ll re=wt-(now-1000000000000000ll);//答案与不确定的数有关 
			if(re>0)
			{
				return re;
			}
			return -1;
		}
	}
};

/*

*/