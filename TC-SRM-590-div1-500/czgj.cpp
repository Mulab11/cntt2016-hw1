/*
	Gauss Elimination
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
const int MAXN = 64;
class XorCards {
	public:
	vector<int> hb; // hb = highbit
	int check(LL x, int d, int n, const vector<LL> &a){
		LL s = 0;
		rep(i, 0, (int)a.size() - 1)
			if (hb[i] < d) return s >> d == x >> d ? n - i : -1;
			else if ((s >> hb[i] & 1) ^ (x >> hb[i] & 1)) s ^= a[i];
		return s >> d == x >> d ? 0 : -1;
	}
	long long numberOfWays(vector<long long> a, long long limit) {
		int n = a.size(), vn = 0; hb.resize(n);
		red(i, 63, 0){ // Gauss Elimination
			rep(j, vn, n - 1) if (a[j] >> i & 1) {swap(a[j], a[vn]); break;}
			if (~a[vn] >> i & 1) continue;
			rep(j, vn + 1, n - 1) if (a[j] >> i & 1) a[j] ^= a[vn];
			hb[vn] = i; if (++vn >= n) break;
		}
		rep(i, vn, n - 1) hb[i] = -1;
		LL ret = 0;
		rep(i, 0, 63) if (limit >> i & 1) { // if differ at i
			int d = check(limit ^ (1ll << i), i, n, a);
			if (d >= 0) ret += 1ll << d;
		}
		int d = check(limit, 0, n, a); // if equ
		if (d >= 0) ret += 1ll << d;
		return ret; 
	}
};

/*
	Subete wa God Knows...
*/
