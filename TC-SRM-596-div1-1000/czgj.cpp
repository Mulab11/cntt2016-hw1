/*
	Number theory
	Math
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;

class SparseFactorial {
	public:
	void merge(vector<LL>& a, const vector<LL> &b){
		int u = a.size(), v = b.size(), w = u * v; a.resize(w);
		red(i, w - 1, 0) a[i] = ~a[i % u] && ~b[i % v] ? max(a[i % u], b[i % v]) : -1;
	}
	vector<LL> calc(int p, int c, int m){
		vector<int> cnt(m);
		vector<LL> ret(m, -1);
		rep(i, 0, p * c - 1){
			int d1 = (LL)i * i % m;
			for (int j = (LL)i * i % p; j < m; j += p){
				if (cnt[j] >= c) continue;
				int x = j - d1;
				if (!x) cnt[j] = c; else while (x % p == 0) ++cnt[j], x /= p;
				if (cnt[j] >= c) ret[j] = (LL)i * i + 1;
			}
		}
		return ret;
	}
	long long getCount(long long lo, long long hi, long long m) {
		vector<LL> s(1); LL t = m;
		rep(i, 2, t){
			int cnt = 0, tt = t;
			while (t % i == 0) ++cnt, t /= i;
			if (cnt) merge(s, calc(i, cnt, tt / t));
		}
		LL ret = 0;
		rep(i, 0, m - 1){
			if (s[i] < 0) continue;
			LL t = s[i] / m * m + i;
			if (t < s[i]) t += m;
			if (hi >= t) ret += (hi - t) / m + 1;
			if (lo > t) ret -= (lo - 1 - t) / m + 1;
		}
		return ret;
	}
};

/*
	irohanihoheto
	chirinuruwo
*/

