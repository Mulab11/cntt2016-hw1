#line 2 "ConvexPolygonGame.cpp"
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
#define maxm 200010
typedef long long ll;
using namespace std;
struct poi {
	int x, y;
	poi() {}
	poi(int _x, int _y) {x = _x; y = _y;}
	poi operator - (const poi &b) { return poi(x - b.x, y - b.y);}
	ll operator * (const poi &b) { return 1ll * x * b.y - 1ll * y * b.x;}
}a[maxm];
class ConvexPolygonGame {
	public:
		string winner(vector <int> X, vector <int> Y) {
			int n = X.size(), m = 0;
			for (int x = -100000; x <= 100000; ++x) {
				int u = -oo, d = oo;
				for (int i = 0; i < n; ++i) {
					poi l = poi(X[i], Y[i]), r = poi(X[(i + 1) % n], Y[(i + 1) % n]);
					if (X[i] == x && x == X[(i + 1) % n]) {
						d = min(Y[i], Y[(i + 1) % n]) + 1; u = max(Y[i], Y[(i + 1) % n]) - 1;
						continue;
					}
					double k = 1.0 * (Y[i] - Y[(i + 1) % n]) / (X[i] - X[(i + 1) % n]);
					if ((X[i] <= x && x <= X[(i + 1) % n])) {
						d = int(ceil(1.0 * (Y[i] + 1.0 * (x - X[i]) * k)));
						if (x == X[i] || x == X[(i + 1) % n]) ++d;
					}
					if ((X[(i + 1) % n] <= x && x <= X[i])) {
						u = int(floor(1.0 * Y[(i + 1) % n] + 1.0 * (x - X[(i + 1) % n]) * k));
						if (x == X[i] || x == X[(i + 1) % n]) --u;
					}
				}
				for (int j = d; j <= u; ++j) {
					if (++m == maxm) return "Masha";
					a[m] = poi(x, j);
				}
			}
			if (m <= 1) return "Petya";
			for (int i = 3; i <= m; ++i) {
				if (((a[i] - a[1]) * (a[i] - a[2])))
					return "Masha";
			}
			return "Petya";
		}
};
