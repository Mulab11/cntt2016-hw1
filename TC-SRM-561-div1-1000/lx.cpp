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

const int N = 2505;
const int M = 305;

class Orienteering
{
public : 
	int id[51][51];
	vector<int> adj[N];
	vector<int> pot;
	int col[N], n, m;

	inline void addEdge(int x, int y)
	{
		adj[x].pb(y);
		adj[y].pb(x);
	}

	int dis[M][M], *nowdis;

	void Dfs(int x, int fa, int d)
	{
		if (col[x])
			nowdis[col[x]] = d;
		rep (i, 0, adj[x].size() - 1)
		{
			int to = adj[x][i];
			if (to == fa)
				continue ;
			Dfs(to, x, d + 1);
		}
	}

	int getNum(int x, int fa)
	{
		int cnt = col[x] > 0;
		rep (i, 0, adj[x].size() - 1)
		{
			int to = adj[x][i];
			if (to == fa)
				continue ;
			cnt += getNum(to, x);
		}
		return cnt;
	}

	double expectedLength(vector<string> board, int K)
	{
		n = m = 0;

		rep (i, 0, board.size() - 1)
		{
			rep (j, 0, board[i].size() - 1)
			{
				if (board[i][j] != '#')
				{
					id[i][j] = ++n;
					if (board[i][j] == '*')
					{
						col[n] = ++m;
						pot.pb(n);
					}
					if (i > 0 && id[i - 1][j])
						addEdge(id[i - 1][j], n);
					if (j > 0 && id[i][j - 1])
						addEdge(id[i][j - 1], n);
				}
			}
		}

		rep (i, 0, m - 1)
		{
			nowdis = dis[i + 1];
			Dfs(pot[i], 0, 0);
		}

		static double f[M];

		f[m] = 1.0;
		down (i, m, 1)
			f[i - 1] = f[i] / i * (i - K);

		double sum = 0;

		rep (i, 1, n)
		{
			rep (j, 0, adj[i].size() - 1)
			{
				int to = adj[i][j];
				if (i < to)
				{
					int cnt = getNum(i, to);
					sum += 1.0 - f[cnt] - f[m - cnt];
				}
			}
		}

		f[m - 2] = 1.0;
		down (i, m - 2, 1)
			f[i - 1] = f[i] / i * (i + 2 - K);

		double dia = 0;

		rep (i, 1, m) rep (j, i + 1, m)
		{
			int cnt = 0;

			rep (k, 1, m)
			{
				if (k != i && k != j)
				{
					if (dis[i][k] > dis[i][j] || (dis[i][k] == dis[i][j] && k < j))
						continue ;
					if (dis[j][k] > dis[j][i] || (dis[j][k] == dis[j][i] && k < i))
						continue ;
					++cnt;
				}
			}

			dia += dis[i][j] * f[cnt];
		}

		dia *= (K - 1.0) * K / ((m - 1.0) * m);

		return sum * 2 - dia;
	}
};
