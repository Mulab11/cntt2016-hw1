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

struct TheTree 
{
    int maximumDiameter(vector <int> cnt)
    {
    	int n=cnt.size();
    	int k=n,ans=0;
    	while (k)
    	{
    		while (k&&cnt[k-1]==1) k--;
    		int p=k;
    		while (p&&cnt[p-1]!=1) p--;
    		ans=max(ans,n+k-2*p);
    		k=p;
    	}
    	return ans;
    }
};
