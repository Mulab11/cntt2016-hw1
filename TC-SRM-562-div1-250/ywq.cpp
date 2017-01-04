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

ll s[128];

struct PastingPaintingDivOne 
{
    vector<long long> countColors(vector <string> clipboard, int T)
    {
    	int n=clipboard.size(),m=clipboard[0].size();

        //enumerate each grid in the clipboard and count how many grids will be overwritten by this grid

    	for (int i=0;i<n;i++)
    		for (int j=0;j<m;j++)
    			if (clipboard[i][j]!='.')
    			{
    				int x=i-1,y=j-1;
    				while (x>=0&&y>=0)
    				{
    					if (clipboard[x][y]!='.') break;
    					x--;y--;
    				}
    				if (x<0||y<0) s[clipboard[i][j]]+=T; else s[clipboard[i][j]]+=min(T,i-x);
    			}
    	vector<ll> ans;
    	ans.pb(s['R']);
    	ans.pb(s['G']);
    	ans.pb(s['B']);
    	return ans;
    }
};
