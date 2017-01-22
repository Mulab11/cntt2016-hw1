#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define LX_JUDGE

using namespace std;
typedef long long LL;

template<typename T> inline void upmax(T & x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T & x, T y) { x > y ? x = y : 0; }

const int mo = 1e9 + 7;
const int N = 305;

typedef pair<int, int> pii;

class WolfInZooDivOne {
public :
	pii segs[N];
	int f[N][N];		//f[i][j]: 最后两个 1 分别在 i, j 的方案数
	int n, m;

	inline void upd(int & x, int y) {
		(x += y) >= mo ? x -= mo : 0;
	}

	int solve() {
		rep (i, 0, n - 1) rep (j, 0, i - 1) {
			upd(f[i][j], 1);
			int mi = i;
			rep (k, 0, m - 1) {
				if (segs[k].y >= i && segs[k].x <= j)
					upmax(mi, segs[k].y);
			}
			rep (k, mi + 1, n - 1)  upd(f[k][i], f[i][j]);
		}
		int ans = n + 1;
		rep (i, 0, n - 1) rep (j, 0, i - 1) 
			upd(ans, f[i][j]);
		return ans;
	}

	//DP, 计数
	int count(int n, vector<string> L, vector<string> R) {
		this->n = n;
		int x;
		stringstream ss;
		rep (i, 0, L.size() - 1)  ss << L[i];
		while (ss >> x)  segs[m++].x = x;
		ss.clear();
		rep (i, 0, R.size() - 1)  ss << R[i];
		rep (i, 0, m - 1)  ss >> segs[i].y;
		int ans = solve();
		return ans;
	}
};
