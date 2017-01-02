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

struct CheckerExpansion 
{
    vector <string> resultAfter(long long t, long long x0, long long y0, int w, int h)
    {
    	vector<string> ans;
    	for (int j=h-1;j>=0;j--)
    	{
    		string s="";
    		for (int i=0;i<w;i++)
    		{
    			ll x=x0+i,y=y0+j;
    			if ((x+y)&1) {s+='.';continue;}
    			if (x+y>(t-1)*2) {s+='.';continue;}
    			if ((((x+y)/2)&y)==y) //C((x+y)/2,y) is odd
    			{
    				if ((x+y)&2) s+='B'; else s+='A';
    			}
    			else
    				s+='.';
    		}
    		ans.pb(s);
    	}
    	return ans;
    }
};
