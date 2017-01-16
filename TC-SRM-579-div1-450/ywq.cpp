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

const int inf=1000000000;

int dp[1<<16][55],a[55][3],b[3],g[55][55];

struct TravellingPurchasingMan 
{
    int maxStores(int n, vector <string> interestingStores, vector <string> roads)
    {
    	int m=interestingStores.size();
    	for (int i=0;i<m;i++)
    	{
    		int k=0,l=interestingStores[i].size();
    		for (int j=0;j<l;j++)
    			if (interestingStores[i][j]==' ')
    				k++;
    			else
    				a[i][k]=a[i][k]*10+interestingStores[i][j]-'0';
    	}
    	for (int i=0;i<n;i++)
    		for (int j=0;j<n;j++)
    			if (i!=j) g[i][j]=inf; else g[i][j]=0;
    	for (int i=0;i<roads.size();i++)
    	{
    		memset(b,0,sizeof(b));
    		int k=0,l=roads[i].size();
    		for (int j=0;j<l;j++)
    			if (roads[i][j]==' ')
    				k++;
    			else
    				b[k]=b[k]*10+roads[i][j]-'0';
    		g[b[0]][b[1]]=g[b[1]][b[0]]=b[2];
    	}
    	for (int k=0;k<n;k++)
    		for (int i=0;i<n;i++)
    			for (int j=0;j<n;j++)
    				g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
    	for (int i=0;i<n-1;i++) dp[0][i]=inf;dp[0][n-1]=0;
    	int ans=0;
    	for (int i=1;i<(1<<m);i++)
    	{
    		bool ok=0;int s=0;
    		for (int j=0;j<m;j++)
    		{
    			dp[i][j]=inf;
    			if (i&(1<<j))
    			{
    				s++;
    				for (int k=0;k<n;k++)
    					if (dp[i^(1<<j)][k]+g[k][j]<=a[j][1]) dp[i][j]=min(dp[i][j],max(dp[i^(1<<j)][k]+g[k][j],a[j][0])+a[j][2]);
    				if (dp[i][j]<inf) ok=1;
    			}
    		}
    		if (ok) ans=max(ans,s);
    		for (int j=m;j<n;j++) dp[i][j]=inf;
    	}
    	return ans;
    }
};
