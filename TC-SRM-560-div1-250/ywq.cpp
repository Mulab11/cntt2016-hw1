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

int a[55];

struct TomekPhone 
{
    int minKeystrokes(vector <int> frequencies, vector <int> keySizes)
    {
    	int n=frequencies.size();
    	sort(frequencies.begin(),frequencies.end());
    	sort(keySizes.begin(),keySizes.end());
    	int x=0,ans=0,m=keySizes.size();
    	for (int i=0;i<m/2;i++) swap(keySizes[i],keySizes[m-i-1]); //reverse keySizes
    	for (int i=n-1;i>=0;i--)
    	{
    		if (a[x]==keySizes[x]) return -1;
    		a[x]++;ans+=a[x]*frequencies[i];
    		x++;if (x>=m||a[x]==keySizes[x]) x=0;
    	}
    	return ans;
    }
};
