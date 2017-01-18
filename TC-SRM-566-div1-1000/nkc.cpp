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
#define MAXN 310
#define MAXM 1010
#define INF 1000000000
#define MOD 100007
#define eps 1e-8
#define ll long long
const double pi=acos(-1);
struct FencingPenguins
{
	struct pt
	{
		double x;
		double y;
		char c;
		pt()
		{
			
		}
		pt(double _x,double _y)
		{
			x=_x;
			y=_y;
		}
		friend pt operator -(pt x,pt y)
		{
			return pt(x.x-y.x,x.y-y.y);
		}
		friend double operator *(pt x,pt y)
		{
			return x.x*y.y-x.y*y.x;
		}
		friend bool operator <(pt x,pt y)
		{
			return x.c<y.c;
		}
	};
	int f[MAXN][MAXN],g[MAXN][MAXN],h[MAXN][MAXN][2];
	bool vf[MAXN][MAXN],vg[MAXN][MAXN],vh[MAXN][MAXN][2];
	bool abl[MAXN][MAXN];
	int n,r,N;
	string c;
	vector<int>x,y;
	pt p[MAXN],P[MAXN];
	ll ps[MAXN][MAXN];
	ll count(int x,int y,int z)
	{
		return ps[x][y]&ps[y][z]&ps[z][x];
	}
	int H(int l,int r,bool flag)
	{
		if(l==r)
		{
			return flag;
		}
		if(vh[l][r][flag])
		{
			return h[l][r][flag];
		}
		vh[l][r][flag]=1;
		int i;
		int re=0;
		for(i=l+1;i<=r;i++)
		{
			if(!abl[l][i])
			{
				continue ;
			}
			if(ps[i][l])
			{
				if(i>=l+4&&!(ps[l+1][i-1]&ps[i][l]))
				{
					(re+=(ll)F(l+1,i-1)*H(i,r,flag||count(l,i,r))%MOD)%=MOD;
				}
			}
			else
			{ 
				(re+=H(i,r,flag||count(l,i,r)))%=MOD;
			}
		}
		h[l][r][flag]=re;
		return re;
	}
	int G(int l,int r)
	{
		if(vg[l][r])
		{
			return g[l][r];
		}
		vg[l][r]=1;
		int i;
		int re=0;
		for(i=l+2;i<=r;i++)
		{
			if(!abl[i][l])
			{
				continue ;
			}
			if(!(ps[l][i]&ps[r][l]))
			{
				(re+=H(l,i,0))%=MOD;
			}
			else if(i+2<r&&!(ps[l][i]&ps[r][l]&ps[i+1][r]))
			{
				(re+=(ll)H(l,i,0)*F(i+1,r)%MOD)%=MOD;
			}
		}
		g[l][r]=re;
		return re;
	}
	int F(int l,int r)
	{
		if(vf[l][r])
		{
			return f[l][r];
		}
		vf[l][r]=1;
		int i;
		int re=0;
		for(i=l;i<r;i++)
		{
			if(!(ps[i][r]&ps[r][l]))
			{
				(re+=G(i,r))%=MOD;
			}
		}
		f[l][r]=re;
		return re;
	}
	void pre()
	{
		int i,j,k,l;
		double o=pi*2/n;
		for(i=1;i<=n;i++)
		{
			P[i].x=r*cos((i-1)*o);
			P[i].y=r*sin((i-1)*o);
		}
		sort(p+1,p+N+1);
		for(i=1;i<=n;i++)
		{
			abl[i][i]=1;
			for(j=i+1;j<=n;j++)
			{
				for(k=1;k<=N;k++)
				{
					if((P[j]-P[i])*(p[k]-P[i])>0)
					{
						ps[i][j]|=1ll<<k;
					}
					else
					{
						ps[j][i]|=1ll<<k;
					}
				}
				abl[i][j]=abl[j][i]=1;
				for(k=1;k<=N;k++)
				{
					for(l=k+1;p[l].c==p[k].c;l++)
					{
						if(((ps[i][j]>>l)&1)!=((ps[i][j]>>k)&1))
						{
							abl[i][j]=abl[j][i]=0;
							break;
						}
					}
					if(!abl[i][j])
					{
						break;
					}
					k=l-1;
				}
			}
		}
	}
	int countWays(int _n,int _r,vector<int> _x,vector<int> _y,string _c)
	{
		int i;
		n=_n;
		r=_r;
		x=_x;
		y=_y;
		c=_c;
		N=_x.size();
		for(i=1;i<=N;i++)
		{
			p[i].x=_x[i-1];
			p[i].y=_y[i-1];
			p[i].c=_c[i-1];
		}
		pre();
		for(i=1;i<n;i++)
		{
			if(ps[i+1][i])
			{
				return 0;
			}
		}
		if(ps[1][n])
		{
			return 0;
		}
		return F(1,n);
	}
};