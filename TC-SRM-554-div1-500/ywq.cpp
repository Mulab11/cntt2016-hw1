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

pii b[55];
bool ok[55];

struct TheBrickTowerMediumDivOne 
{
    vector <int> find(vector <int> heights)
    {
    	int n=heights.size();
    	vi ans;ans.pb(0);
    	int k=0;ok[k]=1;
    	while (1)
    	{
    		int p=k+1;
    		while (p<n&&heights[p]>heights[k]) p++;
    		if (p==n) break;
    		ans.pb(p);ok[p]=1;k=p;
    	}
        //arrange the rest in non-decreasing order
    	int m=0;
    	for (int i=0;i<n;i++) if (!ok[i]) b[m++]=mp(heights[i],i);
    	sort(b,b+m);
    	for (int i=0;i<m;i++) ans.pb(b[i].y);
    	return ans;
    }
};
