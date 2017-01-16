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

const int inf=1000000000;

int s[55];
int dp[55][55],g[55][55][2];

struct WallGameDiv1 
{
    int play(vector <string> costs)
    {
    	int n=costs.size(),m=costs[0].size();
    	for (int i=0;i<m;i++) dp[n-1][i]=costs[n-1][i]-'0';
    	for (int i=n-2;i>=0;i--)
    	{
    		s[0]=costs[i][0]-'0';
    		for (int j=1;j<m;j++) s[j]=s[j-1]+costs[i][j]-'0';
    		for (int k=m-1;k>=0;k--)
    			for (int p=0;p<m-k;p++)
    			{
    				int q=p+k;
    				if (k==m-1)
    					g[p][q][0]=g[p][q][1]=0;
    				else
    				{
    					g[p][q][0]=g[p][q][1]=inf;
    					if (p)
    					{
    						g[p][q][0]=g[p-1][q][0];
    						g[p][q][1]=g[p-1][q][0]+s[q-1]-s[p-1];
    					}
    					if (q+1<m)
    					{
    						g[p][q][1]=min(g[p][q][1],g[p][q+1][1]);
    						g[p][q][0]=min(g[p][q][0],g[p][q+1][1]+s[q]-s[p]);
    					}
    				}
    				g[p][q][0]=max(g[p][q][0],dp[i+1][p])+costs[i][p]-'0';
    				g[p][q][1]=max(g[p][q][1],dp[i+1][q])+costs[i][q]-'0';
    			}
    		for (int j=0;j<m;j++) dp[i][j]=g[j][j][0];
    	}
    	int ans=inf;
    	for (int i=0;i<m;i++) ans=min(ans,dp[0][i]);
    	return ans;
    }
};
