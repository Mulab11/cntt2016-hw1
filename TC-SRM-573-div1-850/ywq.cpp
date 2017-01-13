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

const int mod=1000000007;

int n,fac[100010],inv[100010];

int power(int x,int y)
{
	int t=1;
	while (y)
	{
		if (y&1) t=ll(t)*x%mod;
		x=ll(x)*x%mod;y>>=1;
	}
	return t;
}

int c(int n,int m)
{
	return ll(fac[n])*inv[m]%mod*inv[n-m]%mod;
}

int solve(vi x,int m)
{
	int ans=0;
	for (int i=x[0]-m;i<=x[0]+m;i++)
	{
		int t=1;
		for (int j=0;j<n;j++)
		{
			if ((x[j]-i+m)&1) {t=0;break;}
			int p=(x[j]-i+m)/2;
			if (p<0||p>m) {t=0;break;}
			t=ll(t)*c(m,p)%mod;
		}
		ans=(ans+t)%mod;
	}
	return ans;
}

struct WolfPack 
{
    int calc(vector <int> x, vector <int> y, int m)
    {
    	n=x.size();
    	for (int i=0;i<n;i++)
    	{
    		int p=x[i]+y[i],q=x[i]-y[i];
    		x[i]=p;y[i]=q;
    	}
    	fac[0]=1;for (int i=1;i<=m;i++) fac[i]=ll(fac[i-1])*i%mod;
    	inv[m]=power(fac[m],mod-2);
    	for (int i=m;i;i--) inv[i-1]=ll(inv[i])*i%mod;
    	return ll(solve(x,m))*solve(y,m)%mod;
    }
};
