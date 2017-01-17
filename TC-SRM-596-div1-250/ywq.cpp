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

struct IncrementAndDoubling 
{
    int getMin(vector <int> a)
    {
    	int n=a.size(),ans=0,t=0;
    	for (int i=0;i<n;i++)
    	{
    		int x=a[i],y=-1,z=0;
    		while (x)
    		{
    			if (x&1) z++;
    			x>>=1;y++;
    		}
    		t=max(t,y);ans+=z;
    	}
    	return ans+t;
    }
};
