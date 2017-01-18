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
#define MAXM 1010
#define INF 1000000000
#define MOD 1000000007
#define eps 1e-8
#define ll long long
struct vec
{
	ll to;
	ll fro;
	ll v;
	ll c;
};
vec mp[MAXM];
ll tai[MAXN],cnt;
ll n,m1,m2;
ll s1[MAXN],t1[MAXN],l1[MAXN];
ll s2[MAXN],t2[MAXN],l2[MAXN];
ll X;
ll dis[MAXN],ct[MAXN];
ll q[MAXN],hd,tl;
bool iq[MAXN];
ll c[MAXN];
ll flag;
ll C;
inline void be(ll x,ll y,ll z,ll zz)
{
	mp[++cnt].to=y;
	mp[cnt].fro=tai[x];
	tai[x]=cnt;
	mp[cnt].v=z;
	mp[cnt].c=zz;
}
void build()
{//差分约束建图 
	ll i;
	memset(tai,0,sizeof(tai));
	cnt=0;
	for(i=1;i<=m1;i++)
	{
		if(s1[i]<t1[i])
		{
			be(t1[i],s1[i],-l1[i],0);
		}
		else
		{
			be(t1[i],s1[i],X-l1[i],1);
		}
	}
	for(i=1;i<=m2;i++)
	{
		if(s2[i]<t2[i])
		{
			be(s2[i],t2[i],l2[i],0);
		}
		else
		{
			be(s2[i],t2[i],l2[i]-X,-1);
		}
	}
	be(n,0,-X,-1);
	be(0,n,X,1);
	for(i=1;i<=n;i++)
	{
		be(i,i-1,-1,0);
	}
}
void spfa()
{//判断是否可行 
	ll i,x,y;
	hd=0;
	tl=0;
	memset(dis,0,sizeof(dis));
	memset(c,0,sizeof(c));
	memset(ct,0,sizeof(ct));
	for(i=0;i<=n;i++)
	{
		iq[q[tl++]=i]=1;
		tl%=MAXN;
	}
	while(hd!=tl)
	{
		iq[x=q[hd++]]=0;
		hd%=MAXN;
		if(ct[x]++>n)
		{
			flag=1;
			C=c[x];
			return ;
		}
		for(i=tai[x];i;i=mp[i].fro)
		{
			y=mp[i].to;
			if(dis[y]>dis[x]+mp[i].v)
			{
				dis[y]=dis[x]+mp[i].v;
				c[y]=c[x]+mp[i].c;
				if(!iq[y])
				{
					iq[q[tl++]=y]=1;
					tl%=MAXN;
				}
			}
		}
	}
	flag=0;
	C=c[x];
}
struct YamanoteLine
{
	ll howMany(int _n,vector<int>_s1,vector<int>_t1,vector<int>_l1,vector<int>_s2,vector<int>_t2,vector<int>_l2)
	{
		ll i,j,k;
		m1=_s1.size();
		m2=_s2.size();
		n=_n;
		for(i=1;i<=m1;i++)
		{
			s1[i]=_s1[i-1];
			t1[i]=_t1[i-1];
			l1[i]=_l1[i-1];
		}
		for(i=1;i<=m2;i++)
		{
			s2[i]=_s2[i-1];
			t2[i]=_t2[i-1];
			l2[i]=_l2[i-1];
		}
		//*
		ll l=0,r=10000000000000ll;
		ll L,R;
		while(l<=r)
		{//二分下界 
			ll mid=l+r>>1;
			X=mid;
			build();
			spfa();
			if(flag&&!C)
			{
				return 0;
			}
			if(!flag||(flag&&C<0))
			{
				r=mid-1;
				L=mid;
			}
			else
			{
				l=mid+1;
			}
		}
		
		l=0,r=10000000000000ll;
		while(l<=r)
		{//二分上界 
			ll mid=l+r>>1;
			X=mid;
			build();
			spfa();
			if(flag&&!C)
			{
				return 0;
			}
			if(!flag||(flag&&C>0))
			{
				l=mid+1;
				R=mid;
			}
			else
			{
				r=mid-1;
			}
		}
		if(L>R)
		{
			return 0;
		}
		if(R-L+1>5000000000000ll)
		{
			return -1;
		}
		return R-L+1;
		//*/
	}
};

/*

*/