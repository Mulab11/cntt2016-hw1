#line 5 "CharacterBoard.cpp"
#include <bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for (int i = (a), _end_ = (b); i < _end_; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define mp make_pair
#define x first
#define y second
#define pb push_back
#define SZ(x) (int((x).size()))
#define ALL(x) (x).begin(), (x).end()

template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

typedef long long LL;

const int oo = 0x3f3f3f3f;

const int Mod = 1e9 + 9;

const int maxn = 10;

int g[maxn + 1][maxn + 1];

int n, m;

map<int, vector<pair<int, int> > > all;

inline int fpm(LL b, int e, int m)
{
	b %= m;
	LL t = 1;
	for ( ; e; e >>= 1, (b *= b) %= m)
		if (e & 1) (t *= b) %= m;
	return t;
}

class CharacterBoard
{
	public:
		int countGenerators(vector <string> fragment, int W, int, int)
		{
			n = SZ(fragment), m = SZ(fragment[0]);
			REP(i, 0, n) REP(j, 0, m) g[i][j] = fragment[i][j] - 'a'; 
			all.clear();
			REP(i, 0, n)
			{
				REP(j, -m + 1, m)
				{
					LL tmp = (LL)i * W + j;
					if (tmp <= 0) continue;
					for (LL k = 1; k * k <= tmp; ++k)
						if (!(tmp % k))
						{
							if (k <= W) all[k].pb(mp(i, j));
							if (k * k != tmp && tmp / k <= W) all[tmp / k].pb(mp(i, j));
						}
				}
			}
			int ret = LL(fpm(26, W + 1, Mod) - 1) * fpm(25, Mod - 2, Mod) % Mod;
			int ret0 = 0;
			(ret -= 1) %= Mod;
			for (auto it : all)
			{
				(ret -= fpm(26, it.x, Mod)) %= Mod;
				set<int> vis;
				REP(u, 0, n)
					REP(v, 0, m)
					{
						vis.insert(((LL)u * W + v) % it.x);
						for (auto it0 : it.y)
						{
							int x = u + it0.x, y = v + it0.y;
							if (x < n && y >= 0 && y < m) if (g[u][v] != g[x][y]) goto lyc;
						}
					}
				(ret0 += fpm(26, it.x - SZ(vis), Mod)) %= Mod;
lyc:;
			}
			ret = (LL)ret * fpm(26, Mod - 1 - n * m, Mod) % Mod;
			(ret += ret0) %= Mod;
			(ret += Mod) %= Mod;
			return ret;
		}
		

};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
