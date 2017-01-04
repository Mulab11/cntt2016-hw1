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

struct KnightCircuit2 
{
    int maxSize(int w, int h)
    {
    	if (w>h) swap(w,h);
    	if (w==1) return 1;
    	if (w==2) return (h+1)/2;
    	if (h==3) return 8;
    	return w*h;
    }
};
