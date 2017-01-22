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
const int N = 315;

class TheExperiment
{
public : 
	int a[N], n;
	int f[N][N][2], g[N];

	inline void upd(int & x, int y) {
		(x += y) >= mo ? x -= mo : 0;
	}

	int countPlacements(vector<string> board, int M, int L, int A, int B) {
		rep (i, 0, board.size() - 1) rep (j, 0, board[i].size() - 1)
			a[++n] = board[i][j] - '0';
		f[0][0][0] = 1;
		g[0] = 1;
		rep (i, 1, n) {
			int s = a[i];
			down (j, i - 1, max(i - L, 0)) {
				if (s >= A && s <= B) {
					int h = (i - j == L);
					rep (k, 0, M - 1) {
						upd(f[i][k + 1][h], f[j][k][0]);
						upd(f[i][k + 1][1], f[j][k][1]);
					}
				}
				s += a[j];
				if (s > B)  break ;
			}
			rep (k, 0, M) {
				upd(f[i][k][0], g[k]);
				upd(g[k], f[i][k][1]);
			}
		}
		return g[M];
	}
};
