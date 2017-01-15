// BEGIN CUT HERE

// END CUT HERE
#line 5 "Ear.cpp"
#include <bits/stdc++.h>

using namespace std;

#define SZ(x) (int)(x).size()
#define pb push_back
#define mp make_pair
#define fi first
#define se second

typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<double> VD;
typedef long long ll;
typedef pair<int,int> pii;

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(x > y) x = y;}

const int RG = 10000;

vector<int> r, bx, by;
vector<pii> b;
int pre[RG + 9];

// transfer from string to integers
void get(vector<int> &a, const vector<string> &b) {
	a.clear();
	string s;
	for(int i = 0; i < SZ(b); ++i) s += b[i];
	s += ' ';
	for(int i = 0; i < SZ(s); ++i) {
		int j = i;
		while(j < SZ(s) - 1 && s[j] != ' ') ++j;
		int num = 0;
		for(int k = i; k < j; ++k)
			num = num * 10 + s[k] - '0';
		a.pb(num);
		i = j;
	}
}

bool cmp(const pii &p, const pii &q) {
	return p.se < q.se;
}

// interval[l, r] sum
int S(int l, int r) {
	if(l > r || r < 1 || l > RG) return 0;
	chkmax(l, 1), chkmin(r, RG);
	return pre[r] - pre[l - 1];
}

// number of situations that A in [1, s1], B in [1, s1 + s2], A < B
ll calc(int s1, int s2) {
	ll ret = 0;
	ret += s1 * s2;
	ret += s1 * (s1 - 1) / 2;
	return ret;
}

struct Ear {
    long long getCount(vector <string> redX, vector <string> blueX, vector <string> blueY) {
		// change string into numbers
		get(r, redX), get(bx, blueX), get(by, blueY), b.clear();
		
		for(int i = 0; i < SZ(bx); ++i) b.pb(mp(bx[i], by[i]));
		std::sort(b.begin(), b.end(), cmp);// sort blue nodes into y-ascending orders
		
		memset(pre, 0, sizeof pre);
		for(int i = 0; i < SZ(r); ++i) pre[r[i]]++;
		for(int i = 1; i <= RG; ++i) pre[i] += pre[i - 1];// get prefix sum of red nodes

		ll ans = 0;
		// enumerate 2 blue nodes
		for(int i = 0; i < SZ(b); ++i)// i -> Q
			for(int j = i + 1; j < SZ(b); ++j)// j -> P
				if(b[i].se < b[j].se) {// Py > Qy
					if(b[i].fi < b[j].fi) {// Qx < Px
						int dx = b[i].se * (b[j].fi - b[i].fi) / (b[j].se - b[i].se);
						int s1 = S(0, b[i].fi - dx - 1), s2 = S(b[i].fi - dx, b[i].fi - 1);
						// A in [1, s1], B in [1, s1 + s2], Ax < Bx
						int t1 = S(b[i].fi + 1, b[j].fi), t2 = S(b[j].fi + 1, RG);
						// C in [1, t1], D in [1, t1 + t2], Cx < Dx
						assert(s1 >= 0 && s2 >= 0 && t1 >= 0 && t2 >= 0);
						ans += calc(s1, s2) * calc(t2, t1);
					}
					else if(b[i].fi == b[j].fi) {// Qx = Px
						int s1 = S(0, b[i].fi - 1), s2 = S(b[i].fi + 1, RG);
						// A, B in [1, s1], C, D in [1, s2], Ax < Bx, Cx < Dx
						assert(s1 >= 0 && s2 >= 0);
						ans += s1 * (s1 - 1) / 2 * s2 * (s2 - 1) / 2;
					}
					else {// Qx > Px
						int dx = b[i].se * (b[i].fi - b[j].fi) / (b[j].se - b[i].se);
						int s1 = S(0, b[j].fi - 1), s2 = S(b[j].fi, b[i].fi - 1);
						// A in [1, s1], B in [1, s1 + s2], Ax < Bx
						int t1 = S(b[i].fi + 1, b[i].fi + dx), t2 = S(b[i].fi + dx + 1, RG);
						// C in [1, t1], D in [1, t1 + t2], Cx < Dx
						assert(s1 >= 0 && s2 >= 0 && t1 >= 0 && t2 >= 0);
						ans += calc(s1, s2) * calc(t2, t1);
					}
				}
		return ans;
    }
};
