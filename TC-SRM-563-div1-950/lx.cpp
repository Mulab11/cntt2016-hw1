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

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

const int mo = 1e9 + 9;
const int N = 1605;

typedef pair<int, int> pii;

class CoinsGame
{
public : 
	int id[41][41], tot;
	pii loc[N];
	bool can[N][N];
	int pow_2[N];
	int n, m;

	inline bool in(pii a)
	{
		return a.x >= 0 && a.x < n && a.y >= 0 && a.y < m;
	}

	queue<pii> Q;

	void insert(int x, int y)
	{
		if (x > y)
			swap(x, y);
		if (x != y && !can[x][y])
		{
			can[x][y] = 1;
			Q.push(pii(x, y));
		}
	}

	int size[N], fa[N];

	inline int findSet(int x)
	{
		return fa[x] == x ? x : fa[x] = findSet(fa[x]);
	}

	int ways(vector<string> board)
	{
		n = board.size();
		m = board[0].size();

		rep (i, 0, n * m)
			fa[i] = i;

		tot = 0;

		rep (i, 0, n - 1) rep (j, 0, m - 1)
		{
			if (board[i][j] == '.')
			{
				id[i][j] = ++tot;
				loc[tot] = pii(i, j);
				int o = id[i][j];
				if (i == 0 || i == n - 1 || j == 0 || j == m - 1)
					fa[findSet(o)] = findSet(0);
				if (i > 0 && id[i - 1][j])
					fa[findSet(o)] = findSet(id[i - 1][j]);
				if (j > 0 && id[i][j - 1])
					fa[findSet(o)] = findSet(id[i][j - 1]);
			}
		}

		findSet(0);

		tot = 0;
		int num = 1;

		rep (i, 0, n - 1) rep (j, 0, m - 1)
		{
			if (id[i][j])
			{
				int o = id[i][j];
				if (findSet(o) == fa[0])
				{
					id[i][j] = ++tot;
					loc[tot] = pii(i, j);
				}
				else
					(num <<= 1) >= mo ? num -= mo : 0;
			}
		}

		rep (i, 0, m - 1)
		{
			if (id[0][i])
			{
				int x = id[0][i];
				rep (j, 1, tot) 
				{
					if (loc[j].x > 0)
						insert(x, j);
				}
			}
			if (id[n - 1][i])
			{
				int x = id[n - 1][i];
				rep (j, 1, tot)
				{
					if (loc[j].x < n - 1)
						insert(x, j);
				}
			}
		}

		rep (i, 0, n - 1)
		{
			if (id[i][0])
			{
				int x = id[i][0];
				rep (j, 1, tot)
				{
					if (loc[j].y > 0)
						insert(x, j);
				}
			}
			if (id[i][m - 1])
			{
				int x = id[i][m - 1];
				rep (j, 1, tot)
				{
					if (loc[j].y < m - 1)
						insert(x, j);
				}
			}
		}

		while (!Q.empty())
		{
			pii u = Q.front();
			Q.pop();
			pii a = loc[u.x], b = loc[u.y];
			pii _a, _b;
			rep (d, 0, 3)
			{
				_a = pii(a.x + dx[d], a.y + dy[d]);
				_b = pii(b.x + dx[d], b.y + dy[d]);

				bool f1 = in(_a), f2 = in(_b);

				if (f1 && f2 && id[_a.x][_a.y] && id[_b.x][_b.y])
					insert(id[_a.x][_a.y], id[_b.x][_b.y]);

				if (f1 && !id[_a.x][_a.y])
				{
					pii tmp = pii(b.x - dx[d], b.y - dy[d]);
					if (in(tmp) && id[tmp.x][tmp.y])
						insert(u.x, id[tmp.x][tmp.y]);
				}
				if (f2 && !id[_b.x][_b.y])
				{
					pii tmp = pii(a.x - dx[d], a.y - dy[d]);
					if (in(tmp) && id[tmp.x][tmp.y])
						insert(id[tmp.x][tmp.y], u.y);
				}
			}
		}

		rep (i, 1, tot)
		{
			fa[i] = i;
			size[i] = 1;
		}

		rep (i, 1, tot) rep (j, i + 1, tot)
		{
			if (!can[i][j])
			{
				int x = findSet(i);
				int y = findSet(j);
				if (x != y)
				{
					fa[x] = y;
					size[y] += size[x];
				}
			}
		}

		pow_2[0] = 1;
		rep (i, 1, tot)
			(pow_2[i] = pow_2[i - 1] << 1) >= mo ? pow_2[i] -= mo : 0;

		int ans = pow_2[tot] - 1;

		rep (i, 1, tot) 
		{
			if (fa[i] == i)
				(ans -= pow_2[size[i]] - 1) < 0 ? ans += mo : 0;
		}

		ans = ((LL) (num - 1) * (pow_2[tot] - 1) + ans) % mo;

		return ans;
	}
};

