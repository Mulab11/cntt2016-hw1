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

ll f[55][110];

//a simple dp problem

struct MonstersValley 
{
    int minimumPrice(vector<long long> dread, vector <int> price)
    {
    	int n=dread.size();
    	for (int i=0;i<=n;i++)
    		for (int j=0;j<=2*n;j++)
    			f[i][j]=-1;
    	f[0][0]=0;
    	for (int i=0;i<n;i++)
    		for (int j=0;j<=2*n;j++)
    			if (f[i][j]>=0)
    			{
    				f[i+1][j+price[i]]=max(f[i+1][j+price[i]],f[i][j]+dread[i]);
    				if (f[i][j]>=dread[i]) f[i+1][j]=max(f[i+1][j],f[i][j]);
    			}
    	for (int i=0;i<=2*n;i++) if (f[n][i]>=0) return i;
    }
};
