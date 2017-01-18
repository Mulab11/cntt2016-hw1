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
int dx[5]=
{0,0,0,1,-1};
int dy[5]=
{0,-1,1,0,0};
int ans;
struct Tunnels
{
	int n,m;
	char mp[MAXN][MAXN];
	bool vis[MAXN][MAXN];
	bool chk[MAXN][MAXN];
	bool visu,visl,visr;
	int mxl,mnl,mxr,mnr;
	bool stu[MAXN];
	bool cul[MAXN],cur[MAXN],cdl[MAXN],cdr[MAXN],ZMiG[MAXN];
	int f[MAXN][MAXN][MAXN];
	void dfs(int x,int y)
	{
		int i;
		vis[x][y]=1;
		if(x==1)
		{
			visu=1;
		}
		if(y==1)
		{
			visl=1;
			mxl=max(mxl,x);
			mnl=min(mnl,x);
		}
		if(y==m)
		{
			visr=1;
			mxr=max(mxr,x);
			mnr=min(mnr,x);
		}
		for(i=1;i<=4;i++)
		{
			int xx=x+dx[i];
			int yy=y+dy[i];
			if(!vis[xx][yy]&&mp[xx][yy]=='X')
			{
				dfs(xx,yy);
			}
		}
	}
	void dfs2(int x,int y)
	{
		int i;
		chk[x][y]=1;
		int d=0;
		for(i=1;i<=4;i++)
		{
			d+=mp[x+dx[i]][y+dy[i]]=='X';
		}
		if(y==1)
		{
			if(d<2)
			{
				if(mxl==mxr&&mxl==mnl&&mxr==mnr)
				{
					ZMiG[x]=1;
				}
				else if(!visu)
				{
					if(visr)
					{
						if(mnr<x)
						{
							cdl[x]=1;
						}
						if(mxr>x)
						{
							cul[x]=1;
						}
					}
					else
					{
						if(x==mnl)
						{
							cul[x]=1;
						}
						if(x==mxl&&mnl<mxl-1)
						{
							cdl[x]=1;
						}
					}
				}
				else
				{
					if(x==mxl&&(!visr||(visr&&mxr<=x)))
					{
						cdl[x]=1;
					}
				}
			}
		}
		if(y==m)
		{
			if(d<2)
			{
				if(mxl==mxr&&mxl==mnl&&mxr==mnr)
				{
					ZMiG[x]=1;
				}
				else if(!visu)
				{
					if(visl)
					{
						if(mnl<x)
						{
							cdr[x]=1;
						}
						if(mxl>x)
						{
							cur[x]=1;
						}
					}
					else
					{
						if(x==mnr)
						{
							cur[x]=1;
						}
						if(x==mxr&&mnr<mxr-1)
						{
							cdr[x]=1;
						}
					}
				}
				else
				{
					if(x==mxr&&(!visl||(visl&&mxl<=x)))
					{
						cdr[x]=1;
					}
				}
			}
		}
		for(i=1;i<=4;i++)
		{
			int xx=x+dx[i];
			int yy=y+dy[i];
			if(!chk[xx][yy]&&mp[xx][yy]=='X')
			{
				dfs2(xx,yy);
			}
		}
	}
	int minimumTunnels(vector<string> _mp)
	{
		int i,j,k,dl,dr;
		n=_mp.size();
		m=_mp[0].size();
		for(i=1;i<=n;i++)
		{
			for(j=1;j<=m;j++)
			{
				mp[i][j]=_mp[i-1][j-1];
			}
		}
		for(i=1;i<=n;i++)
		{
			for(j=1;j<=m;j++)
			{
				if(!vis[i][j]&&mp[i][j]=='X')
				{
					visl=visr=visu=0;
					mxl=mxr=0;
					mnl=mnr=INF;
					dfs(i,j);
					dfs2(i,j);
					ans++;
				}
			}
		}
		if(m==1)
		{
			return bool(ans);
		}
		memset(f,0xef,sizeof(f));
		f[0][0][0]=0;
		int ANS=0;
		for(i=1;i<=n;i++)
		{
			cerr<<cul[i]<<' '<<cur[i]<<' '<<cdl[i]<<' '<<cdr[i]<<' '<<ZMiG[i]<<endl;
		}
		for(i=1;i<=n;i++)
		{
			for(j=0;j<=n;j++)
			{
				for(k=0;k<=n;k++)
				{
					for(dl=-1;dl<=1;dl++)
					{/*考虑当前行左边怎么连
											-1:往下连下边的块 
											0:不连或者直接连地 
											1:往上连上边的块*/ 
						for(dr=-1;dr<=1;dr++)
						{
							if(
								(dl!=-1||cdl[i]||ZMiG[i])&&
								(dr!=-1||cdr[i]||ZMiG[i])&&
								(dl!=1||cul[i]||ZMiG[i])&&
								(dr!=1||cur[i]||ZMiG[i])&&
								(j+dl>=0&&k+dr>=0)&&
								(!ZMiG[i]||!dl||dl!=dr)
							)
							{
								int t=(dl==1)+(dr==1);
								f[i][j][k]=max(f[i][j][k],f[i-1][j+dl][k+dr]+t); 
							}
						}
					}
					ANS=max(ANS,f[i][j][k]);
				}
			}
		}
		return ans-ANS;
	}
};