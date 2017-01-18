#line 2 "PyramidSequences.cpp"
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
typedef long long ll;
using namespace std;
ll cnt(ll l, ll r, ll c, ll d) {
	if (l > r) return 0;
	return (r / d) + (r % d >= c) - ((l - 1) / d) - ((l - 1) % d >= c);
}
ll calc(ll x, ll y, ll d) {
	ll ret = 0;
	if (x % d < y % d) swap(x, y);
	ret += 1ll * (x / d + 1) * (y / d + 1) * (y % d);
	ret += 1ll * (x / d + 1) * (y / d) * ((x % d) - (y % d));
	ret += 1ll * (x / d) * (y / d) * (d - (x % d));
	return ret;
}
class PyramidSequences {
	public:
		long long distinctPairs(int x, int y) {
			ll a = 2ll * x - 2, b = 2ll * y - 2, d = __gcd(a, b);
			ll ans = 1ll * a * b / d;
			if (2ll * x % d == 2ll * y % d) {
				ll del = calc(x - 1, y - 1, d) - calc(x - 1, 1, d) - calc(y - 1, 1, d) + calc(1, 1, d);
				ans -= del;
				del = calc(x - 1, 2ll * y - 2, d) - calc(x - 1, y, d) - calc(1, 2ll * y - 2, d) + calc(1, y, d);
				ans -= del;
			}
			ll r1, r2, p1, p2;
			if (d % 2ll == 0) {
				r1 = (2ll * y % d) / 2ll; r2 = (r1 + d / 2ll) % d;
				p1 = (2ll * x % d) / 2ll; p2 = (p1 + d / 2ll) % d;
			} else {
				r2 = -1; r1 = y % d;
				p2 = -1; p1 = x % d;
			}
			ans -= 1ll * cnt(1, a, r1, d) * cnt(2, y - 1, r1, d);
			if (r2 != -1)
				ans -= 1ll * cnt(1, a, r2, d) * cnt(2, y - 1, r2, d);
			ans -= 1ll * cnt(2, x - 1, p1, d) * cnt(1, b, p1, d);
			if (p2 != -1)
				ans -= 1ll * cnt(2, x - 1, p2, d) * cnt(1, b, p2, d);
			if (r1 == p1)
				ans += 3ll * cnt(2, y - 1, p1, d) * cnt(2, x - 1, p1, d);
			if (r2 != -1 && r2 == p1)
				ans += 3ll * cnt(2, y - 1, p1, d) * cnt(2, x - 1, p1, d);
			if (p2 != -1 && p2 == r1) 
				ans += 3ll * cnt(2, y - 1, p2, d) * cnt(2, x - 1, p2, d);
			if (p2 != -1 && r2 != -1 && p2 == r2)
				ans += 3ll * cnt(2, y - 1, p2, d) * cnt(2, x - 1, p2, d);
			return ans;
		}
};
