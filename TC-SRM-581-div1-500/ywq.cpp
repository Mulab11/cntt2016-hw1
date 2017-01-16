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

int d1[310][310],d2[310][310],s1[310],s2[310];
string t1,t2;

struct TreeUnion 
{
    double expectedCycles(vector <string> tree1, vector <string> tree2, int K)
    {
    	if (K==3) return 0.0;
    	t1="";t2="";
    	for (int i=0;i<tree1.size();i++) t1+=tree1[i];
    	for (int i=0;i<tree2.size();i++) t2+=tree2[i];
    	int n1=t1.size(),n2=t2.size();
    	int n=2;
    	for (int i=0;i<n1;i++) if (t1[i]==' ') n++;
    	for (int i=0;i<n;i++)
    		for (int j=0;j<n;j++)
    			d1[i][j]=d2[i][j]=n;
    	for (int i=0;i<n;i++) d1[i][i]=d2[i][i]=0;
    	int p=0,t=0;
    	for (int i=0;i<=n1;i++)
    		if (i==n1||t1[i]==' ')
    		{
    			p++;d1[p][t]=d1[t][p]=1;t=0;
    		}
    		else
    			t=t*10+t1[i]-48;
    	p=t=0;
    	for (int i=0;i<=n2;i++)
    		if (i==n2||t2[i]==' ')
    		{
    			p++;d2[p][t]=d2[t][p]=1;t=0;
    		}
    		else
    			t=t*10+t2[i]-48;
    	for (int k=0;k<n;k++)
    		for (int i=0;i<n;i++)
    			for (int j=0;j<n;j++)
    			{
    				d1[i][j]=min(d1[i][j],d1[i][k]+d1[k][j]);
    				d2[i][j]=min(d2[i][j],d2[i][k]+d2[k][j]);
    			}
  		memset(s1,0,sizeof(s1));memset(s2,0,sizeof(s2));
  		double ans=0;
  		for (int i=0;i<n;i++)
  			for (int j=i+1;j<=n;j++)
  			{
  				s1[d1[i][j]]++;s2[d2[i][j]]+=2;
  			}
  		for (int i=1;i<K-2;i++) ans=ans+double(s1[i])*s2[K-2-i];
  		return ans/n/(n-1);
    }
};
