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

int a[22][22],dp[22][1355][2],ans[1355][2];

struct RandomPaintingOnABoard 
{
    double expectedSteps(vector <string> prob)
    {
    	int n=prob.size(),m=prob[0].size();
    	if (n<m)
    		for (int i=0;i<n;i++)
    			for (int j=0;j<m;j++)
    				a[i][j]=prob[i][j]-48;
    	else
    	{
    		swap(n,m);
    		for (int i=0;i<n;i++)
    			for (int j=0;j<m;j++)
    				a[i][j]=prob[j][i]-48;
    	}
    	int S=0;
    	for (int i=0;i<n;i++)
    		for (int j=0;j<m;j++)
    			S+=a[i][j];
    	for (int i=0;i<(1<<n);i++)
    	{
    		int ts=0;
    		dp[0][0][0]=1;dp[0][0][1]=0;
    		for (int j=0;j<m;j++)
    		{
    			int s=0;
    			for (int k=0;k<n;k++) if (i&(1<<k)) s+=a[k][j];
    			for (int k=0;k<=ts+s;k++) dp[j+1][k][0]=dp[j+1][k][1]=0;
    			for (int k=0;k<=ts;k++)
    				for (int p=0;p<2;p++)
    					if (dp[j][k][p])
    					{
    						dp[j+1][k][p]+=dp[j][k][p];
    						dp[j+1][k+s][p^1]+=dp[j][k][p];
    					}
    			ts+=s;
    		}
    		bool p=(n+m)&1;
    		for (int j=0;j<n;j++) if (i&(1<<j)) p^=1;
    		for (int j=0;j<=ts;j++)
    			for (int k=0;k<2;k++)
    				ans[j][k^p]+=dp[m][j][k];
    	}
    	double tmp=0;
    	for (int i=0;i<S;i++)
    	{
    		double x=double(i)/S;
    		tmp+=x/(1-x)*(ans[i][1]-ans[i][0]);
    	}
    	return tmp+1;
    }
};
