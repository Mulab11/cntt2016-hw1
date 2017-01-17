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

int a[1010];

struct LittleElephantAndIntervalsDiv1 
{
    long long getNumber(int M, vector <int> L, vector <int> R)
    {
    	int n=L.size();
    	for (int i=1;i<=M;i++) a[i]=-1;
    	for (int i=0;i<n;i++)
    		for (int j=L[i];j<=R[i];j++)
    			a[j]=i;
    	ll ans=1;
    	for (int i=0;i<n;i++)
    	{
    		bool ok=0;
    		for (int j=1;j<=M;j++) if (a[j]==i) ok=1;
    		if (ok) ans<<=1;
    	}
    	return ans;
    }
};
