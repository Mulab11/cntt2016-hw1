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

struct BallsSeparating 
{
    int minOperations(vector <int> red, vector <int> green, vector <int> blue)
    {
    	int n=red.size(),ans=inf;
    	for (int i=0;i<n;i++)
    		for (int j=0;j<n;j++)
    			for (int k=0;k<n;k++)
    				if (i!=j&&i!=k&&j!=k)
    				{
    					int t=0;
    					for (int p=0;p<n;p++)
    						if (p==i)
    							t+=green[p]+blue[p];
    						else
    							if (p==j)
    								t+=red[p]+blue[p];
    							else
    								if (p==k)
    									t+=red[p]+green[p];
    								else
    									t+=red[p]+green[p]+blue[p]-max(max(red[p],blue[p]),green[p]);
    					ans=min(ans,t);
    				}
    	if (ans==inf) return -1; else return ans;
    }
};
