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

const int mod=1000000009;

string s1,s2;
int fac[2000],inv[2000];
int dp[2000][2000],sum[2000],b[2000];

int power(int x,int y)
{
	int t=1;
	while (y)
	{
		if (y&1) t=ll(t)*x%mod;
		y>>=1;x=ll(x)*x%mod;
	}
	return t;
}

struct ColorfulBuilding 
{
    int count(vector <string> color1, vector <string> color2, int L)
    {
    	s1="";s2="";
    	for (int i=0;i<color1.size();i++)
    	{
    		s1+=color1[i];s2+=color2[i];
    	}
    	int n=s1.size();
    	fac[0]=1;for (int i=1;i<=n;i++) fac[i]=ll(fac[i-1])*i%mod;
    	inv[n]=power(fac[n],mod-2);for (int i=n;i;i--) inv[i-1]=ll(inv[i])*i%mod;
    	int m=0;
    	for (int i=0;i<n;i++)
    	{
    		b[i]=0;
    		for (int j=0;j<i;j++) if (s1[i]==s1[j]&&s2[i]==s2[j]) {b[i]=b[j];break;}
    		if (!b[i]) b[i]=++m;
    	}
    	sum[1]=1;dp[b[n-1]][1]=1;
    	for (int i=n-2;i>=0;i--)
    	{
    		int x=b[i];
    		for (int j=n-i;j>=1;j--)
    		{
    			int t=dp[x][j];
    			if (j) t=((t+sum[j-1]-dp[x][j-1])%mod+mod)%mod;
    			if (i<n-1) t=ll(t)*fac[n-i-2]%mod*inv[n-i-1]%mod;
    			dp[x][j]=(dp[x][j]+t)%mod;sum[j]=(sum[j]+t)%mod;
    		}
    	}
    	return ll(sum[L])*fac[n-1]%mod;
    }
};
