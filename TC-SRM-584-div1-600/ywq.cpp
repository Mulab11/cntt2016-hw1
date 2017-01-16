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

int a[55],b[55];
bool ok[55];
ll dp[55][55],dp2[55][55],c[55][55];

struct Excavations 
{
    long long count(vector <int> kind, vector <int> depth, vector <int> found, int K)
    {
    	int n=kind.size();
    	for (int i=0;i<n;i++) a[i]=depth[i];
    	sort(a,a+n);
    	int n2=1;
    	for (int i=1;i<n;i++) if (a[i]!=a[i-1]) a[n2++]=a[i];
    	for (int i=0;i<n;i++) depth[i]=lower_bound(a,a+n2,depth[i])-a+1;
    	memset(dp,0,sizeof(dp));dp[0][0]=1;
   		memset(ok,0,sizeof(ok));
    	for (int i=0;i<found.size();i++)
    	{
    		ok[found[i]]=1;
    		for (int j=0;j<=n2;j++)
    			for (int k=0;k<=n;k++)
    			{
    				dp2[j][k]=dp[j][k];dp[j][k]=0;
    			}
    		int m=0;
    		for (int j=0;j<n;j++) if (kind[j]==found[i]) b[m++]=depth[j];
    		sort(b,b+m);
    		for (int j=0;j<=n2;j++)
    			for (int k=0;k<=n;k++)
    				if (dp2[j][k])
    					for (int l=0;l<m;l++)
    						dp[max(j,b[l])][k+l]+=dp2[j][k];
    	}
    	for (int i=0;i<=n;i++)
    	{
    		c[i][0]=c[i][i]=1;
    		for (int j=1;j<i;j++) c[i][j]=c[i-1][j-1]+c[i-1][j];
    	}
    	ll ans=0;
    	for (int i=1;i<=n2;i++)
    	{
    		int x=n-found.size();
    		for (int j=0;j<n;j++) if (depth[j]<=i&&!ok[kind[j]]) x--;
    		for (int j=0;j<=n;j++)
    			if (dp[i][j])
    			{
    				int y=K-found.size();
    				if (x-j>=y) ans+=c[x-j][y]*dp[i][j];
    			}
    	}
    	return ans;
    }
};
