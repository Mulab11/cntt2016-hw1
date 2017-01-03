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

//a simple bfs problem

bool v[55][1030];
pii q[100010];

struct XorTravelingSalesman 
{
    int maxProfit(vector <int> cityValues, vector <string> roads)
    {
    	int n=cityValues.size();
    	int f=1,r=1;q[1]=mp(0,cityValues[0]);
    	v[0][cityValues[0]]=1;
    	while (f<=r)
    	{
    		int x=q[f].x,y=q[f].y;f++;
    		for (int i=0;i<n;i++)
    			if (roads[x][i]=='Y'&&!v[i][y^cityValues[i]])
    			{
    				q[++r]=mp(i,y^cityValues[i]);
    				v[q[r].x][q[r].y]=1;
    			}
    	}
    	for (int i=1023;i>=0;i--)
    		for (int j=0;j<n;j++)
    			if (v[j][i]) return i;
    }
};
