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

const int di[5][2]={{1,0},{0,1},{-1,0},{0,-1},{0,0}};

bool a[15][15],b[15][15][15];
int g[15],f[15][15];
int n,m;

bool exist(int x,int y)
{
	return x>=0&&x<n&&y>=0&&y<m;
}

int dfs(int k)
{
	if (k>=n)
	{
		for (int i=0;i<m;i++) if (a[k-1][i]) return n*m+1;
		return 0;
	}
	bool ok[3];ok[0]=ok[1]=ok[2]=0;int t=0;
	for (int i=0;i<m;i++)
		if (a[k-1][i]) {t++;ok[g[i]]=1;}
	if (!t) return dfs(k+1);
	if (ok[0]&&ok[1]) return n*m+1;
	if (ok[0])
	{
		for (int i=0;i<m;i++)
			if (a[k-1][i])
			{
				g[i]=0;
				for (int l=0;l<4;l++)
    			{
    				int x=k+di[l][0],y=i+di[l][1];
    				if (exist(x,y)) a[x][y]^=1;
    			}
    		}
    	return t+dfs(k+1);
    }
    if (ok[1])
	{
		for (int i=0;i<m;i++)
			if (a[k-1][i])
			{
				g[i]=1;
				for (int l=0;l<5;l++)
    			{
    				int x=k+di[l][0],y=i+di[l][1];
    				if (exist(x,y)) a[x][y]^=1;
    			}
    		}
    	return t+dfs(k+1);
    }
    for (int i=k-1;i<n;i++)
    	for (int j=0;j<m;j++)
    		b[k][i][j]=a[i][j];
    for (int j=0;j<m;j++) f[k][j]=g[j];
    for (int i=0;i<m;i++)
		if (a[k-1][i])
		{
			g[i]=0;
			for (int l=0;l<4;l++)
    		{
    			int x=k+di[l][0],y=i+di[l][1];
    			if (exist(x,y)) a[x][y]^=1;
    		}
    	}
    int mi=dfs(k+1);
    for (int i=k-1;i<n;i++)
    	for (int j=0;j<m;j++)
    		a[i][j]=b[k][i][j];
    for (int j=0;j<m;j++) g[j]=f[k][j];
    for (int i=0;i<m;i++)
		if (a[k-1][i])
		{
			g[i]=1;
			for (int l=0;l<5;l++)
    		{
    			int x=k+di[l][0],y=i+di[l][1];
    			if (exist(x,y)) a[x][y]^=1;
    		}
    	}
    return min(mi,dfs(k+1))+t;
}

struct YetAnotherBoardGame 
{
    int minimumMoves(vector <string> board)
    {
    	n=board.size();m=board[0].size();
    	int ans=n*m+1;
    	for (int i=0;i<(1<<m);i++)
    		for (int j=0;j<2;j++)
    		{
    			int t=0;
    			for (int k=0;k<m;k++) g[k]=2;
    			for (int p=0;p<n;p++)
    				for (int q=0;q<m;q++)
    					a[p][q]=(board[p][q]=='W');
    			for (int k=0;k<m;k++)
    				if (i&(1<<k))
    				{
    					g[k]=j;t++;
    					for (int l=0;l<4+j;l++)
    					{
    						int x=di[l][0],y=di[l][1]+k;
    						if (exist(x,y)) a[x][y]^=1;
    					}
    				}
    			ans=min(ans,t+dfs(1));
    		}
    	if (ans>n*m) return -1; else return ans;
    }
};
