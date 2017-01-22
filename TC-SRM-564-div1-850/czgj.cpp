/*
	Ah, So BIG
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
#define xx first
#define yy second
using namespace std;
typedef long long LL;
typedef vector<int> VI;
const LL MOD = 1e9 + 9;
LL func(VI a){
	sort(a.begin(), a.end());
	if (a[0]) return 0; // distance of root should be 0
	LL ret = 1;
	rep(i, 1, (int)a.size() - 1){
		int p = lower_bound(a.begin(), a.end(), a[i]) - a.begin();
		ret = ret * p % MOD;
	}
	return ret;
}
LL chain(VI a, VI b, VI c, int x, int y){ // when b->a->c is a chain
	if (!x || !y) return 0;
	map<int, VI> pb, pc;
	pb[x].push_back(0);
	pb[-x].push_back(0);
	pc[-y].push_back(0);
	rep(i, 0, (int)a.size() - 1){
		int u = b[i] - a[i], v = c[i] - a[i];
		if (v == y){ // at B
			int d2 = a[i] + b[i] - x;
			if (d2 % 2) return 0;
			pb[u].push_back(d2 / 2);
		}
		else if (u == x){ // at C
			int d2 = a[i] + c[i] - y;
			if (d2 % 2) return 0;
			pc[v].push_back(d2 / 2);
		}
		else return 0; // no way
	}
	LL ret = 1;
	for (auto p : pb){
		if (p.xx < -x || p.xx > x || (p.xx + x) % 2) return 0;
		ret = ret * func(p.yy) % MOD;
	}
	for (auto p : pc){
		if (p.xx < -y || p.xx > y || (p.xx + y) % 2) return 0;
		ret = ret * func(p.yy) % MOD;
	}
	return ret;
}
LL chain(VI a, VI b, VI c){
	LL ret = 0;
	int i = min_element(a.begin(), a.end()) - a.begin();
	ret += chain(a, b, c, a[i] + b[i], a[i] + c[i]);
	ret += chain(a, b, c, a[i] + b[i], abs(a[i] - c[i]));
	ret += chain(a, b, c, abs(a[i] - b[i]), a[i] + c[i]);
	ret += chain(a, b, c, abs(a[i] - b[i]), abs(a[i] - c[i]));
	return ret % MOD;
}
LL triangle(VI a, VI b, VI c, int x){
	int da = a[x], db = b[x], dc = c[x];
	map<int, VI> pa, pb, pc;
	pa[-(da + db)].push_back(0);
	pb[-(db + dc)].push_back(0);
	pc[-(dc + da)].push_back(0);
	rep(i, 0, (int)a.size() - 1){
		int x = a[i] - b[i], y = b[i] - c[i], z = c[i] - a[i];
		if (x == da - db){ // at C
			int dd = a[i] + c[i] - da - dc;
			if (dd % 2) return 0;
			pc[z].push_back(dd / 2);
		}
		else if (y == db - dc){ // at A
			int dd = a[i] + b[i] - da - db;
			if (dd % 2) return 0;
			pa[x].push_back(dd / 2);
		}
		else if (z == dc - da){ // at B
			int dd = b[i] + c[i] - db - dc;
			if (dd % 2) return 0;
			pb[y].push_back(dd / 2);
		}
		else return 0;
	}
	LL ret = 1;
	for (auto p : pa){
		if (p.xx < - da - db || p.xx > da - db || (da + db - p.xx) % 2) return 0;
		ret = ret * func(p.second) % MOD;
	}
	for (auto p : pb){
		if (p.xx < - db - dc || p.xx > db - dc || (db + dc - p.xx) % 2) return 0;
		ret = ret * func(p.second) % MOD;
	}
	for (auto p : pc){
		if (p.xx < - dc - da || p.xx > dc - da || (dc + da - p.xx) % 2) return 0;
		ret = ret * func(p.second) % MOD;
	}
	return ret;
}
LL triangle(VI a, VI b, VI c){
	LL ret = 0;
	rep(i, 0, (int)a.size() - 1) ret += triangle(a, b, c, i);
	return ret % MOD;
}
class UnknownTree {
	public:
	int getCount(vector <int> A, vector <int> B, vector <int> C) {
		return (chain(A, B, C) + chain(B, A, C) + chain(C, A, B) + triangle(A, B, C)) % MOD;
	}
};

/*
	bigger than bigger
*/
