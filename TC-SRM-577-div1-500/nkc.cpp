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
#define MAXN 110
#define MAXM 1010
#define INF 1000000000
#define MOD 1000000007
#define eps 1e-8
#define ll long long
struct EllysChessboard
{
	int f[15][15][15][15];
	int n;
	int X[MAXN],Y[MAXN];
	int LX,LY,RX,RY;
	int val(int lx,int ly,int rx,int ry,int x,int y)
	{
		return max(max(abs(lx-x),abs(rx-x)),max(abs(ly-y),abs(ry-y)));
	}
	bool inside(int lx,int ly,int rx,int ry,int x,int y)
	{
		return x>=lx&&x<=rx&&y>=ly&&y<=ry;
	}
	void cal(int lx,int ly,int rx,int ry)
	{
		int i,j;
		for(i=1;i<=n;i++)
		{
			if(!inside(lx,ly,rx,ry,X[i],Y[i]))
			{
				int nlx=lx,nly=ly,nrx=rx,nry=ry;
				nlx=min(nlx,X[i]);
				nly=min(nly,Y[i]);
				nrx=max(nrx,X[i]);
				nry=max(nry,Y[i]);
				int t=f[lx][ly][rx][ry];
				t+=val(lx,ly,rx,ry,X[i],Y[i]);
				for(j=1;j<=n;j++)
				{
					if(i!=j&&inside(nlx,nly,nrx,nry,X[j],Y[j])&&!inside(lx,ly,rx,ry,X[j],Y[j]))
					{
						t+=val(nlx,nly,nrx,nry,X[j],Y[j]);
					}
				}
				f[nlx][nly][nrx][nry]=min(f[nlx][nly][nrx][nry],t);
			}
		}
	}
	int minCost(vector<string> mp)
	{
		int i,j,k,l;
		LX=INF;
		LY=INF;
		RX=0;
		RY=0;
		memset(f,0x3f,sizeof(f));
		for(i=0;i<mp.size();i++)
		{
			for(j=0;j<mp[i].size();j++)
			{
				if(mp[i][j]=='#')
				{
					X[++n]=i+j;
					Y[n]=i-j+7;
					LX=min(LX,X[n]);
					LY=min(LY,Y[n]);
					RX=max(RX,X[n]);
					RY=max(RY,Y[n]);
					f[X[n]][Y[n]][X[n]][Y[n]]=0;
				}
			}
		}
		if(!n)
		{
			return 0;
		}
		for(i=0;i<=14;i++)
		{
			for(j=0;j<=14;j++)
			{
				for(k=0;k+i<=14;k++)
				{
					for(l=0;l+j<=14;l++)
					{
						if(f[k][l][k+i][l+j]<INF)
						{
							cal(k,l,k+i,l+j);
						}
					}
				}
			}
		}
		return f[LX][LY][RX][RY];
	}
};

/*

*/