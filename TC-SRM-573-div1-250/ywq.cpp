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

int a[50];

struct TeamContest 
{
    int worstRank(vector <int> strength)
    {
    	int n=strength.size();
    	for (int i=0;i<n;i++) a[i]=strength[i];
    	int t=max(max(a[0],a[1]),a[2])+min(min(a[0],a[1]),a[2]);
    	sort(a+3,a+n);
    	int x=3,y=n-1,ans=1;
    	while (x<=y)
    		if (a[x]+a[y]>t) {ans++;x+=2;y--;} else x+=3;
    	return ans;
    }
};
