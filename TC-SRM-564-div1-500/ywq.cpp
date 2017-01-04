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

struct AlternateColors2 
{
    long long countWays(int n, int k)
    {
    	ll ans=0;
    	for (int i=1;i<=n;i++) //enumerate the number of red balls
    	{
    		int t=n-i;
    		if (k%3==1&&k/3+1<=i) ans+=max(0,t-(k/3+1)*2+1);
    		if (i+k>n)
    		{
    			int x=i+k-n;
    			ans+=max(0,min(t+1,x)-max(t-x,-1)-1);
    		}
    	}
    	if (k!=n)
    		for (int i=0;i<=n/3;i++)
    		{
    			int t=i*3;
    			if (k<=t) break;
    			t=k-t;
    			if (t%2==0) continue;
    			int x=n-k-1;
    			ans+=(x+1)*2;
    		}
    	return ans;
    }
};
