#line 2 "Constellation.cpp"
#include<vector>
#include<list>
#include<map>
#include<set>
#include<deque>
#include<stack>
#include<bitset>
#include<algorithm>
#include<functional>
#include<numeric>
#include<utility>
#include<sstream>
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<cstring>
#define cl(x) memset(x, 0, sizeof(x));
#define pii pair<int, int>
#define fr first
#define sc second
#define mp make_pair
#define pb push_back
#define oo 0x3f3f3f3f
#define maxn 60
typedef long long ll;
using namespace std;
struct poi {
	int x, y;
	poi() {}
	poi(int _x, int _y) {x = _x; y = _y;}
	poi operator + (const poi &b) { return poi(x + b.x, y + b.y);}
	poi operator - (const poi &b) { return poi(x - b.x, y - b.y);}
	ll operator * (const poi &b) { return 1ll * x * b.y - 1ll * y * b.x;}
} a[maxn];
bool between(int l, int r, int x) {
	if (a[l].x == a[r].x) {
		if (a[l].y > a[r].y) swap(l, r);
		return (a[l].y <= a[x].y && a[x].y <= a[r].y);
	} else {
		if (a[l].x > a[r].x) swap(l, r);
		return (a[l].x <= a[x].x && a[x].x <= a[r].x);
	}
}
class Constellation {
	public:
		double expectation(vector <int> x, vector <int> y, vector <int> prob) {
			int n = x.size();
			for (int i = 0; i < n; ++i) a[i] = poi(x[i], y[i]);
			double ans = 0;
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < n; ++j) {
					if (j == i) continue;
					double now = a[i] * a[j] * 0.5;
					double p = prob[i] / 1000.0 * prob[j] / 1000.0;
					for (int k = 0; k < n; ++k) {
						if (k == i || k == j) continue;
						ll tmp = (a[k] - a[i]) * (a[j] - a[i]);
						if (tmp > 0 || (tmp == 0ll && between(i, j, k)))
							p *= (1000.0 - prob[k]) / 1000.0;
					}
					ans += p * now;
				}
			return fabs(ans);
		}
};
