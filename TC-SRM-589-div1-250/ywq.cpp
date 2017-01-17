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

bool g[26][26];
int a[26],q[30];
bool v[26];

struct GooseTattarrattatDiv1 
{
    int getmin(string S)
    {
    	int n=S.size();
    	for (int i=0;i<n/2;i++)
    		g[S[i]-97][S[n-1-i]-97]=g[S[n-1-i]-97][S[i]-97]=1;
    	int ans=n;
    	for (int i=0;i<n;i++) a[S[i]-97]++;
    	for (int i=0;i<26;i++)
    		if (!v[i])
    		{
    			int f=1,r=1;q[1]=i;v[i]=1;
    			while (f<=r)
    			{
    				for (int j=0;j<26;j++)
    					if (g[q[f]][j]&&!v[j])
    					{
    						q[++r]=j;v[j]=1;
    					}
    				f++;
    			}
    			int ma=0;
    			for (int j=1;j<=r;j++) ma=max(ma,a[q[j]]);
    			ans-=ma;
    		}
    	return ans;
    }
};
