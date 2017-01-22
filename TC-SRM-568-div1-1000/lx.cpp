#include <bits/stdc++.h>

#define x first
#define y second
#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)

using namespace std;

const int N = 61;

typedef long long LL;
typedef double ld;

inline bool inter(pair<int, int > a, pair<int , int > b)
{
	if (a.x > b.x)
		swap(a, b);
	return a.x < b.x && a.y > b.x && a.y < b.y;
}

namespace work0
{
	int n, m;
	int col[N], a[N], tot;
	vector<int > lable;
	vector<pair<int, int> > line;

	bool Dfs(int x)
	{
		rep (y, 0, m - 1) if (inter(line[x], line[y]))
		{
			if (col[y] == 0)
			{
				col[y] = col[x] ^ 1;
				if (!Dfs(y))
					return 0;
			}
			else if (col[y] == col[x])
				return 0;
		}
		return 1;
	}

	bool check()
	{
		line.clear();
		rep (i, 0, n - 1) rep (j, i + 1, n - 1)
		{
			if (a[i] == a[j])
				line.push_back(make_pair(i, j));
		}
		memset(col, 0, sizeof(col));
		rep (i, 0, m - 1) if (!col[i])
		{
			col[i] = 2;
			if (!Dfs(i))
				return 0;
		}
		return 1;
	}

	bool search(int step)
	{
		if (step == n)
			return check();
		if (lable[step] != -1 || a[step] != 0)
		{
			if (lable[step] != -1)
				a[step] = lable[step];
			return search(step + 1);
		}
		rep (to, step + 1, n - 1) if (lable[to] == -1 && a[to] == 0)
		{
			a[step] = a[to] = ++tot;
			if (search(step + 1))
				return 1;
			a[step] = a[to] = 0;
			--tot;
		}
		return 0;
	}

	bool main(vector<int> lable)
	{
		memset(a, 0, sizeof(a));
		work0::lable = lable;
		n = lable.size();
		m = n >> 1;
		tot = 0;
		return search(0);
	}
};

namespace work1
{
	const int N = 61;

	int kind[N], n, m;

	vector<int > lable;
	vector<pair<int , int > > line;

	int fa[N], dis[N];

	int findSet(int x)
	{
		if (x == fa[x])	
			return x;
		int d = findSet(fa[x]);
		dis[x] ^= dis[fa[x]];
		return fa[x] = d;
	}

	vector<pair<pair<int , int >, int > > limit;

    int check()
    {
		rep (i, 0, n) 
		{
			fa[i] = i;
			dis[i] = 0;
		}

		limit.clear();
		int x, y, z, a, b;

		rep (i, 0, m - 1)
		{
			int o = kind[i];
			a = line[i].x;
			b = line[i].y;
			limit.push_back(make_pair(make_pair(a, a + 1), o));
			limit.push_back(make_pair(make_pair(b, b + 1), o));
			int sum = b - a + 1;
			if (o || !(sum & 1))
				limit.push_back(make_pair(make_pair(a, b + 1), 0));
			else
				limit.push_back(make_pair(make_pair(a, b + 1), 1));
		}

		limit.push_back(make_pair(make_pair(0, n), n & 1));

		rep (i, 0, limit.size() - 1)
		{
			x = limit[i].x.x;
			y = limit[i].x.y;
			z = limit[i].y;
			a = findSet(x);
			b = findSet(y);
			if (a != b)
			{
				dis[a] = dis[x] ^ dis[y] ^ z;
				fa[a] = b;
			}
			else if ((dis[x] ^ dis[y]) != z)
				return 0;
        }

		return 1;
    }

	bool search(int step)
	{
		if (step == m)
			return check();
		rep (now, 0, 1)
		{
			int j = 0;
			kind[step] = now;
			for ( ; j < step; ++j)
			{
				if (kind[j] == kind[step] && inter(line[j], line[step]))
					break ;
			}
			if (j == step && search(step + 1))
				return 1;
		}
		return 0;
	}

	int vis[N];

	bool main(vector<int > lable)
	{
		memset(vis, -1, sizeof(vis));

		work1::lable = lable;
		n = lable.size();

		rep (i, 0, n - 1) if (lable[i] != -1)
		{
			if (~vis[lable[i]])
				line.push_back(make_pair(vis[lable[i]], i));
			else
				vis[lable[i]] = i;
		}

		m = line.size();
		return search(0);
	}
};

class DisjointSemicircles {
public:
	int vis[N];

	string getPossibility(vector<int > s)
	{
		memset(vis, -1, sizeof(vis));

		int num0 = 0;
		int cnt = s.size() / 2;

		rep (i, 0, s.size() - 1)
		{
			if (s[i] == -1)
				++num0;
			else
			{
				if (~vis[s[i]])
					s[i] = s[vis[s[i]]] = cnt--;
				else
					vis[s[i]] = i;
			}
		}

		bool ans = num0 <= 12 ? work0::main(s) : work1::main(s);
		return ans ? "POSSIBLE" : "IMPOSSIBLE";
	}
};

int main()
{
	return 0;
}
