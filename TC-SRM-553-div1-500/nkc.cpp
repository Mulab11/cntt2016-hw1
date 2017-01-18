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
bool okal[MAXN][MAXN],okar[MAXN][MAXN];
bool okbl[MAXN][MAXN],okbr[MAXN][MAXN];
int sal[MAXN][MAXN],sbl[MAXN][MAXN],sar[MAXN][MAXN],sbr[MAXN][MAXN];
int n,m;
struct TwoConvexShapes
{
	int countWays(vector<string>mp)
	{
		int i,j;
		n=mp.size();
		m=mp[0].size();
		for(i=0;i<=m+1;i++)
		{
			sal[0][i]=sbl[0][i]=sar[0][i]=sbr[0][i]=1;
		}
		for(i=1;i<=n;i++)
		{//预处理 
			okal[i][0]=okbl[i][0]=okar[i][m+1]=okbr[i][m+1]=1;
			for(j=1;j<=m;j++)
			{
				okal[i][j]=okal[i][j-1]&(mp[i-1][j-1]!='B');
				okbl[i][j]=okbl[i][j-1]&(mp[i-1][j-1]!='W');
			}
			for(j=m;j;j--)
			{
				okar[i][j]=okar[i][j+1]&(mp[i-1][j-1]!='B');
				okbr[i][j]=okbr[i][j+1]&(mp[i-1][j-1]!='W');
			}
		}
		for(i=1;i<=n;i++)
		{//DP
			for(j=1;j<=m+1;j++)
			{
				sar[i][j]=sar[i][j-1];
				sbr[i][j]=sbr[i][j-1];
				if(okar[i][j]&&okbl[i][j-1])
				{
					(sar[i][j]+=sar[i-1][j])%=MOD;
				}
				if(okbr[i][j]&&okal[i][j-1])
				{
					(sbr[i][j]+=sbr[i-1][j])%=MOD;
				}
				
			}
			for(j=m;~j;j--)
			{
				sal[i][j]=sal[i][j+1];
				sbl[i][j]=sbl[i][j+1];
				if(okal[i][j]&&okbr[i][j+1])
				{
					(sal[i][j]+=sal[i-1][j])%=MOD;
				}
				if(okbl[i][j]&&okar[i][j+1])
				{
					(sbl[i][j]+=sbl[i-1][j])%=MOD;
				}
				
			}
		}
		int re=((sbl[n][0]+sal[n][0])%MOD+(sar[n][m+1]+sbr[n][m+1])%MOD)%MOD;
		for(j=1;j<=m+1;j++)
		{//去重垂直分割的方案数 
			bool flag1=1;
			bool flag2=1;
			for(i=1;i<=n;i++)
			{
				if(!okal[i][j-1]||!okbr[i][j])
				{
					flag1=0;
				}
				if(!okbl[i][j-1]||!okar[i][j])
				{
					flag2=0;
				}
			}
			(re+=MOD-flag1-flag2)%=MOD;
		}
		for(i=1;i<=n;i++)
		{//去重水平分割的方案数 
			bool flag1=1;
			bool flag2=1;
			for(j=1;j<=i;j++)
			{
				if(!okal[j][m])
				{
					flag1=0;
				}
				if(!okbl[j][m])
				{
					flag2=0;
				}
			}
			for(j=i+1;j<=n;j++)
			{
				if(!okbr[j][1])
				{
					flag1=0;
				}
				if(!okar[j][1])
				{
					flag2=0;
				}
			}
			(re+=MOD-flag1-flag2)%=MOD;
		}
		return re;
	}
};

/*

*/