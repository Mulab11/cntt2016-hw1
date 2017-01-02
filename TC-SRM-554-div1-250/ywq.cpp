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

map<pair<int,ll>,ll> dp;
int n,a[300010];
bool nprime[1000010];

ll dfs(int k,ll x)
{
	if (k>n) return 1;
	if (x<a[k]) return 1;
	if (ll(a[k])*a[k]>x) //we can arrange at most one prime
	{
		int l=k,r=n;
		while (l<=r)
		{
			int mid=(l+r)>>1;
			if (a[mid]<=x) l=mid+1; else r=mid-1;
		}
		return l-k+1;
	}
	ll s=dfs(k+1,x);
	x/=a[k];
	while (x)
	{
		s+=dfs(k+1,x);
		x=x/a[k]/a[k];
	}
	return s;
}

struct HolyNumbers 
{
    long long count(long long upTo, int maximalPrime)
    {
    	n=0;
    	//Euler's Sieve
    	for (int i=2;i<=maximalPrime;i++)
    	{
    		if (!nprime[i]) a[++n]=i;
    		for (int j=1;j<=n;j++)
    		{
    			if (i*a[j]>maximalPrime) break;
    			nprime[i*a[j]]=1;
    			if (i%a[j]==0) break;
    		}
    	}
    	return dfs(1,upTo);
    }
};
