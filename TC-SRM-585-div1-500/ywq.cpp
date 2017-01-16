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
int dp[1300],dp2[1300],c[1300][1300];

struct LISNumber 
{
    int count(vector <int> cardsnum, int K)
    {
    	int n=cardsnum.size();
    	memset(dp,0,sizeof(dp));dp[cardsnum[n-1]-1]=1;
    	int s=cardsnum[n-1];
    	for (int i=0;i<=1296;i++)
    	{
    		c[i][0]=c[i][i]=1;
    		for (int j=1;j<i;j++) c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
    	}
    	for (int i=n-2;i>=0;i--)
    	{
    		memset(dp2,0,sizeof(dp2));
    		for (int j=0;j<s;j++)
    			if (dp[j])
    				for (int x=0;x<2;x++)
    					for (int k=0;k<=j&&k<=cardsnum[i]-x;k++)
    					{
    						int t=ll(c[j][k])*c[s-j+cardsnum[i]-1][s-j+x+k-1]%mod;
    						dp2[j+cardsnum[i]-x-k]=(ll(t)*dp[j]+dp2[j+cardsnum[i]-x-k])%mod;
    					}
    		memcpy(dp,dp2,sizeof(dp));
    		s+=cardsnum[i];
    	}
    	return dp[K-1];
    }
};
