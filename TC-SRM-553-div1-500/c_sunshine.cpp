#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
const int M=1000000007;
inline void up(int &x,const int &y)
{x+=y;if(x>=M)x-=M;}
class TwoConvexShapes
{
	public:
	char s[55][55];
	int n,m;
	int can[55][55],f[55][55],g[55][55];
	
	int cc(char *a,char *b,char c)
	{int res=0;for(;a<=b;a++)res+=(*a==c);return res;}
	
	int dp()
	{
		//can[i][j] : if it is valid to paint first j cells black and the other cells white in i-th row.
		for(int i=1;i<=n;i++)
			for(int j=0;j<=m;j++)
				can[i][j]=cc(s[i]+1,s[i]+j,'W')==0&&cc(s[i]+j+1,s[i]+m,'B')==0;
		memset(f,0,sizeof(f));
		memset(g,0,sizeof(g));
		f[0][0]=1;
		g[0][m]=1;
		//f/g[i][j]: the number of ways to paint first rows, and i-th row's first j cells are black.
		//j must be increasing for f and decreasing for g.
		for(int i=0;i<n;i++)
			for(int j=0;j<=m;j++)
				for(int k=0;k<=m;k++)
					if(can[i+1][k])
					{
						if(k>=j)up(f[i+1][k],f[i][j]);
						if(k<=j)up(g[i+1][k],g[i][j]);
					}
		int res=0;
		for(int j=0;j<=m;j++)
		{
			if(can[n][j])up(res,f[n][j]),up(res,g[n][j]);
			//Sometimes we can place all break points at j-th column, that may be counted twice.
			res--;
			for(int i=1;i<=n;i++)
				if(!can[i][j]){res++;break;}
		}
		return (res+M)%M;
	}
	
	int countWays(vector<string> grid)
	{
		n=grid.size(),m=grid[0].size();
		int ans=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				s[i][j]=grid[i-1][j-1];
		up(ans,dp());
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				s[i][j]=grid[i-1][m-j];
		up(ans,dp());
		for(int i=0;i<n;i++)
		{
			//Sometimes we can paint first i rows black and the other rows white, that may be counted twice.
			ans--;
			for(int k=1;k<=n;k++)
				if(k<=i&&!can[k][m]||k>i&&!can[k][0]){ans++;break;}
			//Sometimes we can paint first i rows white and the other rows black, that may be counted twice.
			ans--;
			for(int k=1;k<=n;k++)
				if(k<=i&&!can[k][0]||k>i&&!can[k][m]){ans++;break;}
		}
		return ans;
	}
	
};

