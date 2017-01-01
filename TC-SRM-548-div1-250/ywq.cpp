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

const int inf=1000000000;

struct KingdomAndTrees 
{
    int minLevel(vector <int> heights)
    {
    	int n=heights.size();
        //binary search
    	int l=0,r=inf;
    	while (l<=r)
    	{
    		int mid=(l+r)>>1;
    		int t=max(heights[0]-mid,1);//make the height of the first tree as less as possible
    		bool ok=1;
    		for (int i=1;i<n;i++)
    		{
    			if (heights[i]+mid<=t) {ok=0;break;} //the height of the ith tree can't be higher than the height of the (i-1)th tree
    			t=max(t+1,heights[i]-mid);//make the height of the ith tree as less as possible
    		}
    		if (ok) r=mid-1; else l=mid+1;
    	}
    	return l;
    }	
};
