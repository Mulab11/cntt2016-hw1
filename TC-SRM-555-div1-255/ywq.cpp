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

//a simple dp problem

int dp[55];

struct CuttingBitString 
{
    int getmin(string S)
    {
    	int n=S.size();dp[0]=0;
    	for (int i=1;i<=n;i++)
    	{
    		dp[i]=n+1;
    		for (int j=0;j<i;j++)
    		{
    			ll t=0;
    			for (int k=j;k<i;k++) t=t*2+S[k]-'0';
    			while (t&&t%5==0) t/=5;
    			if (t==1&&S[j]=='1') dp[i]=min(dp[i],dp[j]+1);
    		}
    	}
    	if (dp[n]==n+1) return -1; else return dp[n];
    }
};
