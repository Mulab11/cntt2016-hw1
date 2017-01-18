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
#define MOD 1000000009
#define eps 1e-8
#define ll long long
ll w,sx,sy;
string a[11];
int n,m;
ll ans;
ll l;
ll mi(ll x,ll y)
{
	ll re=1;
	while(y)
	{
		if(y&1)
		{
			(re*=x)%=MOD;
		}
		(x*=x)%=MOD;
		y>>=1;
	}
	return re;
}
ll ni(ll x)
{
	return mi(x,MOD-2);
}
ll pt(ll x,ll y)
{
	return (x+sx)*w+y+sy;
}
map<int,bool>vis;
map<int,bool>ced;
map<int,char>gen;
void cal(ll x)
{
	if(x-l>=0)
	{
		(ans+=MOD-mi(26,x-l))%=MOD;
	}
	int i,j;
	ll rem=x;
	gen.clear();
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			if(!gen[pt(i,j)%x])
			{
				gen[pt(i,j)%x]=a[i][j];
				rem--;
			}
			else if(gen[pt(i,j)%x]!=a[i][j])
			{
				return ;
			}
		}
	}
	(ans+=mi(26,rem))%=MOD;
}
void calc(ll c)
{
	ll y;
	ced[c]=1;
	for(y=1;y*y<=c;y++)
	{
		if(!(c%y))
		{
			if(!vis[y])
			{
				vis[y]=1;
				cal(y);
			}
			if(y*y!=c)
			{
				if(c/y<=w&&!vis[c/y])
				{
					vis[c/y]=1;
					cal(c/y);
				}
			}
		}
	}
	
}
struct CharacterBoard
{
	int countGenerators(vector<string>_a,int _W,int _sx,int _sy)
	{
		ll i,j,I,J;
		w=_W;
		sx=_sx;
		sy=_sy;
		n=_a.size();
		m=_a[0].size();
		for(i=0;i<n;i++)
		{
			a[i]=_a[i];
		}
		l=n*m;
		if(l<=w)
		{
			ans=(mi(26,w-l+1)-1+MOD)%MOD*ni(25)%MOD;
		}
		for(i=0;i<n;i++)
		{
			for(j=0;j<m;j++)
			{
				for(I=0;I<n;I++)
				{
					for(J=0;J<m;J++)
					{
						ll c=pt(i,j)-pt(I,J);
						if(c>=1&&!ced[c])
						{
							calc(c);
						}
					}
				}
			}
		}
		if(!vis[1])
		{
			cal(1);
		}
		return ans;
	}
};
/*

*/