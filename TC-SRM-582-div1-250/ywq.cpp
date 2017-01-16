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

const ll inf=1000000000000000000ll;

int a[55];
pair<int,ll> b[55];
ll c[55];

struct SpaceWarDiv1 
{
    long long minimalFatigue(vector <int> magicalGirlStrength, vector <int> enemyStrength, vector<long long> enemyCount)
    {
    	int n=magicalGirlStrength.size(),m=enemyCount.size();
    	for (int i=0;i<n;i++) a[i]=magicalGirlStrength[i];
    	for (int i=0;i<m;i++) b[i]=mp(enemyStrength[i],enemyCount[i]);
    	sort(a,a+n);sort(b,b+m);
    	if (a[n-1]<b[m-1].x) return -1;
    	ll l=1,r=inf;
    	while (l<=r)
    	{
    		ll mid=(l+r)>>1;
    		for (int i=0;i<m;i++) c[i]=b[i].y;
    		int k=m-1;bool ok=0;
    		for (int i=n-1;i>=0;i--)
    		{
    			if (b[k].x>a[i]) break;
    			ll res=mid;
    			while (res&&k>=0)
    			{
    				ll t=min(res,c[k]);
    				res-=t;c[k]-=t;
    				if (!c[k]) k--;
    			}
    			if (k<0) {ok=1;break;}
    		}
    		if (ok) r=mid-1; else l=mid+1;
    	}
    	return l;
    }
};
