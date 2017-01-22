/*
	Dp, quick power
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
const LL MOD = 1e9 + 7;
const int MAXN = 400;
vector<LL> operator *(const vector<LL>& a, const vector<LL>& b){ // a[i] * b[j] -> c[(i + j) % n]
	int n = a.size(); vector<LL> ret(n);
	rep(i, 0, n - 1) rep(j, 0, n - 1) ret[(i + j) % n] = (ret[(i + j) % n] + a[i] * b[j]) % MOD;
	return ret;
}
vector<LL> pow(vector<LL> a, LL p){
	int n = a.size(); vector<LL> ret(n); ret[0] = 1;
	for (; p; p >>= 1, a = a * a) if (p & 1) ret = ret * a;
	return ret;
}
class PenguinEmperor {
	public:
	int countJourneys(int n, long long m) {
		vector<LL> a(n), b(n), c(n); b[0] = 1;
		rep(i, 0, n - 1){
			rep(j, 0, n - 1) a[j] = (b[(i + j) % n] + (i && 2 * i != n ? b[(n + j - i) % n] : 0)) % MOD;
			b = a; if (i == m % n) c = b; // remainder
		}
		return (pow(b, m / n) * c)[0];
	}
};

/*
	But, maybe we could make a deal.
		- Flower Dance
*/
