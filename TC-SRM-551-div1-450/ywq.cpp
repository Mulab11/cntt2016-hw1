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
int d[55];

struct ColorfulWolves 
{
    int getmin(vector <string> colormap)
    {
    	int n=colormap.size();
    	for (int i=0;i<n;i++) d[i]=n*n;d[0]=0;
        //dijkstra
    	while (1)
    	{
    		int mi=n*n,j;
    		for (int i=0;i<n;i++) if (d[i]<mi&&!v[i]) {j=i;mi=d[i];}
    		if (mi==n*n) return -1;
    		if (j==n-1) return mi;
    		v[j]=1;int s=0;
    		for (int i=0;i<n;i++)
    			if (colormap[j][i]=='Y') d[i]=min(d[i],mi+(s++));
    	}
    }
};
