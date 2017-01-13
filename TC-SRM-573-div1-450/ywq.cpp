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

const ll inf=1000000000000000ll;

ll d[55][55];
bool v[55][55];

struct SkiResorts 
{
    long long minCost(vector <string> road, vector <int> altitude)
    {
    	int n=road.size();
    	for (int i=1;i<n;i++)
    		for (int j=0;j<n;j++)
    			d[i][j]=inf;
    	for (int j=0;j<n;j++) d[0][j]=abs(altitude[0]-altitude[j]);
    	memset(v,0,sizeof(v));
    	while (1)
    	{
    		ll mi=inf;int p,q;
    		for (int i=0;i<n;i++)
    			for (int j=0;j<n;j++)
    				if (d[i][j]<mi&&!v[i][j])
    				{
    					mi=d[i][j];p=i;q=j;
    				}
    		if (mi==inf) return -1;
    		if (p==n-1) return mi;
    		v[p][q]=1;
    		for (int i=0;i<n;i++)
    			for (int j=0;j<n;j++)
    				if (road[p][i]=='Y'&&altitude[q]>=altitude[j]) d[i][j]=min(d[i][j],mi+abs(altitude[i]-altitude[j]));
    	}
    }
};
