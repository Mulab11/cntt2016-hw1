#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
int f[2500], n, m, N, u, v, E;
struct edge
{
	int u, v, w;
}
p[10000];
inline bool operator < (const edge &a, const edge &b)
{
	return a.w < b.w;
}
inline int id(int x, int y)
{
	return x * m + y;
}
int F(int x)
{
	return f[x] == x ? x : f[x] = F(f[x]);
}
class ArcadeManao
{
	public :
		int shortestLadder(std::vector < std::string > A, int x, int y)
		{
			n = A.size(), m = A[0].length();
			N = n * m;
			for (int i = 0; i < N; i++)
				f[i] = i;
			u = id(n - 1, 0), v = id(x - 1, y - 1);
			E = 0;
			for (int i = 0; i < n; i++)
				for (int j = 1; j < m; j++)
					if (A[i][j] == 'X' && A[i][j - 1] == 'X')
						p[E++] = (edge) { id(i, j), id(i, j - 1), 0 };
			for (int i = 0; i < m; i++)
			{
				int fir = 0;
				while (fir < n && A[fir][i] == '.')
					fir++;
				for (int j = fir + 1; j < n; j++)
					if (A[j][i] == 'X')
						p[E++] = (edge) { id(fir, i), id(j, i), j - fir }, fir = j;
			}
			std::sort(p, p + E);
			if (F(u) == F(v))
				return 0;
			for (int i = 0; i < E; i++)
			{
				int U = F(p[i].u), V = F(p[i].v);
				if (U != V)
					f[U] = V;
				if (F(u) == F(v))
					return p[i].w;
			}
			return -23423;
		}
};