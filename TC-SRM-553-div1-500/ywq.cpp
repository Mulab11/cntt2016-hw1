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

const int mod=1000000007;
int f1[55][2],f2[55][2],dp1[55],dp2[55];

struct TwoConvexShapes 
{
    int countWays(vector <string> grid)
    {
    	int n=grid.size(),m=grid[0].size();
    	for (int i=0;i<n;i++)
    	{
            //find the left(right) most 'B'('W') on the ith line
    		f1[i][0]=f1[i][1]=m;f2[i][0]=f2[i][1]=-1;
    		for (int j=0;j<m;j++)
    			if (grid[i][j]=='B') f2[i][0]=j; else if (grid[i][j]=='W') f2[i][1]=j;
    		for (int j=m-1;j>=0;j--)
    			if (grid[i][j]=='B') f1[i][0]=j; else if (grid[i][j]=='W') f1[i][1]=j;
    	}
    	int ans=0;
    	for (int k=0;k<2;k++)
    	{
    		for (int j=0;j<=m;j++) if (j<=f1[0][k^1]&&j>f2[0][k]) dp1[j]=dp2[j]=1; else dp1[j]=dp2[j]=0;
    		for (int i=1;i<n;i++)
    		{
    			int s=0;
    			for (int j=0;j<=m;j++)
    			{
    				s=(s+dp1[j])%mod;
    				if (j<=f1[i][k^1]&&j>f2[i][k]) dp1[j]=s; else dp1[j]=0;
    			}
    			s=0;
    			for (int j=m;j>=0;j--)
    			{
    				s=(s+dp2[j])%mod;
    				if (j<=f1[i][k^1]&&j>f2[i][k]) dp2[j]=s; else dp2[j]=0;
    			}
    		}
    		for (int j=0;j<=m;j++) ans=((ans+dp1[j])%mod+dp2[j])%mod;
            //we've counted the situation that the boundary is a vertical twice
    		for (int j=0;j<=m;j++)
    		{
    			bool ok=1;
    			for (int i=0;i<n;i++)
    				if (!(j<=f1[i][k^1]&&j>f2[i][k])) ok=0;
    			ans=(ans-ok+mod)%mod;
    		}
    	}
        //we've counted the situation that the boundary is a horizontal twice
    	for (int i=0;i<n;i++)
	    	for (int k=0;k<2;k++)
	    	{
	    		bool ok=1;
	    		for (int j=0;j<i;j++) if (f1[j][k]<m) ok=0;
	    		for (int j=i;j<n;j++) if (f1[j][k^1]<m) ok=0;
	    		ans=(ans-ok+mod)%mod;
	    	}
    	return ans;	
    }
};
