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

int g[55][55];

struct Egalitarianism 
{
    int maxDifference(vector <string> isFriend, int d)
    {
    	int n=isFriend.size();
    	for (int i=0;i<n;i++)
    		for (int j=0;j<n;j++)
    			if (isFriend[i][j]=='Y') g[i][j]=1; else g[i][j]=n;
    	for (int i=0;i<n;i++) g[i][i]=0;
    	for (int k=0;k<n;k++)
    		for (int i=0;i<n;i++)
    			for (int j=0;j<n;j++)
    				g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
    	int ans=0;
    	for (int i=0;i<n;i++)
    		for (int j=0;j<n;j++)
    			ans=max(ans,g[i][j]);
    	if (ans==n) return -1; else return ans*d;
    }
};
