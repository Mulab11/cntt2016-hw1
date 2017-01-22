#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define SZ(x) (int((x).size()))
#define x first
#define y second
#define mp make_pair
#define pb push_back

using namespace std;

class UndoHistory {
public :
	inline int lcp(const string & a, const string & b) {
		int i = 0;
		while (i < SZ(a) && i < SZ(b)) {
			if (a[i] != b[i]) 
				return i;
			++i;
		}
		return i;
	}
	int minPresses(vector<string> lines) {
		int ans = SZ(lines[0]) + 1;
		rep (i, 1, SZ(lines) - 1) {
			int mi = 1e9;
			if (lcp(lines[i], lines[i - 1]) == SZ(lines[i - 1]))
				mi = SZ(lines[i]) - SZ(lines[i - 1]);
			rep (j, 0, i - 1)
				mi = min(mi, 2 + SZ(lines[i]) - lcp(lines[i], lines[j]));
			ans += mi + 1;
		}
		return ans;
	}
};
