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

int m1,m2;
int c[60],d[60];
bool g[60][60],v[60];
int pre[60];

int dfs(int k)
{
	for (int j=0;j<m2;j++)
		if (g[k][j]&&!v[j])
		{
			v[j]=1;
			if (pre[j]==-1||dfs(pre[j]))
			{
				pre[j]=k;return 1;
			}
		}
	return 0;
}

struct GearsDiv1 
{
    int getmin(string color, vector <string> graph)
    {
    	int n=color.size();
    	string ss="RGB";
    	int ans=n;
    	for (int u=0;u<3;u++)
    	{
    		int ch=ss[u];
			char ch2;
			if (ch!='R') ch2='R';
			if (ch!='G') ch2='G';
			if (ch!='B') ch2='B';
			m1=m2=0;
			for (int i=0;i<n;i++)
				if (color[i]==ch2)
					c[m1++]=i;
				else if (color[i]!=ch)
					d[m2++]=i;
			for (int i=0;i<m1;i++)
				for (int j=0;j<m2;j++)
					if (graph[c[i]][d[j]]=='Y') g[i][j]=1; else g[i][j]=0;
			for (int i=0;i<m2;i++) pre[i]=-1;
			int tmp=0;
			for (int i=0;i<m1;i++)
			{
				memset(v,0,sizeof(v));
				if (dfs(i)) tmp++;
			}
			ans=min(ans,tmp);
		}
		return ans;
    }
};
