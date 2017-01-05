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

int a[55][26];
bool v[55];
vi ans;

struct StringGame 
{
    vector <int> getWinningStrings(vector <string> S)
    {
    	int n=S.size(),m=S[0].size();
    	for (int i=0;i<n;i++)
    		for (int j=0;j<m;j++)
    			a[i][S[i][j]-'a']++;
    	for (int i=0;i<n;i++)
    	{
    		memset(v,0,sizeof(v));
    		int s=n;
    		while (s>1)
    		{
    			int x=-1;
    			for (int j=0;j<26;j++)
    				if (a[i][j])
    				{
    					bool ok=1,t=0;
    					for (int k=0;k<n;k++)
    					{
    						if (a[i][j]<a[k][j]&&!v[k]) {ok=0;break;}
    						if (a[i][j]>a[k][j]&&!v[k]) t=1;
    					}
    					if (ok&&t) {x=j;break;}
    				}
    			if (x==-1) break;
    			for (int k=0;k<n;k++)
    				if (a[i][x]>a[k][x]&&!v[k]) {s--;v[k]=1;}
    		}
    		if (s==1) ans.pb(i);
    	}
    	return ans;
    }
};
