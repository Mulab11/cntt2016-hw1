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

const int mod=1000000007;

struct TrafficCongestion 
{
    int theMinCars(int treeHeight)
    {
    	int ans=1;
    	for (int i=0;i<treeHeight;i++)
    		if (i&1) ans=(ans*2+1)%mod; else ans=(ans*2-1)%mod;
    	return (ans+mod)%mod;
    }
};
