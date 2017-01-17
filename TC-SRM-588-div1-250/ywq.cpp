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

pii a[55];
int b[55];

struct GUMIAndSongsDiv1 
{
    int maxSongs(vector <int> duration, vector <int> tone, int T)
    {
    	int n=duration.size();
    	for (int i=0;i<n;i++)
    	{
    		a[i].x=tone[i];a[i].y=duration[i];
    	}
    	sort(a,a+n);
    	int ans=0;
    	for (int i=0;i<n;i++)
    		for (int j=i;j<n;j++)
    		{
    			int m=0;
    			for (int k=i;k<=j;k++) b[m++]=a[k].y;
    			sort(b,b+m);
    			int t=T-a[j].x+a[i].x,s=0;
    			for (int k=0;k<m;k++) if (t>=b[k]) {t-=b[k];s++;} else break;
    			ans=max(ans,s);
    		}
    	return ans;
    }
};
