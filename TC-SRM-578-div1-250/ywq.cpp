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

bool v[55][55];
int q[2510][2];

struct GooseInZooDivOne 
{
    int count(vector <string> field, int dist)
    {
    	int n=field.size(),m=field[0].size();
    	int dp[2];
    	dp[0]=1;dp[1]=0;
    	for (int i=0;i<n;i++)
    		for (int j=0;j<m;j++)
    			if (field[i][j]=='v'&&!v[i][j])
    			{
    				int f=1,r=1;q[1][0]=i;q[1][1]=j;v[i][j]=1;
    				while (f<=r)
    				{
    					for (int tx=0;tx<n;tx++)
    						for (int ty=0;ty<m;ty++)
    							if (abs(tx-q[f][0])+abs(ty-q[f][1])<=dist&&field[tx][ty]=='v'&&!v[tx][ty])
    							{
    								q[++r][0]=tx;q[r][1]=ty;
    								v[tx][ty]=1;
    							}
    					f++;
    				}
    				if (r&1)
    					dp[0]=dp[1]=(dp[0]+dp[1])%mod;
    				else
    				{
    					dp[0]=dp[0]*2%mod;
    					dp[1]=dp[1]*2%mod;
    				}
    			}
    	return (dp[0]-1+mod)%mod;
    }
};
