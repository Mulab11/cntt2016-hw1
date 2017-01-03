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

ll t;
int n;
vi e[55];
int size[55],b[55];
bool v[55],ok[55];

void dfs1(int k)
{
	v[k]=1;size[k]=1;
	for (int i=0;i<e[k].size();i++)
		if (!v[e[k][i]])
		{
			dfs1(e[k][i]);
			size[k]+=size[e[k][i]];
		}
	v[k]=0;
}

void dfs2(int k)
{
	if (size[k]<=2) return; //the subtree must be a complete binary tree
	v[k]=1;int l=0;
	for (int i=0;i<e[k].size();i++)
		if (!v[e[k][i]]) b[l++]=size[e[k][i]];
	if (l!=2||((!ok[b[0]])&&(!ok[b[1]]))||b[0]>b[1]*2+1||b[1]>b[0]*2+1) //at least one subtree is full binary tree
		t=0;
	else
		if (b[0]==b[1]) t<<=1;
	for (int i=0;i<e[k].size();i++)
		if (!v[e[k][i]]) dfs2(e[k][i]);
	v[k]=0;
}

struct HatRack 
{
    long long countWays(vector <int> knob1, vector <int> knob2)
    {
    	n=knob1.size()+1;
    	for (int i=0;i<n-1;i++)
    	{
    		e[knob1[i]].pb(knob2[i]);
    		e[knob2[i]].pb(knob1[i]);
    	}
    	for (int i=0;i<6;i++) ok[(1<<i)-1]=1;
    	ll ans=0;
    	for (int i=1;i<=n;i++) //enumerate the root of the tree
    	{
    		dfs1(i); //get the size of each subtree
    		t=1;
    		dfs2(i);
    		ans+=t;
    	}
    	return ans;
    }
};
