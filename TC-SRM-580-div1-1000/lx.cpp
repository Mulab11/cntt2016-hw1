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

template<typename T> inline void upmax(T & x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T & x, T y) { x > y ? x = y : 0; }

const int inf = 0x3f3f3f3f;
const int N = 52;

class WallGameDiv1 {
private :
	int w2[N][N], w[N][N];
	int f[N][N][N][2];
	int n, m;
	int rec(int Row, int L, int R, int p) {
		int &ans = f[Row][L][R][p];
		if (ans < 0) {
			int pos = p ? R : L;
			if (Row == n - 1) {
				return ans = w[Row][pos];
			} else if (L == 0 && R == m-1) {
				return ans = w[Row][pos] + rec(Row + 1, pos, pos, 0);
			}
			ans = inf;
			if (p == 0) {
				if (L > 0)   upmin(ans, rec(Row, L - 1, R, 0));
				if (R < m-1) upmin(ans, rec(Row, L, R + 1, 1) + w2[Row][R] - w2[Row][L]);
			} else {
				if (L > 0)   upmin(ans, rec(Row, L - 1, R, 0) + w2[Row][R - 1] - w2[Row][L - 1]);
				if (R < m-1) upmin(ans, rec(Row, L, R + 1, 1));
			}
			ans = max(ans, rec(Row + 1, pos, pos, 0)) + w[Row][pos];
		}
		return ans;
	}
public :
	int play(vector<string> costs) {
		n = costs.size();
		m = costs[0].size();
		rep (i, 0, n - 1) {
			rep (j, 0, m - 1) {
				w[i][j] = costs[i][j] - '0';
				w2[i][j] = (j > 0 ? w2[i][j - 1] : 0) + w[i][j];
			}
		}
		if (m == 1) {
			int ans = 0;
			rep (i, 0, n - 1) 
				ans += w[i][0];
			return ans;
		}
		memset(f, -1, sizeof(f));
		int ans = inf;
		rep (i, 0, m - 1) {
			upmin(ans, rec(0, i, i, 0));
		}
		return ans;
	}
};
