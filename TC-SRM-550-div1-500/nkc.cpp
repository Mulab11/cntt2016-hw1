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
ll r;
vector<string>re;
ll mi[51];
char cal(ll x,ll y)
{
	if((y+x)&1)
	{
		return '.';
	}
	ll t=(y+x)/2+1;
	if(r<t)
	{
		return '.';
	}
	if(t==1)
	{
		return 'A';
	}
	if(t==2)
	{
		if(y==0||y==1)
		{
			return 'B';
		}
		else
		{
			return '.';
		}
	}
	int i,lst;
	for(i=1;;i++)
	{
		if(mi[i]<t)
		{
			lst=i;
		}
		else
		{
			break;
		}
	}
	if(x>=mi[lst]&&y>=mi[lst])
	{
		return cal(x-mi[lst],y-mi[lst]);
	}
	else if(x>=mi[lst+1])
	{
		return cal(x-mi[lst+1],y);
	}
	else
	{
		return '.';
	}
}
struct CheckerExpansion
{
	vector<string>resultAfter(ll _r,ll sx,ll sy,int w,int h)
	{
		ll i,j;
		r=_r;
		mi[0]=1;
		for(i=1;i<=50;i++)
		{
			mi[i]=mi[i-1]<<1;
		}
		for(i=0;i<h;i++)
		{
			string t="";
			for(j=0;j<w;j++)
			{
				t+=cal(sx+j,sy+h-i-1);
			}
			re.push_back(t);
		}
		return re;
	}
};