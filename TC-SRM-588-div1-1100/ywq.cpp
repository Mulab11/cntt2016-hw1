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

int n,m;
char g[55][55];
int d[2][55][55];
int q[2510][2];
bool v[55][55];

bool dfs(int x,int y,int d)
{
	if (d>=3) return 1;
	v[x][y]=1;
	for (int k=0;k<4;k++)
	{
		int tx=x+di[k][0],ty=y+di[k][1];
		if (tx>=0&&tx<n&&ty>=0&&ty<m&&g[tx][ty]!='#'&&!v[tx][ty])
			if (dfs(tx,ty,d+1)) {v[x][y]=0;return 1;}
	}
	v[x][y]=0;
	return 0;
}

struct GameInDarknessDiv1 
{
    string check(vector <string> field)
    {
    	n=field.size();m=field[0].size();
    	for (int i=0;i<n;i++)
    		for (int j=0;j<m;j++)
    			g[i][j]=field[i][j];
    	for (int i=0;i<n;i++)
    		for (int j=0;j<m;j++)
    			if (field[i][j]=='A'||field[i][j]=='B')
    			{
    				int t=field[i][j]-'A';
    				for (int p=0;p<n;p++)
    					for (int q=0;q<m;q++)
    						d[t][p][q]=n*m;
    				d[t][i][j]=0;
    				int f=1,r=1;q[1][0]=i;q[1][1]=j;
    				while (f<=r)
    				{
    					for (int k=0;k<4;k++)
    					{
    						int tx=q[f][0]+di[k][0],ty=q[f][1]+di[k][1];
    						if (tx>=0&&tx<n&&ty>=0&&ty<m&&field[tx][ty]!='#'&&d[t][tx][ty]==n*m)
    						{
    							q[++r][0]=tx;q[r][1]=ty;
    							d[t][tx][ty]=d[t][q[f][0]][q[f][1]]+1;
    						}
    					}
    					f++;
    				}
    			}
    	for (int i=0;i<n;i++)
    		for (int j=0;j<m;j++)
    			if (d[0][i][j]-d[1][i][j]>=2&&field[i][j]!='#')
    			{
    				v[i][j]=1;int s=0;
    				for (int k=0;k<4;k++)
   					{
    					int tx=i+di[k][0],ty=j+di[k][1];
    					if (tx>=0&&tx<n&&ty>=0&&ty<m&&field[tx][ty]!='#')
    					{
    						if (dfs(tx,ty,1)) s++;
    					}
    				}
    				if (s>=3) return "Bob wins";
    				v[i][j]=0;
    			}
    	return "Alice wins";
    }
};
