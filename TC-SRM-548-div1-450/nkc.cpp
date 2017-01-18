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
#define MAXM 5010
#define INF 1000000000
#define MOD 1000000007
#define eps 1e-8
#define ll long long
int n,lim;
int a[MAXN],b[MAXN];
int n1,n2;
int st=0;
int tot;
int v[MAXN],c[MAXN];
bool F[MAXN][MAXN];
bool *f[MAXN];
int anst,ansv=INF;
struct KingdomAndDice
{
	double newFairness(vector<int>_d1,vector<int>_d2,int _lim)
	{
		int i,j,k,l;
		for(i=0;i<MAXN;i++)
		{
			f[i]=F[i]+2505;
		}
		lim=_lim;
		for(i=0;i<_d1.size();i++)
		{
			if(!_d1[i])
			{
				n++;
			}
			else
			{
				a[++n1]=_d1[i];
			}
			b[++n2]=_d2[i];
		}
		sort(a+1,a+n1+1);
		sort(b+1,b+n2+1);
		for(i=1;i<=n1;i++)
		{
			for(j=1;j<=n2;j++)
			{
				if(a[i]<b[j])
				{
					st--;
				}
				else
				{
					st++;
				}
			}
		}
		b[n2+1]=lim+1;
		for(i=1;i<=n2+1;i++)
		{
			int cnt=b[i]-b[i-1]-1;
			for(j=1;j<=n1;j++)
			{
				if(a[j]>b[i-1]&&a[j]<b[i])
				{
					cnt--;
				}
			}
			if(cnt)
			{
				int W=i-1-(n2-i+1);
				v[++tot]=W;
				c[tot]=cnt;
			}
		}
		v[++tot]=-n2;
		c[tot]=n2-n1;
		f[0][st]=1;
		for(i=1;i<=tot;i++)
		{
			for(k=1;k<=n&&k<=c[i];k++)
			{
				for(j=n;j;j--)
				{
					for(l=-2500;l<=2500;l++)
					{
						if(l-v[i]>=-2500&&l-v[i]<=2500)
						{
							f[j][l]|=f[j-1][l-v[i]];
						}
					}
				}
			}
		}
		for(j=-2500;j<=2500;j++)
		{
			if(f[n][j])
			{
				if(abs(j)<ansv||(abs(j)==ansv&&j<anst))
				{
					ansv=abs(j);
					anst=j;
				}
			}
		}
		return 1.0*(anst+n2*n2)/2/n2/n2;
	}
};
/*

*/