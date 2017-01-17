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

struct node
{
	string s;
	int l;
	bool operator <(node a)const {return l<a.l;}
}a[55];

const int mod=1000000007;

int c[55],pow2[17],b[6600],d[1<<16],st[6600],dp[55][6600];
int e[1000000];

struct SimilarNames 
{
    int count(vector <string> names, vector <int> info1, vector <int> info2)
    {
    	int n=names.size(),m=info1.size();
    	for (int i=0;i<n;i++)
    	{
    		a[i+1].s=names[i];a[i+1].l=names[i].size();
    	}
    	sort(a+1,a+n+1);
    	int p=0;
    	for (int i=0;i<n;i++) c[i]=-1;
    	for (int i=0;i<m;i++) if (c[info1[i]]==-1) c[info1[i]]=p++;
    	for (int i=0;i<m;i++) if (c[info2[i]]==-1) c[info2[i]]=p++;
    	pow2[0]=1;for (int i=1;i<=p;i++) pow2[i]=pow2[i-1]<<1;
    	int q=0;
    	for (int i=0;i<pow2[p];i++)
    	{
    		bool ok=1;
    		for (int j=0;j<m;j++) if ((i&pow2[c[info1[j]]])&&!(i&pow2[c[info2[j]]])) {ok=0;break;}
    		if (ok)
    		{
    			b[q]=i;d[i]=q++;
    		}
    		else
    			d[i]=-1;
    	}
    	int cnt=0;
    	for (int i=0;i<q;i++)
    	{
    		st[i]=cnt;
    		for (int j=1;j<q;j++)
    			if ((b[i]&b[j])==0) e[cnt++]=j;
    	}
    	st[q]=cnt;
    	for (int i=0;i<=n;i++)
    	{
    		dp[i][0]=1;
    		for (int j=1;j<q;j++)
    			dp[i][j]=0;
    	}
    	for (int i=n;i;i--)
    	{
    		for (int j=q-1;j>=0;j--)
    			for (int k=0;k<p;k++)
    				if ((!(b[j]&pow2[k]))&&d[b[j]|pow2[k]]!=-1) dp[i][d[b[j]|pow2[k]]]=(dp[i][d[b[j]|pow2[k]]]+dp[i][j])%mod;
    		int k=0;
    		for (int j=i-1;j;j--)
    		{
    			bool ok=1;
    			for (int p=0;p<a[j].l;p++) if (a[i].s[p]!=a[j].s[p]) {ok=0;break;}
    			if (ok) {k=j;break;}
    		}
    		for (int j=q-1;j>=0;j--)
    			for (int l=st[j];l<st[j+1];l++)
    				dp[k][d[b[j]|b[e[l]]]]=(ll(dp[k][j])*dp[i][e[l]]+dp[k][d[b[j]|b[e[l]]]])%mod;
    	}
    	int ans=dp[0][q-1];
    	for (int i=1;i<=n-p;i++) ans=ll(ans)*i%mod;
    	return ans;
    }
};
