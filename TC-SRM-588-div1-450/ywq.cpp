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

int dp[1<<12][135];

struct KeyDungeonDiv1 
{
    int maxKeys(vector <int> doorR, vector <int> doorG, vector <int> roomR, vector <int> roomG, vector <int> roomW, vector <int> keys)
    {
    	int n=doorR.size();
    	for (int i=0;i<(1<<n);i++)
    		for (int j=0;j<=130;j++)
    			dp[i][j]=-1;
    	dp[0][keys[0]]=keys[2];
    	int ans=0;
    	for (int i=0;i<(1<<n);i++)
    	{
    		int s0=keys[0],s1=keys[1],s2=keys[2];
    		for (int j=0;j<n;j++) 
    			if (i&(1<<j))
    			{
    				s0+=roomR[j]-doorR[j];
    				s1+=roomG[j]-doorG[j];
    				s2+=roomW[j];
    			}
    		for (int j=0;j<=130;j++)
    			if (dp[i][j]>-1)
    			{
    				ans=max(ans,s0+s1+s2);
    				int k=dp[i][j];
    				int p=s0+s1+s2-j-k;
    				for (int q=0;q<n;q++)
    					if (!(i&(1<<q)))
    					{
    						if (j+k>=doorR[q]&&p+k>=doorG[q]&&j+k+p>=doorR[q]+doorG[q])
    							dp[i|(1<<q)][max(0,j-doorR[q])+roomR[q]]=max(dp[i|(1<<q)][max(0,j-doorR[q])+roomR[q]],dp[i][j]-max(doorR[q]-j,0)-max(doorG[q]-p,0)+roomW[q]);
    					}
    			}
    	}
    	return ans;
    }
};
