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

int a[110];

struct EelAndRabbit 
{
    int getmax(vector <int> l, vector <int> t)
    {
    	int n=l.size();
    	int m=0;
    	for (int i=0;i<n;i++)
    	{
    		a[m++]=t[i];a[m++]=l[i]+t[i];
    	}
    	sort(a,a+m);
    	int ans=0;
    	for (int i=0;i<m;i++)
    		for (int j=i;j<m;j++)
    		{
    			int s=0;
    			for (int k=0;k<n;k++)
    				if ((t[k]<=a[i]&&a[i]<=t[k]+l[k])||(t[k]<=a[j]&&a[j]<=t[k]+l[k])) s++;
    			ans=max(ans,s);
    		}
    	return ans;
    }
};
