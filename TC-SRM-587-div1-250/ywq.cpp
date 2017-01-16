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

struct JumpFurther 
{
    int furthest(int N, int badStep)
    {
    	int s=0;
    	for (int i=1;i<=N;i++)
    	{
    		s+=i;
    		if (s==badStep) s--;
    	}
    	return s;
    }
};
