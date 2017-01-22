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

typedef pair<int, int> pii;

const int mo = 1e9 + 7;

inline int qpow(int x, int n) {
	int ans = 1;
	while (n) {
		if (n & 1)  ans = (LL) ans * x % mo;
		x = (LL) x * x % mo;
		n >>= 1;
	}
	return ans;
}

class GooseInZooDivOne {
public :
	vector<pii> pois;
	int lim, n, cnt[2];
	bool vis[2521];

	inline int dist(int x, int y) {
		return abs(pois[x].x - pois[y].x) + abs(pois[x].y - pois[y].y);
	}

	bool Bfs(int x) {
		queue<int> Q;
		int cnt = 0;
		vis[x] = 1;
		Q.push(x);
		while (!Q.empty()) {
			int u = Q.front();
			Q.pop();
			++cnt;
			rep (i, 0, n - 1) {
				if (!vis[i] && dist(u, i) <= lim) {
					vis[i] = 1;
					Q.push(i);
				}
			}
		}
		return cnt & 1;
	}

	int count(vector<string> field, int lim) {
		this->lim = lim;
		rep (i, 0, field.size() - 1) rep (j, 0, field[0].size()) {
			if (field[i][j] == 'v') 
				pois.pb(mp(i, j));
		}
		n = pois.size();
		rep (i, 0, n - 1)
			if (!vis[i])  cnt[Bfs(i)]++;
		int ans = qpow(2, cnt[0]);
		if (cnt[1] > 1)  ans = (LL) ans * qpow(2, cnt[1] - 1) % mo;
		return (--ans) < 0 ? ans + mo : ans;
	}
};
