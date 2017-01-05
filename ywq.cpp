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

int deg[55];
bool v[55][55];

struct PenguinSledding 
{
    long long countDesigns(int numCheckpoints, vector <int> checkpoint1, vector <int> checkpoint2)
    {
    	for (int i=0;i<checkpoint1.size();i++)
    	{
    		deg[checkpoint1[i]]++;
    		deg[checkpoint2[i]]++;
    		v[checkpoint1[i]][checkpoint2[i]]=v[checkpoint2[i]][checkpoint1[i]]=1;
    	}
    	ll ans=0;
    	for (int i=1;i<=numCheckpoints;i++)
    		ans+=((1ll<<deg[i])-1);
    	ans=ans-checkpoint1.size()+1;
    	for (int i=1;i<=numCheckpoints;i++)
    		for (int j=i+1;j<=numCheckpoints;j++)
    			for (int k=j+1;k<=numCheckpoints;k++)
    				if (v[i][j]&&v[i][k]&&v[j][k]) ans++;
    	return ans;
    }
};
