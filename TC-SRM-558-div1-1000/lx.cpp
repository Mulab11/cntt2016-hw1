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

const int inf = 0x3f3f3f3f;
const int N = 825;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

class netWork
{
private :
	struct edge
	{
		int to, c, n;
	} e[N * 101];

	int head[N], tot;
	int d[N], S, T;

	bool Bfs()
	{
		static queue<int> Q;
		memset(d, -1, sizeof(d));
		d[S] = 0;
		Q.push(S);
		while (!Q.empty())
		{
			int u = Q.front();
			Q.pop();
			for (int p = head[u]; p; p = e[p].n)
			{
				if (e[p].c && d[e[p].to] == -1)
				{
					d[e[p].to] = d[u] + 1;
					Q.push(e[p].to);
				}
			}
		}
		return d[T] >= 0:
	}

	int Dfs(int x, int f)
	{
		if (x == T)
			return f;
		int a = f;
		for (int p = head[x]; p; p = e[p].n)
		{
			if (e[p].c && d[e[p].to] == d[x] + 1)
			{
				int t = Dfs(e[p].to, min(a, e[p].c));
				e[p].c -= t;
				e[p ^ 1].c += t;
				a -= t;
				if (!a)
					break ;
			}
		}
		if (a)
			d[x] = -1;
		return f - a;
	}
public : 
	inline void init(int s, int t)
	{
		S = s;
		T = t;
		tot = 1;
	}

	inline void addEdge(int x, int y, int c)
	{
		e[++tot] = (edge) {y, c, head[x]}, head[x] = tot;
		e[++tot] = (edge) {x, 0, head[y]}, head[y] = tot;
	}

	int Run()
	{
		int ans = 0;
		while (Bfs())
			ans += Dfs(S, inf);
		return ans;
	}
} my;

class SurroundingGame
{
public : 
	int n, m;

	inline bool in(int x, int y)
	{
		return x >= 0 && x < n && y >= 0 && y < m;
	}

	inline int id(int x, int y)
	{
		return x * m + y;
	}

	inline int getV(char c)
	{
		if (c >= '0' && c <= '9')
			return c - '0';
		if (c >= 'a' && c <= 'z')
			return c - 'a' + 10;
		return c - 'A' + 36;
	}

	int maxScore(vector<string> cost, vector<string> val)
	{
		n = cost.size();
		m = cost[0].size();
		int tot = n * m;
		int S = tot * 2, T = S + 1;
		int sum = 0;
		my.init(S, T);
		rep (i, 0, n - 1) rep (j, 0, m - 1)
		{
			int a = getV(cost[i][j]);
			int b = getV(val[i][j]);
			sum += b;
			if ((i + j) & 1)
			{
				int e = id(i, j);
				my.addEdge(S, e, a);
				my.addEdge(e, e + tot, b);
				rep (d, 0, 3)
				{
					int x = i + dx[d], y = j + dy[d];
					if (in(x, y))
						my.addEdge(e + tot, id(x, y), inf);
				}
			}
			else
			{
				int e = id(i, j);
				my.addEdge(e, T, a);
				my.addEdge(e + tot, e, b);
				rep (d, 0, 3)
				{
					int x = i + dx[d], y = j + dy[d];
					if (in(x, y))
						my.addEdge(id(x, y), e + tot, inf);
				}
			}
		}
		int ans = sum - my.Run();
		return ans;
	}
};
