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

int d[8][2];
ll dp[256];

struct HyperKnight 
{
    long long countCells(int a, int b, int numRows, int numColumns, int k)
    {
    	d[0][0]=a;d[0][1]=b;
    	d[1][0]=b;d[1][1]=a;
    	d[2][0]=-a;d[2][1]=b;
    	d[3][0]=b;d[3][1]=-a;
    	d[4][0]=a;d[4][1]=-b;
    	d[5][0]=-b;d[5][1]=a;
    	d[6][0]=-a;d[6][1]=-b;
    	d[7][0]=-b;d[7][1]=-a;
    	ll ans=0;
    	for (int i=0;i<256;i++)
    	{
    		int x0=0,x1=numRows;
    		int y0=0,y1=numColumns;
    		int s=0;
    		for (int j=0;j<8;j++)
    			if (!(i&(1<<j)))
    			{
    				s++;
    				if (d[j][0]>0) x0=max(x0,d[j][0]); else x1=min(x1,numRows+d[j][0]);
    				if (d[j][1]>0) y0=max(y0,d[j][1]); else y1=min(y1,numColumns+d[j][1]);
    			}
    		dp[i]=ll(max(0,x1-x0))*max(0,y1-y0);
    		for (int j=0;j<i;j++) if ((i&j)==j) dp[i]-=dp[j]; //Inclusion-Exclusion Principle
    		if (s==k) ans+=dp[i];
    	}
    	return ans;
    }
};
