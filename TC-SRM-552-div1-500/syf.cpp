//============================================================================
// Author       : Sun YaoFeng
//============================================================================

#include "iostream"
#include "cstdio"
#include "cstdlib"
#include "algorithm"
#include "cmath"
#include "cstring"
#include "string"
#include "map"
#include "set"
#include "stack"
#include "list"
#include "vector"
#include "queue"

using namespace std;

#define PI acos(-1)
#define MP make_pair
#define PB push_back
#define VI vector < int >
#define PII pair < int, int >
#define LL long long
#define SET(v,i) memset(v, i, sizeof(v))
#define FOR(i,a,b) for (int i = (a); i <= (b); i++)
#define FORD(i,a,b) for (int i = (a); i >= (b); i--)
#define FORN(i,a,b) for (int i = (a); i < (b); i++)
#define DOWN(i,a,b) for (int i = (a); i > (b); i--)
#define FIT(it,v) for (typeof(v.begin()) it = v.begin(); it != v.end(); it++)
#define FITD(it,v) for (typeof(v.rbegin()) it = v.rbegin(); it != v.rend(); it++)
#define FREOPEN freopen("a.in", "r", stdin); freopen("a.out", "w", stdout)

class FoxAndFlowerShopDivOne{
public:
	int call (vector < string > f, int md) {
		int sump [50][50], suml[50][50];
		int upper [2020], lower[2020];
		int r, c;
		int result = -1;
		r = f.size();
		c = f[0].size();
		
		//prepare sump and suml
		//we convert the grid into 1-indexed for convenience
		SET (sump, 0);
		SET (suml, 0);
		FOR (i, 1, r)
			FOR (j, 1, c) {				
				sump[i][j] = sump[i - 1][j] + sump[i][j - 1] - sump[i - 1][j - 1] + (f[i - 1][j - 1] == 'P');
				suml[i][j] = suml[i - 1][j] + suml[i][j - 1] - suml[i - 1][j - 1] + (f[i - 1][j - 1] == 'L');
			}
			
		//consider all the possible line D
		FOR (d, 1, r) {
			SET (upper, -1);
			SET (lower, -1);
			
			//amongst all the upper rectangles that have the difference of number 'P' and 'L'
			//is x, the rectangle has the maximum number of flowers will cover upper[x + 1000] flowers.
			//similar difination for lower array.
			
			//consider all the upper rectangles
			FOR (x1, 1, d)
			FOR (y1, 1, c)
			FOR (x2, x1, d)
			FOR (y2, y1, c) {
				//counting Ls and Ps
				int L = suml[x2][y2] - suml[x1 - 1][y2] - suml[x2][y1 - 1] + suml[x1 - 1][y1 - 1];
				int P = sump[x2][y2] - sump[x1 - 1][y2] - sump[x2][y1 - 1] + sump[x1 - 1][y1 - 1];
				
				upper[P - L + 1000] = max(upper[P - L + 1000], P + L);
			}
			
			FOR (x1, d + 1, r)
			FOR (y1, 1, c)
			FOR (x2, x1, r)
			FOR (y2, y1, c) {
				//counting Ls and Ps
				int L = suml[x2][y2] - suml[x1 - 1][y2] - suml[x2][y1 - 1] + suml[x1 - 1][y1 - 1];
				int P = sump[x2][y2] - sump[x1 - 1][y2] - sump[x2][y1 - 1] + sump[x1 - 1][y1 - 1];
				
				lower[P - L + 1000] = max(lower[P - L + 1000], P + L);
			}
			
			FOR (x, 0, 2000)
			if (upper[x] >= 0)
				FOR (y, 0, 2000)
					if (lower[y] >= 0)
						if (abs(x + y - 2000) <= md) result = max (result, upper[x] + lower[y]);
		}
		
		return result;
	}
	int theMaxFlowers(vector < string > flowers, int maxDiff) {
		int r, c;
		r = flowers.size();
		c = flowers[0].size();
		
		//rotated version of flowers
		vector < string > rotated;
		
		FOR (i, 0, c - 1) {
			string t = "";
			FOR (j, 0, r - 1) t += flowers[j][c - i - 1];
			rotated.PB(t);
		}
		
		return max (call(flowers, maxDiff), call(rotated, maxDiff));
	}
};