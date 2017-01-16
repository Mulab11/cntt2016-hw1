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

string s1,s2;
int l[310],r[310],s[10000000],mi[310],f[310][310],ss[310];
int n;

int g(int x,int y,int z)
{
	return ss[x]+(z-x)*(z-x+1)/2+y-x;
}

struct WolfInZooDivOne 
{
    int count(int N, vector <string> L, vector <string> R)
    {
    	n=N;
    	s1="";s2="";
    	for (int i=0;i<L.size();i++) s1+=L[i];
    	for (int i=0;i<R.size();i++) s2+=R[i];
    	int l1=s1.size(),l2=s2.size();
    	int m=0,d=0;
    	for (int i=0;i<=l1;i++)
    		if (i==l1||s1[i]==' ')
    		{
    			l[m++]=d;d=0;
    		}
    		else
    			d=d*10+s1[i]-'0';
    	m=d=0;
    	for (int i=0;i<=l2;i++)
    		if (i==l2||s2[i]==' ')
    		{
    			r[m++]=d;d=0;
    		}
    		else
    			d=d*10+s2[i]-'0';
    	for (int i=0;i<=n;i++) mi[i]=n+1;
    	for (int i=0;i<m;i++) mi[r[i]+1]=min(mi[r[i]+1],l[i]+1);
    	for (int i=0;i<=n;i++)
    	{
    		f[i][i]=mi[i];
    		for (int j=i+1;j<=n;j++) f[i][j]=min(f[i][j-1],mi[j]);
    	}
    	ss[0]=0;for (int i=1;i<=n;i++) ss[i]=ss[i-1]+(n-i+3)*(n-i+2)/2;
    	s[0]=1;
    	for (int i=1;i<=n;i++)
    		for (int j=0;j<i;j++)
    		{
    			int t=0;
    			for (int k=0;k<=j;k++)
    			{
    				t=(t+s[g(min(k,f[j][i-1]-1),k,j)])%mod;
    				s[g(k,j,i)]=t;
    			}
    		}
    	int ans=0;
    	for (int i=0;i<=n;i++)
    		for (int j=0;j<=i;j++)
    			ans=(ans+s[g(min(f[i][n]-1,j),j,i)])%mod;
    	return ans;
    }
};
