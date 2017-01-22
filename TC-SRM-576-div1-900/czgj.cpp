/*
	Tricky combinatorics
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
const LL inv25 = 440000004;
const LL MOD = 1e9 + 9;
LL pow26(int k){
	LL ret = 1, s = 26;
	for (; k; k >>= 1, s = s * s % MOD)
		if (k & 1) ret = ret * s % MOD;
	return ret;
}
LL sumpow26(int k){
	return (pow26(k + 1) + MOD - 1) * inv25 % MOD;
}
vector<string> a;
set<int> SL;
int w;
class CharacterBoard {
	public:
	int func(int l){ // count strings with length = l
		map<int, char> s;
		rep(i, 0, (int)a.size() - 1)
			rep(j, 0, (int)a[0].size() - 1){
				int pos = ((LL)i * w + j) % l; char c = a[i][j];
				if (s.count(pos) && s[pos] != c) return 0; // conflict
				s[pos] = c;
			}
		return pow26(l - s.size()); // there are (s.size()) constraints, and the others are free
	}
	int countGenerators(vector <string> a, int w, int i0, int j0) {
		SL.clear();
		int n = a.size(), m = a[0].size(), ret = 0; 
		::a = a; ::w = w;
		rep(i, 0, n - 1) rep(j, -m + 1, m - 1){
			LL D = (LL)i * w + j; // D = delta between two grid
			if (D <= 0) continue;
			for (LL l = 1; l <= w && l * l <= D; ++l)  // first deal with l | D
				if (D % l == 0){
					if (!SL.count(l)) SL.insert(l), ret = (ret + func(l)) % MOD;
					if (!SL.count(D / l) && D / l <= w) SL.insert(D / l), ret = (ret + func(D / l)) % MOD;
				}
		}
		SL.insert(w + 1);
		int last = 0;
		for (int now : SL){ /// the others are easy geometric series
			if (now > last + 1){
				assert(last - n * m >= -1);
				ret = (ret + sumpow26(now - n * m - 1) - sumpow26(last - n * m) + MOD) % MOD;
			}
			last = now;
		}
		return ret;
	}
};

/*
	gojira???
	that sounds interesting.
*/
