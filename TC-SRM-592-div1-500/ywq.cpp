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

int dp[55][2510],dp2[55][2510];

struct LittleElephantAndPermutationDiv1 
{
    int getNumber(int N, int K)
    {
    	int M=N*(N+1);
    	dp[0][M/2]=1;
    	for (int i=1;i<=N;i++)
    	{
    		for (int j=0;j<=N;j++)
    			for (int k=0;k<=M;k++)
    			{
    				dp2[j][k]=dp[j][k];
    				dp[j][k]=ll(2*j+1)*dp[j][k]%mod;
    			}
    		for (int j=0;j<=N;j++)
    			for (int k=0;k<=M;k++)
    				if (dp2[j][k])
    				{
    					dp[j+1][k-i]=(dp[j+1][k-i]+dp2[j][k])%mod;
    					if (j) dp[j-1][k+i]=(ll(dp2[j][k])*j%mod*j+dp[j-1][k+i])%mod;
    				}
       	}
    	int ans=0;
    	for (int i=K;i<=M;i++) ans=(ans+dp[0][i])%mod;
    	for (int i=1;i<=N;i++) ans=ll(ans)*i%mod;
    	return ans;
    }
};
