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
#define MAXM 2510
#define MAXD (1<<8)
#define MAXPD (1<<16)+10
#define INF 1000000000
#define MOD 1000000007
#define eps 1e-8
#define ll long long
struct vec
{
	int to;
	int fro;
};
vec mp[MAXN];
int tai[MAXN],cnt;
int n;
int tot;
int rt;
int son[MAXM][26];
bool danger[MAXM];
int q;
int p1[MAXN],p2[MAXN];
ll f[MAXN][MAXD];
ll t0[MAXD],t1[MAXD],tt1[MAXD],tt0[MAXD];
int Q;
int d[MAXN];
int d1[MAXPD],d2[MAXPD],d3[MAXPD],tr[MAXPD],nn[MAXPD];
bool used[MAXD][MAXN];
int ds;
int siz[MAXN];
ll fac[MAXN],ine[MAXN];
int usn[MAXD];
vector<int>TDS[MAXN];
vector<int> *tds=TDS+1;
inline void be(int x,int y)
{
	mp[++cnt].to=y;
	mp[cnt].fro=tai[x];
	tai[x]=cnt;
}
void ins(string x)
{
	int i;
	int p=rt;
	for(i=0;i<x.size();i++)
	{
		if(!son[p][x[i]-'a'])
		{
			son[p][x[i]-'a']=++tot;
		}
		p=son[p][x[i]-'a'];
	}
	danger[p]=1;
}
void build(int x,int now)
{
	int i;
	if(danger[x])
	{
		be(now,++tot);
		now=tot;
	}
	for(i=0;i<26;i++)
	{
		if(son[x][i])
		{
			build(son[x][i],now);
		}
	}
}
void dfs(int x)
{
	int i;
	if(x==q)
	{
		ds++;
		d1[ds]=d2[ds]=d3[ds]=nn[ds]=0;
		for(i=0;i<q;i++)
		{
			if(d[i])
			{
				d1[ds]|=1<<i;
				if(d[i]==2)
				{
					d2[ds]|=1<<i;
				}
				if(d[i]==3)
				{
					d3[ds]|=1<<i;
				}
			}
		}
		for(i=0;i<n;i++)
		{
			if(used[d2[ds]][i]&&used[d3[ds]][i])
			{
				ds--;
				return ;
			}
		}
		int trm=-1;
		for(i=0;i<q;i++)
		{
			if((d1[ds]&(1<<i))&&!(d2[ds]&(1<<i))&&!(d3[ds]&(1<<i)))
			{
				if(trm!=-1&&trm!=p1[i])
				{
					ds--;
					return ;
				}
				if(used[d2[ds]][p2[i]])
				{
					ds--;
					return ;
				}
				if(!used[d3[ds]][p2[i]])
				{
					nn[ds]++;
				}
				trm=p1[i];
			}
		}
		if(trm!=-1&&used[d3[ds]][trm])
		{
			ds--;
			return ;
		}
		for(i=0;i<q;i++)
		{
			if(d2[ds]&(1<<i))
			{
				if(p2[i]==trm)
				{
					ds--;
					return ;
				}
			}
		}
		tr[ds]=trm;
		tds[trm].push_back(ds);
		return ;
	}
	for(i=0;i<4;i++)
	{
		d[x]=i;
		dfs(x+1);
	}
}
void dp(int x)
{
	int i,j,k,I,J,l,y;
	siz[x]=1;
	for(i=tai[x];i;i=mp[i].fro)
	{
		y=mp[i].to;
		dp(y);
		siz[x]+=siz[y];
	}
	memset(tt0,0,sizeof(tt0));
	tt0[0]=1;
	for(i=tai[x];i;i=mp[i].fro)
	{
		y=mp[i].to;
		memset(t0,0,sizeof(t0));
		for(J=0;J<tds[-1].size();J++)
		{
			j=tds[-1][J];
			ll T0=tt0[d2[j]]*f[y][d3[j]]%MOD;
			if(siz[y]-usn[d3[j]]-nn[j]>=0)
			{
				(t0[d1[j]]+=T0*fac[siz[y]-usn[d3[j]]]%MOD*ine[siz[y]-usn[d3[j]]-nn[j]]%MOD)%=MOD;
			}
		}
		memcpy(tt0,t0,sizeof(t0));
	}
	for(i=0;i<Q;i++)
	{
		(f[x][i]+=tt0[i])%=MOD;
	}
	if(x!=1)
	{
		for(I=0;I<n;I++)
		{
			if(tds[I].size())
			{
				memset(tt0,0,sizeof(tt0));
				memset(tt1,0,sizeof(tt1));
				tt0[0]=1;
				for(i=tai[x];i;i=mp[i].fro)
				{
					y=mp[i].to;
					memset(t0,0,sizeof(t0));
					memset(t1,0,sizeof(t1));
					for(J=0;J<tds[I].size();J++)
					{
						j=tds[I][J];
						ll T1=(tt0[d2[j]]+tt1[d2[j]]%MOD)*f[y][d3[j]]%MOD;
						if(siz[y]-usn[d3[j]]-nn[j]>=0)
						{
							(t1[d1[j]]+=T1*fac[siz[y]-usn[d3[j]]]%MOD*ine[siz[y]-usn[d3[j]]-nn[j]]%MOD)%=MOD;
						}
					}
					for(J=0;J<tds[-1].size();J++)
					{
						j=tds[-1][J];
						if(used[d3[j]][I])
						{
							continue ;
						}
						ll T0=tt0[d2[j]]*f[y][d3[j]]%MOD;
						ll T1=tt1[d2[j]]*f[y][d3[j]]%MOD;
						if(siz[y]-usn[d3[j]]-nn[j]>=0)
						{
							(t0[d1[j]]+=T0*fac[siz[y]-usn[d3[j]]]%MOD*ine[siz[y]-usn[d3[j]]-nn[j]]%MOD)%=MOD;
							(t1[d1[j]]+=T1*fac[siz[y]-usn[d3[j]]]%MOD*ine[siz[y]-usn[d3[j]]-nn[j]]%MOD)%=MOD;
						}
					}
					memcpy(tt0,t0,sizeof(t0));
					memcpy(tt1,t1,sizeof(t1));
				}
				for(i=0;i<Q;i++)
				{
					(f[x][i]+=tt1[i])%=MOD;
				}
			}
		}
	}
	/*
	cerr<<x<<"!"<<siz[x]<<' '<<endl;
	for(i=0;i<Q;i++)
	{
		cerr<<bitset<2>(i)<<' '<<f[x][i]<<endl;
	}
	//*/
}

struct SimilarNames
{
	int count(vector<string>names,vector<int>info1,vector<int>info2)
	{
		int i,j,k,l;
		n=names.size();
		rt=tot=1;
		for(i=0;i<n;i++)
		{
			ins(names[i]);
		}
		q=info1.size();
		for(i=0;i<q;i++)
		{
			p1[i]=info1[i];
			p2[i]=info2[i];
		}
		tot=0;
		build(rt,++tot);
		tot--;
		Q=(1<<q);
		for(i=0;i<Q;i++)
		{
			for(j=0;j<q;j++)
			{
				if(i&(1<<j))
				{
					used[i][p1[j]]=1;
					used[i][p2[j]]=1;
				}
			}
			for(j=0;j<n;j++)
			{
				usn[i]+=used[i][j];
			}
		}
		fac[0]=ine[0]=ine[1]=1;
		for(i=1;i<=n;i++)
		{
			fac[i]=fac[i-1]*i%MOD;
		}
		for(i=2;i<=n;i++)
		{
			ine[i]=(MOD-MOD/i)*ine[MOD%i]%MOD;
		}
		for(i=2;i<=n;i++)
		{
			(ine[i]*=ine[i-1])%=MOD;
		}
		dfs(0);
		dp(1);
		return f[1][Q-1]*fac[tot-usn[Q-1]]%MOD;
	}
};