/*
	Easy math.
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;

class AlternateColors2 {
	public:
	long long countWays(int n, int k) {
		LL ret = 0;
		if (k % 3 == 1) ret += (LL)(n - k + 1) * (n - k + 2) / 2; // r=g=b
		ret += (LL)((k - 1) / 2 - (k - 1) / 3) * (n - k + 1) * 2; // r=g>b
		rep(i, 0, n){ // r>g,b
			int mi = max(0, k + 2 - 2 * i), ma = min(k - i, i - 2); 
			ret += max(ma - mi + 1, 0);
		}
		return ret;
	}
};

/*
	Yukkuri shite itte ne!
*/
