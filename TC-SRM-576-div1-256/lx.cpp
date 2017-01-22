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

class ArcadeManao
{
public :
	int fa[2511];
	inline int findSet(int x) {
		return fa[x] == x ? x : fa[x] = findSet(fa[x]);
	}
	int id[55][55], tot, n, m;

	struct edge
	{
		int x, y, z;
		inline bool operator < (const edge & b) const {
			return z < b.z;
		}
	} e[5015];
	int num;

	int shortestLadder(vector<string> board, int x, int y)
	{
		n = board.size(), m = board[0].size();
		rep (i, 0, n - 1) rep (j, 0, m - 1) {
			if (board[i][j] == 'X') {
				id[i][j] = ++tot;
				down (k, i - 1, 0) {
					if (id[k][j]) {
						e[++num] = (edge) {id[k][j], id[i][j], i - k};
						break ;
					}
				}
				if (id[i][j - 1])
					e[++num] = (edge) {id[i][j - 1], id[i][j], 0};
			}
		}
		rep (i, 1, tot)  fa[i] = i;
		sort(e + 1, e + num + 1);
		x = id[x - 1][y - 1];
		y = id[n - 1][0];
		int ans = 0, i = 1;
		while (findSet(x) != findSet(y)) {
			fa[findSet(e[i].x)] = findSet(e[i].y);
			ans = e[i].z;
			i++;
		}
		return ans;
	}
};
