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
const int di[3][2]={{1,0},{0,1},{0,-1}};

void checkmin(int &x,int y)
{
	if (y<x) x=y;
}

bool v[55][55];
int q[2510][2],type[55][2],dp[55][55],dp2[55][55];

struct Tunnels 
{
    int minimumTunnels(vector <string> frame)
    {
    	int n=frame.size(),m=frame[0].size();
    	if (m==1)
    	{
    		for (int i=0;i<n;i++) if (frame[i][0]=='X') return 1;
    		return 0;
   		}
   		int ans=0;
    	for (int i=0;i<n;i++)
    		for (int j=0;j<m;j++)
    			if (frame[i][j]=='X'&&!v[i][j])
    			{
    				int s=0;
    				for (int k=0;k<3;k++)
    				{
    					int x=i+di[k][0],y=j+di[k][1];
    					if (x>=0&&x<n&&y>=0&&y<m&&frame[x][y]=='X') s++;
    				}
    				if (s<2)
    				{
    					int f=1,r=1;q[1][0]=i;q[1][1]=j;v[i][j]=1;
    					while (f<=r)
    					{
    						int x=q[f][0],y=q[f][1];f++;
    						for (int k=0;k<3;k++)
    						{
    							int tx=x+di[k][0],ty=y+di[k][1];
    							if (tx>=0&&tx<n&&ty>=0&&ty<m&&frame[tx][ty]=='X'&&!v[tx][ty])
    							{
    								q[++r][0]=tx;q[r][1]=ty;
    								v[tx][ty]=1;
    							}
    						}
    					}
    					if (i==q[r][0]&&j==0&&q[r][1]==m-1) {type[i][0]=type[i][1]=1;continue;}
    					if (i==0)
    					{
    						ans++;
    						if (q[r][0]==0&&j==0) {type[0][0]=2;continue;}
    						if (q[r][1]>0&&q[r][1]<m-1) continue;    					
    						if (q[r][1]==0) type[q[r][0]][0]=2; else type[q[r][0]][1]=2;
    						continue;
    					}
    					if (i==q[r][0])
    					{
 							if (j==0) type[i][0]=3; else type[i][1]=3;
 							continue;
    					}
    					if (j==q[r][1]&&i+1==q[r][0])
    					{
    						type[i][bool(j)]=3;continue;
    					}
    					if (j==0) type[i][0]=3; else type[i][1]=3;
    					if (q[r][1]==0) type[q[r][0]][0]=2; else if (q[r][1]==m-1) type[q[r][0]][1]=2;
    				}
    			}
    	for (int j=0;j<=n;j++)
    		for (int k=0;k<=n;k++)
    			dp[j][k]=inf;
    	dp[0][0]=0;
    	for (int i=0;i<n;i++)
    	{
    		for (int j=0;j<=n;j++)
    			for (int k=0;k<=n;k++)
    			{
    				dp2[j][k]=dp[j][k];dp[j][k]=inf;
    			}
    		for (int j=0;j<=n;j++)
    			for (int k=0;k<=n;k++)
    				if (dp2[j][k]<inf)
    				{
    					if (type[i][0]==1)
    					{
    						checkmin(dp[max(j-1,0)][k+1],dp2[j][k]+(j==0));
    						checkmin(dp[j+1][max(k-1,0)],dp2[j][k]+(k==0));
    						continue;
    					}
    					int t1=dp2[j][k],t2=j,t3=k;
    					if (type[i][0]==2) t2++;
    					if (type[i][1]==2) t3++;
    					if (type[i][0]==3)
    					{
    						if (t2) t2--; else t1++;
    					}
    					if (type[i][1]==3)
    					{
    						if (t3) t3--; else t1++;
    					}
    					checkmin(dp[t2][t3],t1);
    				}
    	}
    	int tmp=inf;
    	for (int j=0;j<=n;j++)
    		for (int k=0;k<=n;k++)
    			checkmin(tmp,dp[j][k]);
    	return ans+tmp;
    }
};
