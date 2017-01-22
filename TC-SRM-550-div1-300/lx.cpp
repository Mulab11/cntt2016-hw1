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

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

inline int inmod(int x, int mo) {
	if (x < 0)   x += mo;
	if (x >= mo) x -= mo;
	return x;
}

class RotatingBot {
public :
	bool vis[200][200];
	int minx, maxx, miny, maxy;

	inline bool inBoard(int x, int y) {
		return x >= minx && x <= maxx && y >= miny && y <= maxy;
	}

	//大模拟术
	int minArea(vector<int> moves) {
		int x = 100, y = 100;
		minx = x, maxx = x, miny = y, maxy = y;
		memset(vis, 0, sizeof(vis));
		int d = 2;
		int tot = 0;
		rep (i, 0, moves.size()-1) {
			rep (j, 0, moves[i]-1) {
				int nx = x + dx[d], ny = y + dy[d];
				if (vis[nx][ny]) return -1;
				x = nx, y = ny;
				upmin(minx, x);
				upmax(maxx, x);
				upmin(miny, y);
				upmax(maxy, y);
				vis[x][y] = 1;
			}
			tot += moves[i];
			d = inmod(d + 1, 4);
		}
		x = 100, y = 100;
		d = 2;
		memset(vis, 0, sizeof(vis));
		vis[x][y] = 1;
		vector<int>moves2;
		int m = 0;
		rep (i, 0, tot-1) {
			int nx = x + dx[d], ny = y + dy[d];
			if (!inBoard(nx, ny) || vis[nx][ny]) {
				moves2.pb(m);
				m = 0;
				d = inmod(d + 1, 4);
				nx = x + dx[d], ny = y + dy[d];
				if (!inBoard(nx, ny) || vis[nx][ny]) {
					break ;
				}
			} 
			x = nx, y = ny;
			vis[x][y] = 1;
			m++;
		}
		if (m > 0)  moves2.pb(m);
		return moves == moves2 ? (maxx - minx + 1) * (maxy - miny + 1) : -1;
	}
};
