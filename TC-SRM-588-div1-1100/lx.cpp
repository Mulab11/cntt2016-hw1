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

class GameInDarknessDiv1 {
private :
	vector<string> B;
	int n, m;
	int dis[2][51][51];

	inline bool inBoard(int x, int y) {
		return x >= 0 && x < n && y >= 0 && y < m;
	}

	void Bfs(int t, int x, int y) {
		queue<pii> Q;
		memset(dis[t], -1, sizeof(dis[t]));
		dis[t][x][y] = 0;
		Q.push(mp(x, y));
		while (!Q.empty()) {
			pii u = Q.front();
			Q.pop();
			rep (d, 0, 3) {
				pii v(u.x + dx[d], u.y + dy[d]);
				if (inBoard(v.x, v.y) && B[v.x][v.y] != '#' && dis[t][v.x][v.y] == -1) {
					dis[t][v.x][v.y] = dis[t][u.x][u.y] + 1;
					Q.push(v);
				}
			}
		}
	}
	int Dfs(int x, int y, int tx, int ty) {
		if (!inBoard(x, y) || B[x][y] == '#')  return 0;
		int res = 0;
		rep (d, 0, 3) {
			if (!(x + dx[d] == tx && y + dy[d] == ty)) {
				upmax(res, Dfs(x + dx[d], y + dy[d], x, y));
			}
		}
		return res + 1;
	}
public :
	//结论题
	string check(vector<string> board) {
		B = board;
		n = B.size(), m = B[0].size();
		rep (i, 0, n-1) rep (j, 0, m-1) {
			if (board[i][j] == 'A') {
				Bfs(0, i, j);
			} else if (board[i][j] == 'B') {
				Bfs(1, i, j);
			}
		}
		rep (i, 0, n-1) rep (j, 0, m-1) {
			if (B[i][j] != '#' && dis[0][i][j] >= dis[1][i][j] + 2) {
				int cnt = 0;
				rep (d, 0, 3) {
					cnt += Dfs(i + dx[d], j + dy[d], i, j) >= 3;
				}
				if (cnt >= 3) {
					return "Bob wins";
				}
			}
		}
		return "Alice wins";
	}
};
