/*
	Human intelligence
	Then brute force.
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;

class FoxAndAvatar {
	public:
	int w;
	int dfs(int d, int n, int p){
		if ((n <= w || w == 1) && (p == 1 || p == n) || (n < 2 * w && p == w) || (p == n && p % w == 1)) return d; // OTK
		if (d == 3) return 4; // give up
		int ret = 4, x = (p - 1) / w + 1, y = (p - 1) % w + 1, h = n / w;
		// up
		rep(i, 1, x - 1) rep(j, 1, w)
			ret = min(ret, dfs(d + 1, n - i * j, p - i * j));
		// left
		rep(i, 1, x) rep(j, 1, y - 1)
			ret = min(ret, dfs(d + 1, n - j * (h - i + 1) - min(j, n % w), p - (x - i + 1) * j));
		// right
		rep(i, 1, x - 1) rep(j, 1, w - y)
			ret = min(ret, dfs(d + 1, n - j * (h - i + 1) - max(0, min(j, n % w - y)), p - j * (x - i)));
		// down
		if (n > x * w) ret = min(ret, dfs(d + 1, x * w, p));
		return ret;
	}
	int minimalSteps(int n, int width, int x) {
		if (n == 1 && x == 1) return 0; // spj
		w = width;
		return dfs(1, n, x);
	}
};

/*
	1000s are Easy!!(lie)
*/
