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

const int N=40000;

bool nprime[N+10];
int a[N+10];
int now[1000010],g[1000010],s[100];

struct TheDivisionGame 
{
    long long countWinningIntervals(int L, int R)
    {
    	ll ans=0;int cnt=0;
    	for (int i=0;i<=R-L;i++) now[i]=i+L;

        //sieve of Euler

    	for (int i=2;i<=N;i++)
    	{
    		if (!nprime[i])
    		{
    			a[++cnt]=i;
    			for (int j=(L-1)/i+1;j<=R/i;j++)
    			{
    				int t=j*i-L;
    				while (now[t]%i==0)
    				{
    					g[t]++;now[t]/=i;
    				}
    			}
    		}
    		for (int j=1;j<=cnt;j++)
    		{
    			if (i*a[j]>N) break;
    			nprime[i*a[j]]=1;
    			if (i%a[j]==0) break;
    		}
    	}
    	s[0]=1;int t=0;
    	for (int i=0;i<=R-L;i++)
    	{
    		if (now[i]>1) g[i]++;
    		t^=g[i];
    		ans+=s[t];s[t]++;
    	}
    	return ll(R-L+2)*(R-L+1)/2-ans;
    }
};
