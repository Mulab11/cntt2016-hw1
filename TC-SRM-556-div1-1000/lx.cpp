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

class netWork
{
private : 
	struct edge
	{
		int to, c, n;
	} e[N * N * 4];

	int head[N], tot;
	int d[N], S, T;

	bool Bfs()
	{
		queue<int> Q;
		memset(d, -1, sizeof(int) * (T + 3));
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
		return d[T] != -1;
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
		memset(head, 0, sizeof(head));
		tot = 1;
		S = s;
		T = t;
	}

	inline void addEdge(int x, int y, int c, int d = 0)
	{
		e[++tot] = (edge) {y, c, head[x]}, head[x] = tot;
		e[++tot] = (edge) {x, d, head[y]}, head[y] = tot;
	}

	int Run()
	{
		int ans = 0;
		while (Bfs())
			ans += Dfs(S, inf);
		return ans;
	}
} net;

class OldBridges
{
public : 
	vector<string> G;
	int n;

	bool check(int a1, int a2, int an, int b1, int b2, int bn)
	{
		int S = n, T = n + 1;
		net.init(S, T);
		net.addEdge(S, a1, an * 2);
		net.addEdge(a2, T, an * 2);
		net.addEdge(S, b1, bn * 2);
		net.addEdge(b2, T, bn * 2);
		rep (i, 0, n - 1) rep (j, i + 1, n - 1)
		{
			if (G[i][j] == 'N')
				net.addEdge(i, j, inf, inf);
			else if (G[i][j] == 'O')
				net.addEdge(i, j, 2, 2);
		}
		return net.Run() == (an + bn) * 2;
	}

	string isPossible(vector<string> G, int a1, int a2, int an, int b1, int b2, int bn)
	{
		n = G.size();
		this->G = G;
		bool f = check(a1, a2, an, b1, b2, bn) && check(a1, a2, an, b2, b1, bn);
		return f ? "Yes" : "No";
	}
};

int main()
{
#ifdef LX_JUDGE
	freopen("in.txt", "r", stdin);
#endif
	return 0;
}
