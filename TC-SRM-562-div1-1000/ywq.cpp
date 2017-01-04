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

const int mod=1000000009;

vi e[55];
int c[55][55],size[55],g[55],dp[55][55][55],d[55][55],dp2[55][55];
bool v[55];

int power(int x,int y)
{
	int t=1;
	while (y)
	{
		if (y&1) t=ll(t)*x%mod;
		x=ll(x)*x%mod;y>>=1;
	}
	return t;
}

void dfs1(int k,int x)
{
	size[k]=0;g[k]=1;v[k]=1;
	for (int i=0;i<e[k].size();i++)
	{
		int y=e[k][i];
		if (d[x][y]>d[x][k]&&!v[y])
		{
			dfs1(y,x);size[k]+=size[y];
			g[k]=ll(g[k])*g[y]%mod*c[size[k]][size[y]]%mod;
		}
	}
	size[k]++;v[k]=0;
}

void dfs2(int k)
{
	v[k]=1;size[k]=1;g[k]=1;
	dp[k][0][0]=1;
	for (int i=0;i<e[k].size();i++)
	{
		int z=e[k][i];
		if (!v[z])
		{
			dfs2(z);size[k]+=size[z];
			g[k]=ll(g[k])*g[z]%mod*c[size[k]-1][size[z]]%mod;
			for (int p=0;p<=size[k];p++)
				for (int q=0;p+q<=size[k];q++)
				{
					dp2[p][q]=dp[k][p][q];dp[k][p][q]=0;
				}

            //Two-dimensional convolution

			for (int p=0;p<=size[k]-size[z];p++)
				for (int q=0;p+q<=size[k]-size[z];q++)
					for (int x=0;x<=size[z];x++)
						for (int y=0;x+y<=size[z];y++)
							dp[k][p+x][q+y]=(ll(dp2[p][q])*dp[z][x][y]%mod*c[p+x][p]%mod*c[q+y][q]+dp[k][p+x][q+y])%mod;
		}
	}
	v[k]=0;
	dp[k][size[k]][0]=dp[k][0][size[k]]=g[k];
}

struct InducedSubgraphs 
{
    int getCount(vector <int> edge1, vector <int> edge2, int k)
    {
    	int n=edge1.size()+1;
    	for (int i=0;i<=n;i++)
    	{
    		c[i][0]=c[i][i]=1;
    		for (int j=1;j<i;j++) c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
    	}
    	if (k==1) //any permutation is legal
    	{
    		int ans=1;
    		for (int i=2;i<=n;i++) ans=ll(ans)*i%mod;
    		return ans;
    	}
    	if (2*k<=n)
    	{
    		for (int i=0;i<n;i++)
    			for (int j=0;j<n;j++)
    				d[i][j]=n*(i!=j);
    		for (int i=0;i<n-1;i++)
    		{
    			e[edge1[i]].pb(edge2[i]);
    			e[edge2[i]].pb(edge1[i]);
    			d[edge1[i]][edge2[i]]=d[edge2[i]][edge1[i]]=1;
    		}

            //floyd

    		for (int p=0;p<n;p++)
    			for (int i=0;i<n;i++)
    				for (int j=0;j<n;j++)
    					d[i][j]=min(d[i][j],d[i][p]+d[p][j]);


    		memset(v,0,sizeof(v));
    		int ans=0;
    		for (int i=0;i<n;i++)
    			for (int j=0;j<n;j++)
    				if (d[i][j]==n-2*k+1)
    				{
    					dfs1(i,j);dfs1(j,i);
    					if (size[i]==k&&size[j]==k) ans=(ll(g[i])*g[j]+ans)%mod;
    				}
    		return ans;
    	}


    	int ans=0;
    	memset(v,0,sizeof(v));
    	for (int i=0;i<n-1;i++)
    	{
    		e[edge1[i]].pb(edge2[i]);
    		e[edge2[i]].pb(edge1[i]);
    		d[edge1[i]][edge2[i]]=d[edge2[i]][edge1[i]]=1;
    	}
    	for (int i=0;i<n;i++)
    	{
    		memset(dp,0,sizeof(dp));
    		dfs2(i);
    		ans=(ans+dp[i][n-k][n-k])%mod;
    	}
    	for (int i=2;i<2*k-n;i++) ans=ll(ans)*i%mod;
    	return ans;
    }
};
