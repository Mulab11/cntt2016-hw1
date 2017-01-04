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

const int di[4][2]={{1,0},{0,1},{-1,0},{0,-1}};
const int mod=1000000009;

int n,m;
int pow2[1610],q[1610][2],q2[2560010],head[2560010];
bool v[45][45],v2[2560010],g[45][45];

struct CoinsGame 
{
    int ways(vector <string> board)
    {
    	n=board.size();m=board[0].size();
    	pow2[0]=1;for (int i=1;i<=n*m;i++) pow2[i]=pow2[i-1]*2%mod;
    	int s0=0;
    	for (int i=0;i<n;i++) for (int j=0;j<m;j++) if (board[i][j]=='.') s0++;
    	int f=1,r=0;
    	for (int i=0;i<n;i++)
    		for (int j=0;j<m;j++)
    			if ((i==0||j==0||i==n-1||j==m-1)&&board[i][j]=='.')
    			{
    				q[++r][0]=i;q[r][1]=j;
    				v[i][j]=1;
    			}
    	while (f<=r)
    	{
    		int x=q[f][0],y=q[f][1];f++;
    		for (int k=0;k<4;k++)
    		{
    			int tx=x+di[k][0],ty=y+di[k][1];
    			if (tx>=0&&tx<n&&ty>=0&&ty<m&&board[tx][ty]=='.'&&!v[tx][ty])
    			{
    				q[++r][0]=tx;q[r][1]=ty;
    				v[tx][ty]=1;
    			}
    		}
    	}

        //v[i][j]=1:grid(i,j) can be reached from the border

    	int ans=(pow2[s0]-pow2[s0-r]+mod)%mod;
    	f=1;r=0;
    	for (int i=0;i<n;i++)
    		for (int j=0;j<m;j++)
    			if (v[i][j])
    				for (int x=0;x<n;x++)
    					for (int y=0;y<m;y++)
    						if (v[x][y])
    						{
    							int t=((i*m+j)*n+x)*m+y;
    							if (((i==0)^(x==0))||((i==n-1)^(x==n-1))||((j==0)^(y==0))||((j==m-1)^(y==m-1)))
    							{
                                    //one coin in grid(i,j) and one coin in grid(p,q),after we push the button,one falls off the board while the other one doesn't
    								q2[++r]=t;v2[t]=1;
    							}
    						}
    	while (f<=r)
    	{
    		int t=q2[f++];
    		int y=t%m;t/=m;
    		int x=t%n;t/=n;
    		int j=t%m;t/=m;
    		int i=t;
    		for (int k=0;k<4;k++)
    		{
    			int ti=i+di[k][0],tj=j+di[k][1],tx=x+di[k][0],ty=y+di[k][1];
    			if (ti>=0&&ti<n&&tj>=0&&tj<m&&tx>=0&&tx<n&&ty>=0&&ty<m&&board[ti][tj]=='.'&&board[tx][ty]=='.')
    			{
    				int t0=((ti*m+tj)*n+tx)*m+ty;
    				if (!v2[t0]) {q2[++r]=t0;v2[t0]=1;}
    			}
    			ti=i-di[k][0];tj=j-di[k][1];
    			if (ti>=0&&ti<n&&tj>=0&&tj<m&&tx>=0&&tx<n&&ty>=0&&ty<m&&board[ti][tj]=='#'&&board[tx][ty]=='.')
    			{
    				int t0=((i*m+j)*n+tx)*m+ty;
    				if (!v2[t0]) {q2[++r]=t0;v2[t0]=1;}
    			}
    			ti=i+di[k][0];tj=j+di[k][1];tx=x-di[k][0];ty=y-di[k][1];
    			if (ti>=0&&ti<n&&tj>=0&&tj<m&&tx>=0&&tx<n&&ty>=0&&ty<m&&board[ti][tj]=='.'&&board[tx][ty]=='#')
    			{
    				int t0=((ti*m+tj)*n+x)*m+y;
    				if (!v2[t0]) {q2[++r]=t0;v2[t0]=1;}
    			}
    		}
    	}
    	for (int i=0;i<n;i++)
    		for (int j=0;j<m;j++)
    			if (v[i][j]&&(!g[i][j]))
    			{
    				int s=0;
    				for (int x=0;x<n;x++)
    					for (int y=0;y<m;y++)
    						if (v[x][y]&&!v2[((i*m+j)*n+x)*m+y]) {g[x][y]=1;s++;}
    				ans=(ans-pow2[s]+1+mod)%mod;
    			}
    	return ans;
    }
};
