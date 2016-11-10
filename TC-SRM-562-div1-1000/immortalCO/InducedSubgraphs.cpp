#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;

const int mod = 1e9 + 9;

const int MaxN = 50;
int to[MaxN << 1];
vector<int> e[MaxN];

int f[MaxN << 1], c[MaxN << 1], comb[MaxN][MaxN], fac[MaxN];
ll p[MaxN << 1];
bool v[MaxN << 1];
int inv(int i) {return i == 1 ? 1 : mod - (ll) (mod / i) * inv(mod % i) % mod;}

int go_next(int i, int f)
{
	if(e[i].size() != 2u) return -1;
	for(int k = 0; k != 2; ++k)
		if(to[e[i][k]] != f) return to[e[i][k]];
	return -1;
}

void dp(int e)
{
	if(v[e]) return;
	v[e] = 1;
	c[e] = 0;
	f[e] = 1;
	for(int *k = &*::e[to[e]].begin(), *ke = &*::e[to[e]].end(); k != ke; ++k)
		if(*k != (e ^ 1))
		{
			dp(*k);
			c[e] += c[*k];
			f[e] = (ll) f[e] * f[*k] % mod * comb[c[e]][c[*k]] % mod;
		}
	++c[e];
}
int g[MaxN << 1][MaxN][MaxN], M, S;
// g(e, a, b) : 以 e 为根的子树内，两边集合的大小分别为 a、b
void add(int &a, int b) {(a += b) >= mod ? a -= mod : 0;}
void add_item(int f[MaxN][MaxN], int g[MaxN][MaxN], int F, int G)
{
#define dmin(a, b) ((a) < (b) ? (a) : (b))
	int Ta, Tb;
	static int h[MaxN][MaxN];
	for(int a = 0; a <= F && a <= S; ++a) for(int b = 0; a + b <= F && b <= S; ++b) h[a][b] = f[a][b], f[a][b] = 0;
	for(int fa = dmin(F, S); 		fa >= 0; --fa) for(int fb = dmin(F - fa, S); 		fb >= 0; --fb) if((Ta = h[fa][fb]))
		for(int ga = dmin(G, S - fa);	ga >= 0; --ga) for(int gb = dmin(G - ga, S - fb);	gb >= 0; --gb) if((Tb = g[ga][gb]))
			add(f[fa + ga][fb + gb], (ll) Ta * Tb % mod
				* comb[fa + ga][fa] % mod
				* comb[fb + gb][fb] % mod);
}
void calc(int e)
{
	if(v[e]) return;
	v[e] = 1;
	f[e] = 1;
	g[e][0][0] = 1;
	for(int *k = &*::e[to[e]].begin(), *ke = &*::e[to[e]].end(); k != ke; ++k)
		if(*k != (e ^ 1))
		{
			calc(*k);
			add_item(g[e], g[*k], c[e], c[*k]);
			c[e] += c[*k];
			f[e] = (ll) f[e] * f[*k] % mod * comb[c[e]][c[*k]] % mod;
		}
	++c[e];
	if(c[e] <= S) g[e][c[e]][0] = g[e][0][c[e]] = f[e];
	
}

class InducedSubgraphs
{
public:
	int getCount(vector<int> ex, vector<int> ey, int K)
	{
		const int N = ex.size() + 1;
		if(K == 1 || K == N)
		{
			// ans = N!
			int A = 1;
			for(int i = 1; i <= N; ++i) A = (ll) A * i % mod;
			return A;
		}
		comb[0][0] = 1;
		fac[0] = 1;
		for(int i = 1; i <= N; ++i)
		{
			fac[i] = (ll) fac[i - 1] * i % mod;
			comb[i][0] = comb[i][i] = 1;
			for(int j = 1; j != i; ++j)
				comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % mod;
		}
		for(int i = 0; i != N - 1; ++i)
		{
			e[ex[i]].push_back(i << 1 | 0), to[i << 1 | 0] = ey[i];
			e[ey[i]].push_back(i << 1 | 1), to[i << 1 | 1] = ex[i];
		}
		int A = 0;
		if(K * 2 <= N)
		{
			// The center part must be a chain
			// Two sides will be 2 subtrees
			for(int i = 0; i != ((N - 1) << 1); ++i) dp(i);
			for(int s = 0; s != ((N - 1) << 1); ++s) if(c[s] == K)
				for(int t = s + 1; t != ((N - 1) << 1); ++t) if(c[t] == K)
				{
					// check if chain(to[s^1], to[t^1]) is a chain
					int p = to[s ^ 1], lp = to[s], ep = to[t];
					for(int tmp; p != ep; )
					{
						tmp = lp, lp = p, p = go_next(p, tmp);
						if(p == -1) goto skipped_2;
					}
					// Check done!
					A = (A + 2ll * f[s] * f[t]) % mod;
				skipped_2: ;
				}
		}
		else
		{
			// enum the root
			M = K + K - N;
			S = K - M;
			static int f[MaxN][MaxN];
			for(int i = 0; i != N; ++i)
			{
				memset(f, 0, sizeof f);
				f[0][0] = 1;
				int C = 0;
				for(int *k = &*e[i].begin(), *ke = &*e[i].end(); k != ke; ++k)
					calc(*k), add_item(f, g[*k], C, c[*k]), C += c[*k];
				add(A, f[S][S]);
			}
			for(int i = 1; i != M; ++i) A = (ll) A * i % mod;
		}
		return A;
	}
}	user;
