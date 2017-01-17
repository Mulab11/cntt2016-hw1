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

int dp[55][55];

struct AstronomicalRecords 
{
    int minimalPlanets(vector <int> a, vector <int> b)
    {
    	int n=a.size(),m=b.size();
    	int ans=n+m;
    	for (int p=0;p<n;p++)
    		for (int q=0;q<m;q++)
    		{
    			for (int i=0;i<=n;i++)
    				for (int j=0;j<=m;j++)
    				{
    					dp[i][j]=0;
    					if (i) dp[i][j]=max(dp[i][j],dp[i-1][j]);
    					if (j) dp[i][j]=max(dp[i][j],dp[i][j-1]);
    					if (i&&j&&ll(a[i-1])*b[q]==ll(b[j-1])*a[p]) dp[i][j]=max(dp[i][j],dp[i-1][j-1]+1);
    				}
    			ans=min(ans,n+m-dp[n][m]);
    		}
    	return ans;
    }
};
