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

int b[20][2];
int a[1000010],head[1000010],nxt[1000010],c[1000010];
ll g[1000010];

ll calc(ll n,int m)
{
	ll ans=0;
	for (int i=0;i<m;i++) if (g[i]<=n) ans+=(n-g[i])/m+1;
	return ans;
}

struct SparseFactorial 
{
    long long getCount(long long lo, long long hi, long long m)
    {
    	int t=m,p=0;
    	for (int i=2;i*i<=t;i++)
    		if (t%i==0)
    		{
    			b[++p][0]=i;b[p][1]=0;
    			while (t%i==0) {t/=i;b[p][1]++;}
    		}
    	if (t>1) {b[++p][0]=t;b[p][1]=1;}
    	for (int i=0;i<m;i++) a[i]=0;
    	for (int i=1;i<=p;i++)
    	{
    		int m0=1;
    		for (int j=0;j<b[i][1];j++) m0*=b[i][0];
    		for (int j=0;j<b[i][0];j++) head[j]=-1;
    		for (int j=999999;j>=0;j--)
    		{
    			int t=ll(j)*j%b[i][0];
    			nxt[j]=head[t];head[t]=j;
    		}
    		for (int j=0;j<m0;j++)
    		{
    			int p0=head[j%b[i][0]],s=0;c[j]=1000000;
    			while (p0!=-1)
    			{
    				ll x=j-ll(p0)*p0;
    				while (x%b[i][0]==0&&s<b[i][1])
    				{
    					x/=b[i][0];s++;
    				}
    				if (s>=b[i][1]) {c[j]=p0;break;}
    				p0=nxt[p0];
    			}
    		}
    		for (int j=0;j<m;j++) a[j]=max(a[j],c[j%m0]);
    	}
    	for (int i=0;i<m;i++)
    		g[i]=(ll(a[i])*a[i]-i+m)/m*m+i;
    	return calc(hi,m)-calc(lo-1,m);
    }
};
