#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)

using namespace std;
typedef long long LL;

const int mo = 1e9 + 7;

class TrafficCongestion {
public :
	int theMinCars(int h) {
		if (h <= 1)  return 1;
		int a = 3, b = 1, c;
		rep (i, 3, h) {
			c = a;
			a = (2ll * b + a) % mo;
			b = c;
		}
		return a;
	}
};
