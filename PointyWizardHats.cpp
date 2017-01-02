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

int n,m,pre[55];
bool g[55][55],v[55];

//Hungary algorithm
int dfs(int k)
{
	for (int i=0;i<m;i++)
		if (g[k][i]&&!v[i])
		{
			v[i]=1;
			if (pre[i]==-1||dfs(pre[i]))
			{
				pre[i]=k;return 1;
			}
		}
	return 0;
}

struct PointyWizardHats 
{
    int getNumHats(vector <int> topHeight, vector <int> topRadius, vector <int> bottomHeight, vector <int> bottomRadius)
    {
    	n=topHeight.size();m=bottomHeight.size();
    	for (int i=0;i<n;i++)
    		for (int j=0;j<m;j++)
    			if (topRadius[i]<bottomRadius[j]&&topHeight[i]*bottomRadius[j]>bottomHeight[j]*topRadius[i]) g[i][j]=1;//the ith top cone can match the jth bottom cone
    	memset(pre,-1,sizeof(pre));
    	int ans=0;
    	for (int i=0;i<n;i++)
    	{
    		memset(v,0,sizeof(v));
    		ans+=dfs(i);
    	}
    	return ans;
    }
};
