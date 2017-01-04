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

struct SpellCards 
{
    int maxDamage(vector <int> level, vector <int> damage)
    {
    	int n=level.size();
    	memset(dp,0,sizeof(dp));
    	for (int i=0;i<n;i++)
    		for (int j=0;j<=n;j++)
    		{
    			dp[i+1][j]=max(dp[i+1][j],dp[i][j]);
    			if (j+level[i]<=n) dp[i+1][j+level[i]]=max(dp[i+1][j+level[i]],dp[i][j]+damage[i]);
    		}
    	return dp[n][n];
    }
};
