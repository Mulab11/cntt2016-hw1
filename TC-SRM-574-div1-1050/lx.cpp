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

const int inf = 0x3f3f3f3f;
const int N = 55;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

class Tunnels
{
public : 
	int n, m;
	vector<string> frame;
	int col[N][N], tot;
	int deg[N][N], mi[N * N], mx[N * N];
	bool Lu[N], Ld[N], Ru[N], Rd[N], LR[N];
	int dp[N][N][N];

	inline bool in(int x, int y) 
	{
		return x >= 0 && x < n && y >= 0 && y < m;
	}

	void Dfs(int x, int y, int c) 
	{
		col[x][y] = c;
		rep (d, 0, 3) 
		{
			int _x = x + dx[d], _y = y + dy[d];
			if (in(_x, _y) && frame[_x][_y] == 'X' && col[_x][_y] == -1)
				Dfs(_x, _y, c);
		}
	}

	int solve() 
	{
		rep (i, 0, n) rep (j, 0, n)
			dp[n][i][j] = -inf;
		dp[n][0][0] = 0;
		down (pos, n - 1, 0) 
		{
			rep (i, 0, pos) rep (j, 0, pos) 
			{
				dp[pos][i][j] = -inf;
				rep (a, -1, 1) rep (b, -1, 1) 
				{
					if ((a != 1  || Ld[pos]) &&
						(a != -1 || Lu[pos]) && 
						(b != 1  || Rd[pos]) &&
						(b != -1 || Ru[pos]) &&
						(a != b || a == 0 || !LR[pos]) &&
						(i + a >= 0 && j + b >= 0) ) 
					{
						int val = dp[pos + 1][i + a][j + b] + (a == 1) + (b == 1);
						upmax(dp[pos][i][j], val);
					}
				}
			}
		}
		return dp[0][0][0];
	}

	int minimumTunnels(vector<string> frame)
	{
		n = frame.size(), m = frame[0].size();
		this->frame = frame;
		rep (i, 0, n - 1) rep (j, 0, m - 1)
			col[i][j] = -1;
		rep (i, 0, n - 1) rep (j, 0, m - 1) 
		{
			if (frame[i][j] == 'X' && col[i][j] == -1)
				Dfs(i, j, tot++);
		}
		if (m == 1) 
		{
			bool flag = 0;
			rep (i, 0, n - 1)
				flag |= frame[i][0] == 'X';
			return flag;
		}
		rep (i, 0, n - 1) rep (j, 0, m - 1) 
		{
			if (col[i][j] != -1) 
			{
				rep (d, 0, 3) 
				{
					int x = i + dx[d], y = j + dy[d];
					if (in(x, y) && col[x][y] != -1)
						++deg[i][j];
				}
			}
		}
		rep (i, 0, tot - 1) 
		{
			mi[i] = n;
			mx[i] = -1;
		}
		rep (i, 0, n - 1) rep (j, 0, m - 1) 
		{
			if (col[i][j] != -1) 
			{
				upmin(mi[col[i][j]], i);
				upmax(mx[col[i][j]], i);
			}
		}
		rep (i, 0, n - 1) 
		{
			if (col[i][0] != -1 && deg[i][0] <= 1) 
			{
				Lu[i] = (i == mi[col[i][0]]);
				Ld[i] = (i == mx[col[i][0]]);
			}
			if (col[i][m - 1] != -1 && deg[i][m - 1] <= 1) 
			{
				Ru[i] = (i == mi[col[i][m - 1]]);
				Rd[i] = (i == mx[col[i][m - 1]]);
			}
		}
		rep (i, 2, n - 1) 
		{
			Ld[i] = Ld[i] && !Lu[i - 1];
			Rd[i] = Rd[i] && !Ru[i - 1];
		}
		rep (i, 0, n - 1)
			LR[i] = (col[i][0] != -1 && col[i][0] == col[i][m - 1]);
		rep (i, 1, n - 1) 
		{
			int c1 = col[i][0], c2 = col[i][m - 1];
			if (c1 != c2) 
			{
				Ld[i] = Ld[i] && (c1 == -1 || mi[c1] != mx[c1]);
				Rd[i] = Rd[i] && (c2 == -1 || mi[c2] != mx[c2]);
			}
		}
		int ans = tot - solve();
		return ans;
	}
};

