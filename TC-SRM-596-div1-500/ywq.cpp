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

vector<ll> b;
bool ok[65][65];
ll ans[65];
int s[65];

struct BitwiseAnd 
{
    vector<long long> lexSmallest(vector<long long> a, int n)
    {
    	int m=a.size();b.clear();
    	for (int i=0;i<m;i++)
    		for (int j=i+1;j<m;j++)
    			if (!(a[i]&a[j])) return b;
    	for (int i=0;i<m;i++)
    		for (int j=i+1;j<m;j++)
    			for (int k=j+1;k<m;k++)
    				if (a[i]&a[j]&a[k]) return b;
    	for (int i=0;i<m;i++)
    	{
    		ll t=a[i];
    		for (int j=0;j<60;j++)
    		{
    			if (t&1) {s[j]++;ok[i][j]=1;}
    			t>>=1;
    		}
    	}
    	for (int i=0;i<m;i++)
    	{
    		int k=m;
    		for (int j=0;j<60;j++) if (ok[i][j]&&s[j]==1) {ans[k++]|=(1ll<<j);if (k>=n) break;}
    		if (k<n) return b;
    	}
    	int x=m,y=m+1;
    	for (int i=0;i<60;i++)
    		if (s[i]==0&&x<n-1)
    		{
    			ans[x]|=(1ll<<i);ans[y]|=(1ll<<i);
    			y++;if (y>=n) {x++;y=x+1;}
    			if (x>=n-1) break;
    		}
    	if (x<n-1) return b;
    	for (int i=0;i<m;i++) ans[i]=a[i];
    	for (int i=0;i<n;i++) b.pb(ans[i]);
    	sort(b.begin(),b.end());
    	return b;
    }
};
