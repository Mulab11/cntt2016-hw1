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

int n;
bool w[55],v[55][55];
int pre[55],q[55];

//Hungarian algorithm

bool dfs(int k)
{
	for (int i=0;i<n;i++)
		if (v[k][i]&&!w[i])
		{
			w[i]=1;
			if (pre[i]==-1||dfs(pre[i]))
			{
				pre[i]=k;return 1;
			}
		}
	return 0;
}

struct Incubator 
{
    int maxMagicalGirls(vector <string> love)
    {
    	n=love.size();
    	for (int i=0;i<n;i++)
    	{
    		int f=1,r=1;q[1]=i;
    		while (f<=r)
    		{
    			for (int j=0;j<n;j++)
    				if (love[q[f]][j]=='Y'&&!v[i][j])
    				{
    					q[++r]=j;v[i][j]=1;
    				}
    			f++;
    		}
    	}
        //v[i][j]=1:node j can be reached from node i(must pass at least one edge)
    	memset(pre,-1,sizeof(pre));int ans=n;
    	for (int i=0;i<n;i++)
    	{
    		memset(w,0,sizeof(w));
    		ans-=dfs(i);
    	}
    	return ans;
    }
};
