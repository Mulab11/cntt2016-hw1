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

typedef long long ll;
const int mod=1000000007;

int g[45][45],a[45][45],dp[45],b[45],h[45][45];
vi c[45];

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

struct SweetFruits 
{
    int countTrees(vector <int> sweetness, int maxSweetness)
    {
    	int n=sweetness.size();
    	int m=0;
    	for (int i=0;i<n;i++) if (sweetness[i]!=-1) m++;
    	for (int i=0;i<=n;i++)
    	{
    		h[i][0]=h[i][i]=1;
    		for (int j=1;j<i;j++) h[i][j]=(h[i-1][j]+h[i-1][j-1])%mod;
    	}
    	for (int i=0;i<=m;i++)
    	{
            //matrix-tree theorem
    		memset(g,0,sizeof(g));
    		for (int p=0;p<m-i;p++)
    			for (int q=m;q<n;q++)
    				g[p][q]=g[q][p]=1;
    		for (int p=m-i;p<n;p++)
    			for (int q=p+1;q<n;q++)
    				g[p][q]=g[q][p]=1;
    		memset(a,0,sizeof(a));
    		for (int p=0;p<n;p++)
    			for (int q=p+1;q<n;q++)
    				a[p][q]=a[q][p]=(mod-g[p][q])%mod;
    		for (int p=0;p<n;p++)
    			for (int q=p+1;q<n;q++)
    				if (g[p][q])
    				{
    					a[p][p]++;a[q][q]++;
    				}
    		dp[i]=1;
    		for (int k=0;k<n-1;k++)
    		{
    			for (int p=k;p<n-1;p++)
    				if (a[p][k])
    				{
    					for (int q=k;q<n-1;q++) swap(a[k][q],a[p][q]);
    					break;
    				}
    			dp[i]=ll(dp[i])*a[k][k]%mod;
    			int t=power(a[k][k],mod-2);
    			for (int p=k+1;p<n-1;p++) a[k][p]=ll(a[k][p])*t%mod;
    			for (int p=k+1;p<n-1;p++)
    				for (int q=k+1;q<n-1;q++)
    					a[p][q]=((-ll(a[k][q])*a[p][k]+a[p][q])%mod+mod)%mod;
    		}
    		for (int p=0;p<i;p++) dp[i]=((-ll(dp[p])*h[i][p]+dp[i])%mod+mod)%mod;
            //dp[i] represents how many trees have exactly i truly sweet fruits
    	}
        //meet in the middle
    	int m1=0;
    	for (int i=0;i<n/2;i++) if (sweetness[i]!=-1) b[i]=m1++;
    	for (int i=0;i<(1<<m1);i++)
    	{
    		int s1=0,s2=0;
    		for (int j=0;j<n/2;j++)
    			if (sweetness[j]!=-1&&(i&(1<<b[j]))) {s1++;s2+=sweetness[j];}
    		c[s1].pb(s2);
    	}
    	for (int i=0;i<=m1;i++) sort(c[i].begin(),c[i].end());
    	int m2=0;
    	for (int i=n/2;i<n;i++) if (sweetness[i]!=-1) b[i]=m2++;
    	int ans=0;
    	for (int i=0;i<(1<<m2);i++)
    	{
    		int s1=0,s2=0;
    		for (int j=n/2;j<n;j++) if (sweetness[j]!=-1&&(i&(1<<b[j]))) {s1++;s2+=sweetness[j];}
    		for (int j=0;j<=m1;j++) ans=(ll(dp[s1+j])*(upper_bound(c[j].begin(),c[j].end(),maxSweetness-s2)-c[j].begin())+ans)%mod;
    	}
    	return ans;
    }
};
