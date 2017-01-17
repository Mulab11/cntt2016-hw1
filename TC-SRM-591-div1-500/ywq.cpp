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

int gcd(int x,int y)
{
	while (y)
	{
		int r=x%y;x=y;y=r;
	}
	return x;
}

struct PyramidSequences 
{
    long long distinctPairs(int N, int M)
    {
    	int g=gcd(N-1,M-1);
    	int x=(N-1)/g,y=(M-1)/g;
    	return ll(g-1)*x*y+(ll(x+1)*(y+1)+1)/2;
    }
};
