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
#define MAXN 5010
#define INF 1000000000
#define MOD 1000000007
#define eps 1e-8
#define ll long long
struct SkiResorts
{
	struct data
	{
		int x;
		int y;
		int z;
		int v;
		data()
		{
			
		}
		data(int _x,int _y,int _z,int _v)
		{
			x=_x;
			y=_y;
			z=_z;
			v=_v;
		}
	};
	int n,mx;
	int tls[MAXN],tln;
	int g[MAXN];
	int h[MAXN];
	data q[MAXN];
	int hd,tl;
	bool iq[MAXN];
	ll dis[MAXN];
	vector<string>mp;
	int pt(int x,int y,int z)
	{
		return z*mx*n+(x-1)*mx+y;
	}
	void spfa()
	{
		int i,j;
		data x,y;
		while(hd!=tl)
		{
			iq[(x=q[hd++]).v]=0;
			hd%=MAXN;
			if(x.z==0)
			{
				data y(x.x,x.y,1,pt(x.x,x.y,1));
				int v=abs(h[x.x]-g[x.y]);
				if(dis[y.v]>dis[x.v]+v)
				{
					dis[y.v]=dis[x.v]+v;
					if(!iq[y.v])
					{
						iq[(q[tl++]=y).v]=1;
						tl%=MAXN;
					}
				}
			}
			else
			{
				for(i=1;i<=n;i++)
				{
					if(mp[x.x-1][i-1]=='Y')
					{
						for(j=1;j<=x.y;j++)
						{
							data y(i,j,0,pt(i,j,0));
							int v=0;
							if(dis[y.v]>dis[x.v]+v)
							{
								dis[y.v]=dis[x.v]+v;
								if(!iq[y.v])
								{
									iq[(q[tl++]=y).v]=1;
									tl%=MAXN;
								}
							}
						}
					}
				}
			}
		}
	}
	
	ll minCost(vector<string>_mp,vector<int>_h)
	{
		mp=_mp;
		int i,j,k,l;
		n=_h.size();
		for(i=0;i<n;i++)
		{
			tls[++tln]=_h[i]; 
			h[i+1]=_h[i];
		}
		
		sort(tls+1,tls+tln+1);
		for(i=1;i<=tln;i++)
		{
			if(tls[i]!=tls[i-1]||i==1)
			{
				mx++;
				g[mx]=tls[i];
			}
		}
		/*
		for(i=1;i<=n;i++)
		{
			for(j=1;j<=mx;j++)
			{
				be(pt(i,j,0),pt(i,j,1),abs(h[i]-g[j]));
			}
		}
		for(i=1;i<=n;i++)
		{
			for(j=1;j<=n;j++)
			{
				if(mp[i-1][j-1]=='Y')
				{
					for(k=1;k<=mx;k++)
					{
						for(l=1;l<=k;l++)
						{
							be(pt(i,k,1),pt(j,l,0),0);
						}
					}
				}
			}
		}
		//*/
		memset(dis,0x3f,sizeof(dis));
		for(i=1;i<=mx;i++)
		{
			iq[(q[tl++]=data(1,i,0,pt(1,i,0))).v]=1;
			dis[pt(1,i,0)]=0;
		}
		spfa();
		ll ans=dis[0];
		for(i=1;i<=mx;i++)
		{
			ans=min(ans,dis[pt(n,i,1)]);
		}
		return ans==dis[0]?-1:ans;
	}
};