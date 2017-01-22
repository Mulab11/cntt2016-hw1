/*
	Tricky math.
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;

class PyramidSequences {
	public:
	long long distinctPairs(int n, int m) {
		int k = __gcd(--n, --m); n /= k, m /= k;
		return (LL)n * m * (k - 1) + (1 + (LL)(n + 1) * (m + 1)) / 2;
	}
};

/*
	Cuius rei demonstrationem mirabilem sane detexi.
	Hanc marginis exiguitas non caperet.
*/
