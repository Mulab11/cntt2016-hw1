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

int b[55],s[55];

struct PiecewiseLinearFunction 
{
    int maximumSolutions(vector <int> Y)
    {
    	int n=Y.size();
    	for (int i=1;i<n;i++) if (Y[i]==Y[i-1]) return -1;
    	for (int i=0;i<n;i++) b[i]=Y[i];
    	sort(b,b+n);
    	int m=1;for (int i=1;i<n;i++) if (b[i]!=b[i-1]) b[m++]=b[i];
    	for (int i=0;i<n;i++) Y[i]=lower_bound(b,b+m,Y[i])-b;
    	for (int i=1;i<n;i++)
    	{
    		int l=Y[i-1],r=Y[i];
    		if (l>r) swap(l,r);
    		s[l]++;s[r]--;
    	}
    	for (int i=1;i<m;i++) s[i]+=s[i-1];
    	int ans=0;
    	for (int i=0;i<m;i++) ans=max(ans,s[i]);
    	for (int i=0;i<m;i++)
    	{
    		int t=0;
    		for (int j=0;j<n-1;j++)
    			if ((Y[j]<=i&&i<Y[j+1])||(Y[j]>=i&&i>Y[j+1])) t++;
    		if (Y[n-1]==i) t++;
    		ans=max(ans,t);
    	}
    	return ans;
	}
};
