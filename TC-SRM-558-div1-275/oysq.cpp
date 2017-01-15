// BEGIN CUT HERE

// END CUT HERE
#line 5 "Stamp.cpp"
#include <bits/stdc++.h>

using namespace std;

#define SZ(x) (int)(x).size()
#define pb push_back
#define mp make_pair

typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<double> VD;
typedef long long ll;
typedef pair<int,int> pii;

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(x > y) x = y;}

const int N = 500;
const int INF = 0x3f3f3f3f;

int f[N + 9][N + 9];
// f[i][j] means minimal steps to color segment [l, r]

// minimal steps of coloring a same-colored segment with length l using stamp of length L
int cnt(int l, int L) {
	return (l - 1) / L + 1;
}

// check if segment [l, r] can be in same color
bool check(const string &s, int l, int r) {
	char c = '*';
	for(int i = l; i <= r; ++i)
		if(s[i] != '*') {
			c = s[i];
			break;
		}
	if(c == '*') return true;
	for(int i = l; i <= r; ++i)
		if(s[i] != '*' && s[i] != c)
			return false;
	return true;
}

struct Stamp {
    int getMinimumCost(string col, int c1, int c2) {
		int n = SZ(col), ans = INF;
		// enumerate the length of the stamp
		for(int L = 1; L <= n; ++L) {
			memset(f, INF, sizeof f);
			// initalization
			for(int l = L; l <= n; ++l)
				for(int i = 0; i <= n - l; ++i)
					if(check(col, i, i + l - 1))
						f[i][i + l - 1] = cnt(l, L);
			// interval dp
			for(int l = L + 1; l <= n; ++l)
				for(int i = 0; i < n; ++i) {
					int j = i + l - 1;
					for(int k = i; k < j; ++k)
						chkmin(f[i][j], f[i][k] + f[k + 1][j]);
				}
			// update answer
			if(f[0][n - 1] != INF)
				chkmin(ans, L * c1 + f[0][n - 1] * c2);
		}
		return ans;
	}
};
