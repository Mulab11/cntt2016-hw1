#include <bits/stdc++.h>
#define rep(i, l, r) for(int _r = r, i = l; i <= _r; ++i)
#define red(i, r, l) for(int _l = l, i = r; i >= _l; --i)
#define debug(x) cerr << #x << " = " << x << endl
#define MEM(x, y) memset(x, y, sizeof(x))
#define X first
#define Y second

using namespace std;
typedef long long LL;
typedef pair<int, int> PI;
const LL MOD = 1e9 + 7;

class XorAndSum{
	public:
	LL maxSum(vector<LL> a){
		int n = a.size();
		int m = 0;
		for (LL v = 1ll << 62; v; v >>= 1){
			int id = -1;
			rep(i, m, n - 1) if (a[i] & v) {id = i; break;}
			if (id == -1) continue;
			swap(a[id], a[m]);
			rep(i, 0, n - 1) if (a[i] & v && i != m) a[i] ^= a[m];
			++m;
		}
		LL mx = 0; rep(i, 0, n - 1) mx ^= a[i];
		LL ret = mx; rep(i, 1, n - 1) ret += mx ^ a[i];
		return ret;
	}
};

