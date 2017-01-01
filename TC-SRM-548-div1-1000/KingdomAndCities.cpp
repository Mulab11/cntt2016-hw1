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

int dp[55][3][55],g[55][3][55],c[1255][1255];

struct KingdomAndCities 
{
    int howMany(int N, int M, int K)
    {
    	for (int i=0;i<=1250;i++)
    	{
    		c[i][0]=c[i][i]=1;
    		for (int j=1;j<i;j++) c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
    	}
        //dp[i][j][k] represents the number of connected graphs that has i nodes,j of them number in [0,M-1] and k edges
    	for (int i=1;i<=N;i++)
    		for (int j=0;j<=M&&j<=i;j++)
    			for (int k=0;k<=K;k++)
    			{
    				int x=i*(i-1)/2;
    				if (j==0) dp[i][j][k]=c[x][k];
    				if (j==1&&k>=2) dp[i][j][k]=ll(c[x-i+1][k-2])*c[i-1][2]%mod;
    				if (j==2)
    				{
    					if (k>=4) dp[i][j][k]=ll(c[x-2*i+3][k-4])*c[i-2][2]%mod*c[i-2][2]%mod;
    					if (k>=3) dp[i][j][k]=(ll(c[x-2*i+3][k-3])*(i-2)%mod*(i-2)%mod+dp[i][j][k])%mod;
    				}
    				g[i][j][k]=dp[i][j][k];
                    //g[i][j][k]:the graph can be unconnected
    				for (int x=1;x<i;x++) //enumerate the number of nodes in the first connected component
    					for (int y=0;y<=k;y++) //enumerate the number of edges in the first connected component
    					{
    						if (j==0) dp[i][0][k]=((-ll(dp[x][0][y])*g[i-x][0][k-y]%mod*c[i-1][x-1]+dp[i][0][k])%mod+mod)%mod;
    						if (j==1) dp[i][1][k]=((-ll(dp[x][1][y])*g[i-x][0][k-y]%mod*c[i-1][x-1]+dp[i][1][k])%mod+mod)%mod;
    						if (j==2)
    						{
    							if (x>=2) dp[i][2][k]=((-ll(dp[x][2][y])*g[i-x][0][k-y]%mod*c[i-2][x-2]+dp[i][2][k])%mod+mod)%mod;
    							dp[i][2][k]=((-ll(dp[x][1][y])*g[i-x][1][k-y]%mod*c[i-2][x-1]+dp[i][2][k])%mod+mod)%mod;
    						}
    					}
    			}
    	return dp[N][M][K];
    }						
};
