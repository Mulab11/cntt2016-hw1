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

const ll inf=3000000000000000000ll;

struct FoxPaintingBalls 
{
    long long theMax(long long R, long long G, long long B, int N)
    {
    	ll m=ll(N)*(N+1)/2;
    	if (m%3==0) return min(min(R,G),B)/(m/3);
        //binary search
    	ll l=1,r=inf;
    	while (l<=r)
    	{
    		ll mid=(l+r)>>1;
    		if (m/3&&min(min(R,G),B)/(m/3)<mid) {r=mid-1;continue;}
    		ll s=R+G+B-(m/3)*mid*3;
    		if (s>=mid) l=mid+1; else r=mid-1;
    	}
    	return r;
    }
};


// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
