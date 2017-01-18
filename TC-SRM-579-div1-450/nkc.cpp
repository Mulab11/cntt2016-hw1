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
#define MAXN 60
#define MAXM 66000
#define INF 1000000000
#define MOD 1000000007
#define eps 1e-8
#define ll long long
struct TravellingPurchasingMan
{
	struct vec
	{
		int to;
		int fro;
		int v;
	};
	vec mp[MAXN*2];
	int tai[MAXN],cnt;
	int st[MAXN],ed[MAXN],dr[MAXN];
	int dis[MAXN][MAXM];
	int n,m;
	int q[MAXN*MAXM],qd[MAXN*MAXM],hd,tl;
	bool iq[MAXN][MAXM];
	inline void be(int x,int y,int z)
	{
		mp[++cnt].to=y;
		mp[cnt].fro=tai[x];
		tai[x]=cnt;
		mp[cnt].v=z;
	}
	inline void bde(int x,int y,int z)
	{
		be(x,y,z);
		be(y,x,z);
	}
	void get(int &x,int &i,string &s)
	{
		for(;s[i]!=' ';i++)
		{
			x*=10;
			x+=s[i]-'0';
		}
		i++;
	}
	void get(int &x,int &y,int &z,string &s)
	{
		int i;
		s+=" ";
		i=x=y=z=0;
		get(x,i,s);
		get(y,i,s);
		get(z,i,s);
	}
	void spfa()
	{
		int i,x,xd,y;
		memset(dis,0x3f,sizeof(dis));
		dis[n-1][0]=0;
		q[tl]=n-1;
		qd[tl++]=0;
		iq[n-1][0]=1;
		while(hd!=tl)
		{
			x=q[hd];
			xd=qd[hd++];
			iq[x][xd]=0;
			hd%=MAXN*MAXM;
			if(x<m)
			{
				int stm=max(dis[x][xd],st[x]);
				if(stm<=ed[x])
				{
					if(dis[x][xd|(1<<x)]>stm+dr[x])
					{
						dis[x][xd|(1<<x)]=stm+dr[x];
						if(!iq[x][xd|(1<<x)])
						{
							q[tl]=x;
							qd[tl++]=xd|(1<<x);
							iq[x][xd|(1<<x)]=1;
							tl%=MAXN*MAXM;
						}
					}
				}
			}
			for(i=tai[x];i;i=mp[i].fro)
			{
				y=mp[i].to;
				if(dis[y][xd]>dis[x][xd]+mp[i].v)
				{
					dis[y][xd]=dis[x][xd]+mp[i].v;
					if(!iq[y][xd])
					{
						q[tl]=y;
						qd[tl++]=xd;
						iq[y][xd]=1;
						tl%=MAXN*MAXM;
					}
				}
			}
		}
	}
	int maxStores(int _n,vector<string>_tm,vector<string>_mp)
	{
		int i,x,y,z;
		n=_n;
		m=_tm.size();
		for(i=0;i<_tm.size();i++)
		{
			get(st[i],ed[i],dr[i],_tm[i]);
		}
		for(i=0;i<_mp.size();i++)
		{
			get(x,y,z,_mp[i]);
			bde(x,y,z);
		}
		spfa();
		int M=1<<m;
		int re=0;
		for(i=0;i<m;i++)
		{
			for(x=0;x<M;x++)
			{
				if(dis[i][x]<INF)
				{
					int t=0;
					for(y=0;y<m;y++)
					{
						t+=(x>>y)&1;
					}
					re=max(re,t);
				}
			}
		}
		return re;
	}
};