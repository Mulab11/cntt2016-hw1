#include <bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for (int i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define mp make_pair
#define x first
#define y second
#define pb push_back
#define SZ(x) (int((x).size()))
#define ALL(x) (x).begin(), (x).end()

#define bcnt(x) __builtin_popcountll(x)
#define ctz(x) __builtin_ctzll(x)

template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

typedef long long LL;

const int oo = 0x3f3f3f3f;

const int maxn = 52;

int n;
int a[maxn + 5];
LL g[maxn + 5];

int ans;

void dfs(const LL &r, LL p, LL x, int sum = 0)
{
	if (!p && !x)
	{
		if (bcnt(r) * 3 >= 2 * n) chkmax(ans, sum);
		return;
	}
	int u = ctz(p | x);
	for (LL cur = p & ~g[u]; cur; cur ^= cur & -cur)
	{
		int v = ctz(cur);
		dfs(r | (1LL << v), p & g[v], x & g[v], sum + a[v]);
		p ^= 1LL << v;
		x ^= 1LL << v;
	}
}

class MagicMolecule 
{
	public:
		int maxMagicPower(vector<int> _a, vector<string> _g) 
		{
			n = SZ(_a);
			REP(i, 0, n) a[i] = _a[i];
			REP(i, 0, n)
			{
				g[i] = 0;
				REP(j, 0, n) if (_g[i][j] == 'Y')
				{
					g[i] |= 1LL << j;
				}
			}
			ans = -1;
			dfs(0, (1LL << n) - 1, 0, 0);
			return ans;
		}
};

// Powered by Greed 2.0-RC
