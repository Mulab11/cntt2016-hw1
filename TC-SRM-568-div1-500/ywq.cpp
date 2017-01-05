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

int d[55],fa[55],w[55],g[55],a[55],dp[55][15][15];

int find(int x)
{
	int y=fa[x];
	if (x!=fa[x]) fa[x]=find(fa[x]);
	d[x]+=d[y];
	return fa[x];
}

struct EqualSums 
{
    int count(vector <string> board)
    {
    	int n=board.size(),m=board[0].size();
    	for (int i=0;i<n;i++)
   		{
   			fa[i]=i;d[i]=0;
   		}
    	for (int i=0;i<n;i++)
    		for (int j=0;j<m;j++)
    			for (int k=j+1;k<m;k++)
    				if (board[i][j]!='-'&&board[i][k]!='-')
    				{
    					int fx=find(j),fy=find(k);
    					if (fx==fy)
    					{
    						if (d[j]-d[k]!=board[i][k]-board[i][j]) return 0;
    					}
    					else
    					{
    						int t=d[j]-d[k]+board[i][j]-board[i][k];
    						if (t>0)
    						{
    							fa[fy]=fx;d[fy]=t;
    						}
    						else
    						{
    							fa[fx]=fy;d[fx]=-t;
    						}
    					}
    				}
    	for (int i=0;i<m;i++) w[i]=10;
    	for (int i=0;i<n;i++)
    		for (int j=0;j<m;j++)
    			if (board[i][j]!='-')
    			{
    				int x=find(j);
    				w[x]=min(w[x],board[i][j]-'0'+d[j]);
    			}
    	for (int i=0;i<m;i++)
    	{
    		int x=find(i);g[x]=max(g[x],d[i]);
    	}
    	int cnt=0;
    	for (int i=0;i<m;i++) if (i==find(i)) a[++cnt]=i;
    	for (int i=1;i<=cnt;i++) if (g[a[i]]>w[a[i]]) return 0;
    	memset(dp,0,sizeof(dp));dp[1][w[a[1]]][g[a[1]]]=1;
    	for (int i=2;i<=cnt;i++)
    		for (int j=0;j<10;j++)
    			for (int k=0;k<10;k++)
    				if (dp[i-1][j][k])
    					for (int p=-9;p<=9;p++)
    					{
    						if (j-p-g[a[i]]<0) continue;
    						if (w[a[i]]+p-k<0) continue;
    						dp[i][min(j,w[a[i]]+p)][max(k,p+g[a[i]])]=(dp[i][min(j,w[a[i]]+p)][max(k,p+g[a[i]])]+dp[i-1][j][k])%mod;
    					}
    	int ans=0;
    	for (int j=0;j<10;j++)
    		for (int k=0;k<10;k++)
    			ans=(ans+dp[cnt][j][k])%mod;
    	return ans;
    }
};
