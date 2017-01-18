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
#define MAXN 50
#define MAXM 1010
#define INF 1000000000
#define MOD 1000000007
#define eps 1e-8
#define ll long long
int s1[MAXN][MAXN],s2[MAXN][MAXN];
int MX1[MAXN][MAXM*2],MX2[MAXN][MAXM*2],MX3[MAXN][MAXM*2],MX4[MAXN][MAXM*2];
int *mx1[MAXN],*mx2[MAXN],*mx3[MAXN],*mx4[MAXN];
int q[MAXM*2],hd,tl;
int n,m;
struct FoxAndFlowerShopDivOne
{
	int theMaxFlowers(vector<string>mp,int mx)
	{
		int i,j,k,l;
		n=mp.size();
		m=mp[0].size();
		memset(MX1,0xef,sizeof(MX1));
		memset(MX2,0xef,sizeof(MX2));
		memset(MX3,0xef,sizeof(MX3));
		memset(MX4,0xef,sizeof(MX4));
		int re=-1;
		for(i=0;i<=n+1;i++)
		{
			mx1[i]=MX1[i]+MAXM+5;
			mx2[i]=MX2[i]+MAXM+5;
		}
		for(i=0;i<=m+1;i++)
		{
			mx3[i]=MX3[i]+MAXM+5;
			mx4[i]=MX4[i]+MAXM+5;
		}
		for(i=1;i<=n;i++)
		{
			for(j=1;j<=m;j++)
			{
				s1[i][j]=s1[i-1][j]+s1[i][j-1]-s1[i-1][j-1];
				s2[i][j]=s2[i-1][j]+s2[i][j-1]-s2[i-1][j-1];
				if(mp[i-1][j-1]=='L')
				{
					s1[i][j]++;
					s2[i][j]++;
				}
				if(mp[i-1][j-1]=='P')
				{
					s1[i][j]--;
					s2[i][j]++;
				}
				for(k=1;k<=i;k++)
				{
					for(l=1;l<=j;l++)
					{
						int c=s1[i][j]-s1[k-1][j]-s1[i][l-1]+s1[k-1][l-1];
						int v=s2[i][j]-s2[k-1][j]-s2[i][l-1]+s2[k-1][l-1];
						mx1[i][c]=max(mx1[i][c],v);
						mx2[k][c]=max(mx2[k][c],v);
						mx3[j][c]=max(mx3[j][c],v);
						mx4[l][c]=max(mx4[l][c],v);
					}
				}
			}
		}
		for(i=1;i<=n;i++)
		{
			for(j=-n*m;j<=n*m;j++)
			{
				mx1[i][j]=max(mx1[i][j],mx1[i-1][j]);
			}
		}
		for(i=n;i;i--)
		{
			for(j=-n*m;j<=n*m;j++)
			{
				mx2[i][j]=max(mx2[i][j],mx2[i+1][j]);
			}
		}
		for(i=1;i<=m;i++)
		{
			for(j=-n*m;j<=n*m;j++)
			{
				mx3[i][j]=max(mx3[i][j],mx3[i-1][j]);
			}
		}
		for(i=m;i;i--)
		{
			for(j=-n*m;j<=n*m;j++)
			{
				mx4[i][j]=max(mx4[i][j],mx4[i+1][j]);
			}
		}
		for(i=1;i<n;i++)
		{
			int wzh=n*m;
			hd=1;
			tl=0;
			for(j=-n*m;j<=n*m;j++)
			{
				while(hd<=tl&&(q[hd]+j<-mx||q[hd]+j>mx))
				{
					hd++;
				}
				while(wzh>=-n*m&&wzh+j>=-mx&&wzh+j<=mx)
				{
					while(hd<=tl&&mx2[i+1][q[tl]]<=mx2[i+1][wzh])
					{
						tl--;
					}
					q[++tl]=wzh;
					wzh--;
				}
				
				re=max(re,mx1[i][j]+mx2[i+1][q[hd]]);
			}
		}
		for(i=1;i<m;i++)
		{
			int wzh=n*m;
			hd=1;
			tl=0;
			for(j=-n*m;j<=n*m;j++)
			{
				while(hd<=tl&&(q[hd]+j<-mx||q[hd]+j>mx))
				{
					hd++;
				}
				while(wzh>=-n*m&&wzh+j>=-mx&&wzh+j<=mx)
				{
					while(hd<=tl&&mx4[i+1][q[tl]]<=mx4[i+1][wzh])
					{
						tl--;
					}
					q[++tl]=wzh;
					wzh--;
				}
				re=max(re,mx3[i][j]+mx4[i+1][q[hd]]);
			}
		}
		return re;
	}
};

/*

*/