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
map<int,int> val;
int n,m,ans,b[5000000],a[5000000];

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

void calc1(int x)
{
	if (!val[x]) val[x]=power(26,x-n*m+mod-1);
	if (val[x]!=-1) ans=(ans-val[x]+mod)%mod;
	val[x]=-1;
}

void calc2(int x)
{
	if (!val[x]) val[x]=power(26,x-n*m+mod-1);
	if (val[x]!=-1)
	{
		ans=(ans-val[x]+mod)%mod;
		val[x]=ll(val[x])*26%mod;
		ans=(ans+val[x])%mod;
	}
}

struct CharacterBoard 
{
    int countGenerators(vector <string> fragment, int W, int i0, int j0)
    {
    	n=fragment.size();m=fragment[0].size();
    	ans=ll(power(26,W)-1)*power(26,mod-n*m)%mod*power(25,mod-2)%mod;
    	for (int i=0;i<n;i++)
    		for (int j=0;j<m;j++)
    		{
    			int l1=0,l2=0;
    			for (int p=0;p<i;p++)
    			{
    				ll t1=ll(i-p)*W+j,t2=ll(i-p)*W+j-m;
    				for (int r=1;ll(r)*r<=t1;r++)
    				{
    					for (ll k=t2/r+1;k<=t1/r;k++)
    					{
    						ll t3=ll(k)*r;
    						int q=j-(t3-ll(i-p)*W);
    						if (fragment[i][j]!=fragment[p][q])
    						{
    							if (k<=W) a[++l1]=k;
    							if (r<=W) a[++l1]=r;
    						}
    						else
    						{
    							if (k<=W) b[++l2]=k;
    							if (r<=W) b[++l2]=r;
    						}
    					}
    				}
    			}
    			for (int q=0;q<j;q++)
    			{
    				ll t=j-q;
    				if (fragment[i][q]!=fragment[i][j])
    				{
    					for (int r=1;ll(r)*r<=t;r++)
    						if (t%r==0)
    						{
    							if (t/r<=W) a[++l1]=t/r;
    							if (r<=W) a[++l1]=r; 
    						}
    				}
    				else
    					for (int r=1;ll(r)*r<=t;r++)
    						if (t%r==0)
    						{
    							if (t/r<=W) b[++l2]=t/r;
    							if (r<=W) b[++l2]=r;
    						}
    			}
    			sort(a+1,a+l1+1);sort(b+1,b+l2+1);
    			for (int k=1;k<=l1;k++) if (k==1||a[k]!=a[k-1]) calc1(a[k]);
    			for (int k=1;k<=l2;k++) if (k==1||b[k]!=b[k-1]) calc2(b[k]);	
    		}
    	return ans;
    }
};
