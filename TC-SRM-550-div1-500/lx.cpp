#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define bin(x) (1<<(x))
#define LX_JUDGE

using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

template<typename T> inline void upmax(T &x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T &x, T y) { x > y ? x = y : 0; }

class CheckerExpansion {
public :
	LL t;
	char calc(LL x, LL y) {
		if ((x + y) & 1)  return '.';
		LL a = (x + y) / 2, b = (x - y) / 2;
		if (a >= t || b < 0 || a < b || (a & y) != y)  return '.';
		return a & 1 ? 'B' : 'A';
	}
	//杨辉三角的性质
	vector<string> resultAfter(LL t, LL x0, LL y0, int w, int h) {
		this->t = t;
		vector<string> res;
		down (y, h-1, 0) {
			string tmp = "";
			rep (x, 0, w-1) {
				tmp = tmp + calc(x0 + x, y0 + y);
			}
			res.pb(tmp);
		}
		return res;
	}
};
