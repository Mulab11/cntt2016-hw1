#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#define NiroBC
const long long MOD = 1000000009;
char fragment[10][10];
int W, N, n, m, D, L, cnt[50], E;
long long pr[50], d[2000000];
void dfs(int k, long long s)
{
	if (k == D)
		d[++L] = s;
	else
		for (int i = 0; i <= cnt[k]; i++)
			dfs(k + 1, s), s *= pr[k];
}
void list(long long w)
{
	D = 0;
	for (long long i = 2; i * i <= w; i++)
		if (w % i == 0)
		{
			pr[D] = i, cnt[D] = 0;
			while (w % i == 0)
				w /= i, cnt[D]++;
			D++;
		}
	if (w > 1)
		pr[D] = w, cnt[D++] = 1;
	dfs(0, 1);
}
long long POWER(long long a, long long b)
{
	long long r = 1;
	for (; b; b >>= 1)
	{
		if (b & 1)
			r = r * a % MOD;
		a = a * a % MOD;
	}
	return r;
}
long long segPOWER(long long a, long long l, long long r)
{
	return (POWER(a, r + 1) - POWER(a, l) + MOD) * POWER(a - 1, MOD - 2) % MOD;
}
struct stupid
{
	int A;
	char B;
}
p[23333];
inline bool operator < (const stupid &a, const stupid &b)
{
	return a.A < b.A;
}
int MAIN()
{
	L = 0;
	for (int i = 1; i < m; i++)
		list(i);
	for (int j = 1; j < n; j++)
		for (int k = -m + 1; k < m; k++)
			list((long long)j * W + k);
	std::sort(d + 1, d + L + 1);
	bool prin = 0;
	L = std::unique(d + 1, d + L + 1) - d - 1;
	long long S = 0;
	if (d[1] > 1)
		S = (S + segPOWER(26, 1 - n * m, d[1] - 1 - n * m)) % MOD;
	while (d[L] > W)
		L--;
	for (int i = 1; i < L; i++)
		if (d[i + 1] - d[i] > 1)
			S = (S + segPOWER(26, d[i] + 1 - n * m, d[i + 1] - 1 - n * m)) % MOD;
	if (d[L] < W)
		S = (S + segPOWER(26, d[L] + 1 - n * m, W - n * m)) % MOD;
	for (int i = 1; i <= L; i++)
	{
		E = 0;
		for (int x = 0; x < n; x++)
			for (int y = 0; y < m; y++)
				p[E++] = (stupid) { (int)(((long long)x * W + y) % d[i]), fragment[x][y] };
		std::sort(p, p + E);
		bool kill = 0;
		int s = n * m;
		for (int j = 1; j < E; j++)
			if (p[j - 1].A == p[j].A)
			{
				if (p[j - 1].B != p[j].B)
					kill = 1;
				s--;
			}
		if (!kill)
			S = (S + POWER(26, d[i] - s)) % MOD;
	}
	return S;
}
class CharacterBoard
{
	public :
		int countGenerators(std::vector < std::string > fragment, int W, int i0, int j0)
		{
			n = fragment.size(), m = fragment[0].length();
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					::fragment[i][j] = fragment[i][j];
			::W = W;
			return MAIN();
		}
};