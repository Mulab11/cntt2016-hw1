#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long int LL;
typedef vector <int> vi;
typedef pair <int, int> pii;
typedef vector <pii> vpi;
const LL MOD = 1000000009LL;

inline bool cmp(const pii &a, const pii &b){return a.se != b.se ? a.se < b.se : a.fi < b.fi;}
class UnknownTree{
public:
	LL solve1(vi x){ //Solve the problem for A
		int n = x.size(), i, j; LL ret = 1LL;
		sort(x.begin(), x.end());
		if(n < 1 || x[0]) return 0LL;
		for(i = 1, j = 0; i < n; ++ i){
			while(j < i && x[j] < x[i]) ++ j;
			(ret *= j) %= MOD;
		} return ret;
	}
	LL solve2(vpi x){ //Solve the problem for A-B(A, B included)
		int n = x.size(), i, tmp; vi ex; vpi X;
		sort(x.begin(), x.end(), cmp);
		if(n <= 1 || x[1].se == 0) return 0LL;
		if(n == 2 && x[1].fi == 0 && x[0].fi == x[1].se) return 1LL;
		if(x[2].se == x[1].se) return 0LL;
		if(x[1].fi + x[1].se != x[0].fi || x[1].fi == 0){
			for(i = 1; i < n; ++ i){
				if(x[i].se - x[i].fi != x[0].fi)
					return 0LL;
				ex.push_back(x[i].fi);
			} return solve1(ex);
		}
		for(i = 2; i < n; ++ i) x[i].se -= x[1].se;
		x[1].se = 0; X.push_back(x[1]);
		for(i = 1; i < n; ++ i){
			if(x[i].fi == x[i].se + x[1].fi) ex.push_back(x[i].se);
			else{
				tmp = x[i].fi + x[i].se - x[1].fi;
				if((tmp < 0) || (tmp & 1)) return 0LL;
				X.push_back(x[i]);
			}
		} return solve2(X) * solve1(ex) % MOD;
	}
	LL solve3center(vi a, vi b, vi c, int ct){ //Seperate all nodes into four parts: subtree A, B, C and the remaining with center as ct
		int i, da, db, dc, n = a.size();
		vi ex; vpi A, B, C;
		A.push_back(pii(a[ct], 0));
		A.push_back(pii(0, a[ct]));
		B.push_back(pii(b[ct], 0));
		B.push_back(pii(0, b[ct]));
		C.push_back(pii(c[ct], 0));
		C.push_back(pii(0, c[ct]));
		ex.push_back(0);
		for(i = 0; i < n; ++ i){
			if(i == ct) continue;
			da = a[i] - a[ct], db = b[i] - b[ct], dc = c[i] - c[ct];
			if(da == db && db == dc && da > 0) ex.push_back(da);
			else if(da == db && da > 0) C.push_back(pii(c[i], da));
			else if(da == dc && da > 0) B.push_back(pii(b[i], da));
			else if(db == dc && db > 0) A.push_back(pii(a[i], db));
			else return 0;
		} return ((solve2(A) * solve2(B) % MOD) * solve2(C) % MOD) * solve1(ex) % MOD;
	}
	LL solve3chain(vi a, vi b, vi c){ //Solve the problem for chain A-B-C
		int i, da, dc, n = a.size(); LL ret = 0LL;
		set <pii> d; vpi A, C; vi ex;
		for(i = 0; i < n; ++ i){
			//Case 1: directly connected to B
			d.insert(pii(a[i] - b[i], c[i] - b[i]));
			//Case 2(.1): between A & B
			d.insert(pii(a[i] + b[i], c[i] - b[i]));
			//Case 2(.2): directly connected to A
			d.insert(pii(b[i] - a[i], c[i] - b[i]));
			//Case 3(.1): between B & C
			d.insert(pii(a[i] - b[i], b[i] + c[i]));
			//Case 3(.2): directly connected to C
			d.insert(pii(a[i] - b[i], b[i] - c[i]));
		} set <pii> :: iterator it;
		for(it = d.begin(); it != d.end(); ++ it){
			da = it -> fi, dc = it -> se;
			if(da <= 0 || dc <= 0) continue;
			A.clear(), C.clear(), ex.clear();
			A.push_back(pii(da, 0));
			A.push_back(pii(0, da));
			C.push_back(pii(dc, 0));
			C.push_back(pii(0, dc));
			ex.push_back(0);
			for(i = 0; i < n; ++ i){
				if(a[i] - b[i] == da && c[i] - b[i] == dc) ex.push_back(b[i]);
				else if(c[i] - b[i] == dc) A.push_back(pii(a[i], b[i]));
				else if(a[i] - b[i] == da) C.push_back(pii(c[i], b[i]));
				else break;
			} if(i < n) continue;
			ret = (ret + (solve2(A) * solve2(C) % MOD) * solve1(ex)) % MOD;
		} return ret;
	}
	int getCount(vi a, vi b, vi c){
		int n = a.size(), ret = 0, i;
		for(i = 0; i < n; ++ i)
			(ret += solve3center(a, b, c, i)) %= MOD;
		return (ret + solve3chain(a, b, c) + solve3chain(a, c, b) + solve3chain(b, a, c)) % MOD;
	}
};
