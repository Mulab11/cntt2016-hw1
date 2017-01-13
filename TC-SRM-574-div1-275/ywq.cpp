#include <map>
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

#define pb push_back
#define mp make_pair
#define x first
#define y second

typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;

bool ok[10][10][2][10][10][2],dp[10][10][2][10][10][2],dp2[10][10][2][10][10][2];
int a[10],b[10];

struct TheNumberGame 
{
    string determineOutcome(int A, int B)
    {
    	int t=A,n=0;
    	while (t)
    	{
    		a[++n]=t%10;t/=10;
    	}
    	int m=0;t=B;
    	while (t)
    	{
    		b[++m]=t%10;t/=10;
    	}
    	for (int i0=1;i0<=n;i0++)
    		for (int j0=i0;j0<=n;j0++)
    			for (int k0=0;k0<2;k0++)
    			{
    				int d0=0;
    				if (k0) for (int p=i0;p<=j0;p++) d0=d0*10+a[p]; else for (int p=j0;p>=i0;p--) d0=d0*10+a[p];
    				for (int i1=1;i1<=m;i1++)
    					for (int j1=i1;j1<=m;j1++)
    						for (int k1=0;k1<2;k1++)
    						{
    							int d1=0;
    							if (k1) for (int p=i1;p<=j1;p++) d1=d1*10+b[p]; else for (int p=j1;p>=i1;p--) d1=d1*10+b[p];
    							if (d0==d1) ok[i0][j0][k0][i1][j1][k1]=dp[i0][j0][k0][i1][j1][k1]=1;
    						}
    			}
    	for (int T=999;T;T--)
    	{
    		for (int i0=1;i0<=n;i0++)
    			for (int j0=i0;j0<=n;j0++)
    				for (int k0=0;k0<2;k0++)
    					for (int i1=1;i1<=m;i1++)
    						for (int j1=i1;j1<=m;j1++)
    							for (int k1=0;k1<2;k1++)
    								dp2[i0][j0][k0][i1][j1][k1]=dp[i0][j0][k0][i1][j1][k1];
    		for (int i0=1;i0<=n;i0++)
    			for (int j0=i0;j0<=n;j0++)
    				for (int k0=0;k0<2;k0++)
    					for (int i1=1;i1<=m;i1++)
    						for (int j1=i1;j1<=m;j1++)
    							for (int k1=0;k1<2;k1++)
    								if (ok[i0][j0][k0][i1][j1][k1])
    									dp[i0][j0][k0][i1][j1][k1]=1;
    								else
    									if (T&1)
    									{
    										dp[i0][j0][k0][i1][j1][k1]=dp2[i0][j0][k0^1][i1][j1][k1];
    										if (i0<j0) {if (k0) dp[i0][j0][k0][i1][j1][k1]|=dp2[i0][j0-1][k0][i1][j1][k1]; else dp[i0][j0][k0][i1][j1][k1]|=dp2[i0+1][j0][k0][i1][j1][k1];}
    									}
    									else
    									{
    										dp[i0][j0][k0][i1][j1][k1]=dp2[i0][j0][k0][i1][j1][k1^1];
    										if (i1<j1) {if (k1) dp[i0][j0][k0][i1][j1][k1]&=dp2[i0][j0][k0][i1][j1-1][k1]; else dp[i0][j0][k0][i1][j1][k1]&=dp2[i0][j0][k0][i1+1][j1][k1];}
										}
		}
		if (dp[1][n][0][1][m][0]) return "Manao wins"; else return "Manao loses";
	}
};
