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

bool v[55];
int q[55],cnt[1<<7];

struct NewArenaPassword 
{
    int minChange(string oldPassword, int K)
    {
    	int n=oldPassword.size();
    	int ans=0;
    	for (int i=0;i<n;i++)
    		if (!v[i])
    		{
    			int f=1,r=1;q[1]=i;v[i]=1;
    			while (f<=r)
    			{
    				if (q[f]<K)
    				{
    					int x=n-K+q[f];
    					if (!v[x]) {v[x]=1;q[++r]=x;}
    				}
    				if (q[f]+K>=n)
    				{
    					int x=q[f]-(n-K);
    					if (!v[x]) {v[x]=1;q[++r]=x;}
    				}
    				f++;
    			}
    			memset(cnt,0,sizeof(cnt));
    			for (int j=1;j<=r;j++) cnt[oldPassword[q[j]]]++;
    			int ma=0;
    			for (int j='a';j<='z';j++) ma=max(ma,cnt[j]);
    			ans+=r-ma;
    		}
    	return ans;
    }
};
