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

string a,b;
int head[55],next0[55],ans;

int dfs(int k)
{
	int s=0;
	int p=head[k];
	while (p)
	{
		int t=dfs(p);
		if (b[p-1]=='1')
		{
			if (t==0&&a[p-1]=='0')
				t=1;
			else
				if (t==1&&a[p-1]=='1') {ans++;t=0;}
		}
		s+=t;p=next0[p];
	}
	ans+=s/2;
	return s%2;
}

struct TurnOnLamps 
{
    int minimize(vector <int> roads, string initState, string isImportant)
    {
    	int n=roads.size()+1;
    	for (int i=0;i<n-1;i++)
    	{
    		next0[i+1]=head[roads[i]];head[roads[i]]=i+1;
    	}
    	a=initState;b=isImportant;
    	ans=0;if (dfs(0)) ans++;
    	return ans;
    }
};
