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
	int to;
	int fro;
};
struct pt
{
	double x;
	double y;
};
struct itv
{
	double l;
	double r;
	int bel;
	itv()
	{
		
	}
	itv(double _l,double _r,int _bel)
	{
		l=_l;
		r=_r;
		bel=_bel;
	}
};
vec mp[MAXN*MAXN];
int tai[MAXN*MAXN],cnt;
pt a[MAXN];
pt s,t;
int n;
double r[MAXN];
itv tvs[MAXN*MAXN];
bool vis[MAXN*MAXN];
int q[MAXN*MAXN],hd,tl;
int tot;
inline void be(int x,int y)
{
	mp[++cnt].to=y;
	mp[cnt].fro=tai[x];
	tai[x]=cnt;
}
inline void bde(int x,int y)
{
	be(x,y);
	be(y,x);
}
double dis(pt x,pt y)
{
	return sqrt((x.x-y.x)*(x.x-y.x)+(x.y-y.y)*(x.y-y.y));
}
ll DIS(pt x,pt y)
{
	ll t1=(ll)(x.x-y.x);
	ll t2=(ll)(x.y-y.y);
	return t1*t1+t2*t2;
}
struct CandyOnDisk
{
	string ableToAchieve(vector<int>_x,vector<int>_y,vector<int>_r,int _sx,int _sy,int _ex,int _ey)
	{
		int i,j,x,y;
		n=_x.size();
		for(i=1;i<=n;i++)
		{
			a[i].x=_x[i-1];
		}
		for(i=1;i<=n;i++)
		{
			a[i].y=_y[i-1];
		}
		for(i=1;i<=n;i++)
		{
			r[i]=_r[i-1];
		}
		s.x=_sx;
		s.y=_sy;
		t.x=_ex;
		t.y=_ey;
		if(s.x==t.x&&s.y==t.y)
		{//特判开始就相等 
			return "YES";
		}
		for(i=1;i<=n;i++)
		{
			if(DIS(a[i],s)==DIS(a[i],t)&&dis(a[i],s)<=r[i])
			{//特判一个轮子转到，用ll防止卡精 
				return "YES";
			}
		}
		for(i=1;i<=n;i++)
		{
			for(j=i+1;j<=n;j++)
			{
				if(!(_x[i-1]==_x[j-1]&&_y[i-1]==_y[j-1]))
				{
					double d=dis(a[i],a[j]);
					double l1,l2,r1,r2;
					if(d<=r[i]+r[j])
					{//算相交的区间 
						if(d<=r[j])
						{
							l1=0;
						}
						else
						{
							l1=d-r[j];
						}
						if(d+r[j]>=r[i])
						{
							r1=r[i];
						}
						else
						{
							r1=d+r[j];
						}
						tvs[++tot]=itv(l1,r1,i);
						if(d<=r[i])
						{
							l2=0;
						}
						else
						{
							l2=d-r[i];
						}
						if(d+r[i]>=r[j])
						{
							r2=r[j];
						}
						else
						{
							r2=d+r[i];
						}
						tvs[++tot]=itv(l2,r2,j);
						bde(tot,tot-1);
					}
				}
			}
		}
		for(i=1;i<=tot;i++)
		{
			x=tvs[i].bel;
			if(dis(s,a[x])>=tvs[i].l&&dis(s,a[x])<=tvs[i].r)
			{
				vis[q[tl++]=i]=1;
			}
		}
		while(hd!=tl)
		{//bfs 
			x=q[hd++];
			for(i=1;i<=tot;i++)
			{
				if(!vis[i]&&tvs[i].bel==tvs[x].bel&&tvs[i].l<=tvs[x].r&&tvs[x].l<=tvs[i].r)
				{
					vis[q[tl++]=i]=1;
				}
			}
			for(i=tai[x];i;i=mp[i].fro)
			{
				y=mp[i].to;
				if(!vis[y])
				{
					vis[q[tl++]=y]=1;
				}
			}
		}
		for(i=1;i<=tot;i++)
		{
			x=tvs[i].bel;
			if(vis[i]&&dis(t,a[x])>=tvs[i].l&&dis(t,a[x])<=tvs[i].r)
			{
				return "YES";
			}
		}
		return "NO";
	}
};