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

int n,m,g[55][55],color[110];

bool dfs(int k)
{
	if (k<n)
	{
		for (int i=0;i<m;i++)
			if (g[k][i]!=2)
			{
				if (color[i+n]==2)
				{
					color[i+n]=color[k]^g[k][i];
					if (!dfs(i+n)) return 0;
				}
				else
					if (color[i+n]!=(color[k]^g[k][i])) return 0;
			}
	}
	else
		for (int i=0;i<n;i++)
			if (g[i][k-n]!=2)
			{
				if (color[i]==2)
				{
					color[i]=color[k]^g[i][k-n];
					if (!dfs(i)) return 0;
				}
				else
					if (color[i]!=(color[k]^g[i][k-n])) return 0;
			}
	return 1;
}

bool check()
{
	for (int i=0;i<n+m;i++) color[i]=2;
	for (int i=0;i<n;i++)
		if (color[i]==2)
		{
			color[i]=0;
			if (!dfs(i)) return 0;
		}
	return 1;
}

struct ThreeColorability 
{
    vector <string> lexSmallest(vector <string> cells)
    {
    	n=cells.size();m=cells[0].size();
    	for (int i=0;i<n;i++)
    		for (int j=0;j<m;j++)
    		{
    			if (cells[i][j]=='N') g[i][j]=0;
    			if (cells[i][j]=='Z') g[i][j]=1;
    			if (cells[i][j]=='?') g[i][j]=2;
    		}
    	if (!check()) {vector<string> ans;return ans;}
    	for (int i=0;i<n;i++)
    		for (int j=0;j<m;j++)
    			if (g[i][j]==2)
    			{
    				g[i][j]=0;
    				if (!check()) g[i][j]=1;
    			}
    	for (int i=0;i<n;i++)
    		for (int j=0;j<m;j++)
    			if (g[i][j]) cells[i][j]='Z'; else cells[i][j]='N';
    	return cells;
    }
};
