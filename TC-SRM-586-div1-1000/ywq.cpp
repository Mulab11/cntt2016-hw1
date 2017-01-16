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
int dp[55][28][28],dp2[28][28],dp3[28][28];

struct StringWeight 
{
    int getMinimum(vector <int> L)
    {
    	int n=L.size();
    	for (int i=0;i<=n;i++)
    		for (int j=0;j<=26;j++)
    			for (int k=0;k<=26;k++)
    				dp[i][j][k]=inf;
    	dp[0][0][0]=0;int s=0;
    	for (int i=0;i<n;i++)
    	{
    		if (L[i]<=26)
   				for (int k=0;k<=26-L[i];k++)
   				{
   					for (int p=k;p<=26;p++)
   					{
   						dp2[p][k]=dp[i][p][k];
   						for (int q=k+1;q<=p;q++)
    						dp2[p][q]=inf;
    				}
    				for (int l=0;l<L[i];l++)
    				{
    					for (int p=k;p<=26;p++)
    						for (int q=k;q<=p;q++)
    						{
    							dp3[p][q]=dp2[p][q];dp2[p][q]=inf;
    						}
    					for (int p=k;p<=26;p++)
    						for (int q=k;q<=p;q++)
    							if (dp3[p][q]<(inf>>1))
    								for (int x=(p-k<=l);x<=(p<26);x++)
    									for (int y=0;y<2;y++)
    										dp2[p+x][q+y]=min(dp2[p+x][q+y],dp3[p][q]-x*(s+l)+y*(s+l));
    				}
    				for (int p=k;p<=26;p++)
    					for (int q=k;q<=p;q++)
    						dp[i+1][p][q]=min(dp[i+1][p][q],dp2[p][q]);
    			}
    		else
    			for (int j=0;j<26;j++)
    			{
    				for (int p=0;p<=26;p++)
   					{
   						dp2[p][0]=dp[i][p][0];
   						for (int q=1;q<=p;q++)
    						dp2[p][q]=inf;
    				}
    				int t=s;
    				for (int l=0;l<26;l++)
    				{
    					int l0=t,r0=t;
    					if (l==j) r0+=L[i]-26;
    					for (int p=0;p<=26;p++)
    						for (int q=0;q<=p;q++)
    						{
    							dp3[p][q]=dp2[p][q];dp2[p][q]=inf;
    						}
    					for (int p=0;p<=26;p++)
    						for (int q=0;q<=p;q++)
    							if (dp3[p][q]<(inf>>1))
    								for (int x=(p<=l);x<=(p<26);x++)
    									for (int y=0;y<2;y++)
    										dp2[p+x][q+y]=min(dp2[p+x][q+y],dp3[p][q]-x*l0+y*r0);
    					if (l==j) t=r0;t++;
    				}
    				for (int p=0;p<=26;p++)
    					for (int q=0;q<=p;q++)
    						dp[i+1][p][q]=min(dp[i+1][p][q],dp2[p][q]);
    			}
    		s+=L[i];
    	}
    	int ans=inf;
    	for (int i=1;i<=26;i++) ans=min(ans,dp[n][i][i]);
    	return ans;
    }
};
