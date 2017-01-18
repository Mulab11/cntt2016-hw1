#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<iomanip>
#include<queue>
#include<map>
#include<bitset>
#include<stack>
#include<vector>
#include<set>
using namespace std;
#define MAXN 1010
#define MAXM 1010
#define INF 1000000000
#define MOD 1000000007
#define ll long long
#define eps 1e-8
struct MapGuessing
{
	string C;
	string T;
	int n;
	int L,R;
	ll d[MAXN];
	char s[MAXN];
	bool cd[MAXN];
	ll c[MAXN][MAXN];
	int tot;
	ll ans;
	int lim;
	ll cal(int now)
	{
		int i,j;
		ll re=0;
		memset(cd,0,sizeof(cd));
		for(i=0;i<C.size();i++)
		{
			if(C[i]=='>')
			{
				now++;
			}
			else if(C[i]=='<')
			{
				now--;
			}
			else
			{
				s[now]=C[i];
				cd[now]=1;
			}
			bool flag=1;
			ll t=0;
			for(j=1;j<=n;j++)
			{
				if(cd[j])
				{
					if(s[j]!=T[j])
					{
						flag=0;
						break;
					}
					t|=1ll<<(j-1);
				}
			}
			if(flag)
			{
				re=t;
			}
		}
		return re;
	}
	void dfs(int x,ll D,int t)
	{
		if(x==lim)
		{
			int i;
			ll now=1;
			for(i=62;~i;i--)
			{
				if((D>>i)&1)
				{
					now*=2;
				}
			}
			if(t&1)
			{
				ans+=now;
			}
			else
			{
				ans-=now;
			}
			return ;
		}
		dfs(x+1,D&d[x],t+1);
		dfs(x+1,D,t);
	}
	ll countPatterns(string _T,vector<string> CS)
	{
		int i,j,k;
		n=_T.size();
		T="!";
		T+=_T;
		for(i=0;i<CS.size();i++)
		{
			C+=CS[i];
		}
		int _L=0,_R=0;
		for(i=0;i<C.size();i++)
		{
			if(C[i]=='>')
			{
				_R++;
				_L--;
				R=max(_R,R);
			}
			if(C[i]=='<')
			{
				_L++;
				_R--;
				L=max(_L,L);
			}
		}
		for(i=L+1;i<=n-R;i++)
		{
			d[++tot]=cal(i);
		}
		c[0][0]=1;
		for(i=1;i<=36;i++)
		{
			c[i][0]=1;
			for(j=1;j<=i;j++)
			{
				c[i][j]=c[i-1][j]+c[i-1][j-1];
			}
		}
		for(i=1;i<=tot;i++)
		{
			lim=min(tot+1,i+L+R+1);
			for(j=0;j<=lim-i-1;j++)
			{
				for(k=1;k<=tot-lim+1;k++)
				{
					if((j+k+1)&1)
					{
						ans+=c[lim-i-1][j]*c[tot-lim+1][k];
					}
					else
					{
						ans-=c[lim-i-1][j]*c[tot-lim+1][k];
					}
				}
			}
			dfs(i+1,d[i],1);
		}
		return ans;
	}
};