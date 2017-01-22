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

const int mo = 1e9 + 9;

inline int qpow(int x, int n) {
	int ans = 1;
	while (n) {
		if (n & 1)  ans = (LL) ans * x % mo;
		x = (LL) x * x % mo;
		n >>= 1;
	}
	return ans;
}
inline int inc(int x, int y) {
	return (x += y) >= mo ? x - mo : x;
}
inline int dec(int x, int y) {
	return (x -= y) < 0 ? x + mo : x;
}

class CharacterBoard {
public :
	vector<string> board;
	int n, m, W;
	inline void upd(int & x, int y) {
		(x += y) >= mo ? x -= mo : 0;
	}
	int calc(int v) {
		map<int, int> mp;
		int cnt = 0;
		rep (i, 0, n - 1) rep (j, 0, m - 1) {
			int & x = mp[((LL) W * i + j) % v];
			if (!x) {
				x = board[i][j];
				++cnt;
			 } else if (x != board[i][j]) {
				return 0;
			 }
		}
		return qpow(26, v - cnt);
	}
	int countGenerators(vector<string> board, int W, int i0, int j0) {
		this->board = board;
		n = board.size(), m = board[0].size();
		this->W = W;
		vector<int> vis;
		rep (i, 0, n - 1) {
			rep (j, -m + 1, m - 1) {
				LL v = abs((LL) W * i + j);
				for (LL x = 1; x * x <= v; ++x) {
					if (v % x == 0) {
						if (x <= W)  vis.pb(x);
						if (v / x <= W)  vis.pb(v / x);
					}
				}
			}
		}
		sort(vis.begin(), vis.end());
		vis.erase(unique(vis.begin(), vis.end()), vis.end());
		int tot = n * m;
		int ans = 0;
		if (W >= tot)
			ans = (LL) dec(qpow(26, W - tot + 1), 1) * qpow(25, mo - 2) % mo;
		rep (i, 0, vis.size() - 1) {
			int v = vis[i];
			if (v >= tot)  upd(ans, mo - qpow(26, v - tot));
			upd(ans, calc(v));
		}
		return ans;
	}
};
