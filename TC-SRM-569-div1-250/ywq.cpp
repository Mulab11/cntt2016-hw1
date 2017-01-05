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

struct TheDevice 
{
    int minimumAdditional(vector <string> plates)
    {
    	int n=plates.size(),m=plates[0].size();
    	int ans=0;
    	for (int i=0;i<m;i++)
    	{
    		int x=0,y=0;
    		for (int j=0;j<n;j++) if (plates[j][i]=='0') x++; else y++;
    		ans=max(ans,max(0,1-x)+max(0,2-y));
    	}
    	return ans;
    }
};
