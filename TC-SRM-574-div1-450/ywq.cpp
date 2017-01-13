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

ll dp[1<<18][18];

struct PolygonTraversal 
{
    long long count(int N, vector <int> points)
    {
    	int init=0;
    	for (int i=0;i<points.size();i++) init|=(1<<(points[i]-1));
    	dp[init][points[points.size()-1]-1]=1;
    	for (int i=init;i<(1<<N)-1;i++)
    	{
    		int s=0;
    		for (int j=0;j<N;j++) if (i&(1<<j)) s++;
    		for (int j=0;j<N;j++)
    			if (dp[i][j])
    				for (int k=0;k<N;k++)
    					if (!(i&(1<<k)))
    					{
    						int t=0;
    						for (int p=min(k,j);p<=max(k,j);p++) if (i&(1<<p)) t++;
    						if (t==1||t==s) continue;
    						dp[i|(1<<k)][k]+=dp[i][j];
    					}
    	}
    	ll ans=0;
    	for (int i=0;i<N;i++) if (abs(points[0]-1-i)!=1&&abs(points[0]-1-i)!=N-1) ans+=dp[(1<<N)-1][i];
    	return ans;
    }
};
