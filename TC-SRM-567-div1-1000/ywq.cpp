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

map<pair<int,vi>,int> v;
int n,w,cnt,a[55],dp[500000];
char b[12][55];
vi c;

int dfs(int k,vi c)
{
	if (k<0) return 1;
	pair<int,vi> t=mp(k,c);
	if (v[t]) return dp[v[t]];
	v[t]=++cnt;
	for (int i=0;i<w;i++)
	{
		vi d;d.clear();bool ok=1;
		for (int j=0;j<w;j++)
		{
			int x=max(0,a[k]-abs(i-j));
			if (x>c[j])
			{
				if (b[k][j]=='-') ok=0;
				d.pb(x);
			}
			else
			{
				if (b[k][j]=='X') ok=0;
				d.pb(c[j]);
			}
		}
		if (ok) dp[v[t]]=(dp[v[t]]+dfs(k-1,d))%mod;
	}
	return dp[v[t]];
}

struct Mountains 
{
    int countPlacements(vector <int> heights, vector <string> visibility)
    {
    	n=heights.size();
    	for (int i=0;i<n;i++) a[i]=heights[i];
    	w=visibility[0].size();
    	for (int i=0;i<n;i++)
    		for (int j=0;j<w;j++)
    			b[i][j]=visibility[i][j];
    	for (int i=0;i<w;i++) c.pb(0);
    	return dfs(n-1,c);
    }
};
