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

const long double eps=1e-10;

long double dis(long double x1,long double y1,long double x2,long double y2)
{
	long double d=(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
	if (d<0) return 0; else return sqrt(d);
}

long double low[55],high[55];

struct CandyOnDisk 
{
    string ableToAchieve(vector <int> x, vector <int> y, vector <int> r, int sx, int sy, int tx, int ty)
    {
    	if (sx==tx&&sy==ty) return "YES";
    	int n=x.size();
    	for (int i=0;i<n;i++)
    	{
    		low[i]=r[i];high[i]=0;
    		long double d=dis(x[i],y[i],sx,sy);
    		if (d-eps<=r[i]) low[i]=high[i]=d;
    	}
    	for (int T=0;T<n*n;T++)
    		for (int i=0;i<n;i++)
    			if (low[i]<high[i]+eps)
    				for (int j=0;j<n;j++)
    				{
    					if (x[i]==x[j]&&y[i]==y[j])
    					{
    						if (low[i]<r[j]+eps)
    						{
    							low[j]=min(low[j],low[i]);
    							high[j]=max(high[j],min(high[i],(long double)(r[j])));
    						}
    						continue;
    					}
    					long double d=dis(x[i],y[i],x[j],y[j]);
    					if (!(d-high[i]>r[j]+eps||d+r[j]+eps<low[i]))
    					{
    						low[j]=min(low[j],max((long double)0.0,d-r[i]));
    						high[j]=max(high[j],min((long double)(r[j]),d+r[i]));
    					}
    				}
    	for (int i=0;i<n;i++)
    	{
    		long double d=dis(x[i],y[i],tx,ty);
    		if (low[i]<d+eps&&d<high[i]+eps) return "YES";
    	}
    	return "NO";
    }
};
