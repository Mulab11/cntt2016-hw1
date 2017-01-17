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
char a[55][55];

int dfs(int k,int fa)
{
	int s=0,x=0;
	for (int i=0;i<n;i++)
		if (i!=fa&&a[i][k]=='Y')
		{
			int t=dfs(i,k);
			if (!t) x++; else s+=t;
		}
	return s+max(x-1,0);
}

struct TPS
{
    int minimalBeacons(vector <string> linked)
    {
    	n=linked.size();
    	for (int i=0;i<n;i++)
    		for (int j=0;j<n;j++)
    			a[i][j]=linked[i][j];
    	if (n==1) return 0;
    	int ans=n;
    	for (int i=0;i<n;i++) ans=min(ans,dfs(i,-1));
    	return ans+1;
    }
};
