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

int n;

struct array0
{
	int d[355];
}a,b,c;

int dp[355],dp2[355];

array0 operator *(array0 a,array0 b) //circular convolution
{
	for (int i=0;i<n;i++) c.d[i]=0;
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			c.d[(i+j)%n]=(ll(a.d[i])*b.d[j]+c.d[(i+j)%n])%mod;
	return c;
}

struct PenguinEmperor 
{
    int countJourneys(int numCities, long long daysPassed)
    {
    	dp[0]=1;n=numCities;
   		for (int i=1;i<=n;i++)
   		{
   			for (int j=0;j<n;j++) {dp2[j]=dp[j];dp[j]=0;}
   			for (int j=0;j<n;j++)
   				if (dp2[j])
   				{
   					dp[(j+i)%n]=(dp[(j+i)%n]+dp2[j])%mod;
   					if (i*2!=n&&i!=n) dp[(j-i+n)%n]=(dp[(j-i+n)%n]+dp2[j])%mod;
   				}
   		}
   		for (int i=0;i<n;i++) a.d[i]=dp[i];
   		for (int i=0;i<n;i++) b.d[i]=(i==0);
   		ll t=daysPassed/n;
   		while (t)
   		{
   			if (t&1) b=b*a;
   			a=a*a;t>>=1;
   		}
   		for (int i=0;i<n;i++) dp[i]=b.d[i];
   		for (int i=1;i<=daysPassed%n;i++)
   		{
   			for (int j=0;j<n;j++) {dp2[j]=dp[j];dp[j]=0;}
   			for (int j=0;j<n;j++)
   				if (dp2[j])
   				{
   					dp[(j+i)%n]=(dp[(j+i)%n]+dp2[j])%mod;
   					if (i*2!=n) dp[(j-i+n)%n]=(dp[(j-i+n)%n]+dp2[j])%mod;
   				}
   		}
   		return dp[0];
    }
};
