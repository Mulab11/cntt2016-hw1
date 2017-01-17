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

char a[2510];
int ss[2510],suf[2510];

struct LittleElephantAndRGB 
{
    long long getNumber(vector <string> list, int minGreen)
    {
    	int m=list.size(),n=0;
    	for (int i=0;i<m;i++)
    	{
    		int l=list[i].size();
    		for (int j=0;j<l;j++) a[n++]=list[i][j];
    	}
    	ll ans=0;
    	for (int i=n-1;i>=0;i--)
    	{
    		int s=0,k=0;bool ok=0;
    		for (int j=i;j>=0;j--)
    		{
    			if (a[j]=='G')
    			{
    				s++;
    				if (s==minGreen) {ok=1;k=s;}
    				if (!ok) k=s;
    			}
    			else
    			{
    				s=0;ok=1;
    			}
    			ans+=suf[minGreen-k];
    		}
    		s=0;k=0;ok=0;
    		memset(ss,0,sizeof(ss));
    		for (int j=i;j<n;j++)
    		{
    			if (a[j]=='G')
    			{
    				s++;
    				if (s==minGreen) {ok=1;k=s;}
    				if (!ok) k=s;
    			}
    			else
    			{
    				s=0;ok=1;
    			}
    			ss[k]++;
    		}
    		int t=0;
    		for (int j=n;j>=0;j--)
    		{
    			t+=ss[j];suf[j]+=t;
    		}
    	}
    	return ans;
    }
};
