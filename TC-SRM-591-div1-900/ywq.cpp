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

const int mod=1000000009;

int pow2[20],dp[65540],dp2[65540];
int b[10][2];

struct StringPath 
{
    int countBoards(int n, int m, string A, string B)
    {
    	pow2[0]=1;for (int i=1;i<=2*m;i++) pow2[i]=pow2[i-1]<<1;
    	memset(dp,0,sizeof(dp));dp[0]=1;
    	for (int i=1;i<=n;i++)
    		for (int j=1;j<=m;j++)
    		{
    			for (int k=0;k<pow2[2*m];k++) {dp2[k]=dp[k];dp[k]=0;}
    			for (int k=0;k<pow2[2*m];k++)
    				if (dp2[k])
    				{
    					int t=k;
    					for (int p=0;p<m;p++)
    					{
    						if (t&1) b[p][0]=1; else b[p][0]=0;
    						if (t&2) b[p][1]=1; else b[p][1]=0;
    						t>>=2;
    					}
    					for (char ch='A';ch<='Z';ch++)
    					{
    						bool ok1=0,ok2=0;
    						if (i==1&&j==1)
    						{
    							if (ch==A[0]) ok1=1;
    							if (ch==B[0]) ok2=1;
    						}
    						if (i>1)
    						{
    							if (b[m-1][0]&&ch==A[i+j-2]) ok1=1;
    							if (b[m-1][1]&&ch==B[i+j-2]) ok2=1;
    						}
    						if (j>1)
    						{
    							if (b[0][0]&&ch==A[i+j-2]) ok1=1;
    							if (b[0][1]&&ch==B[i+j-2]) ok2=1;
    						}
    						int t=k%pow2[2*m-2]*4;
    						if (ok1) t+=1;
    						if (ok2) t+=2;
    						dp[t]=(dp[t]+dp2[k])%mod;
    					}
    				}
    		}
    	int ans=0;
    	for (int i=3;i<pow2[2*m];i+=4) ans=(ans+dp[i])%mod;
    	return ans;
    }
};
