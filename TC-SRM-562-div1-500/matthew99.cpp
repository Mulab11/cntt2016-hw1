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

template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

typedef long long LL;

const int maxn = 230;

typedef bitset<maxn + 5> bset;

const int oo = 0x3f3f3f3f;

template<typename T> inline vector<T> &extract(const vector<string> &x, vector<T> &a)
{
	istringstream in(accumulate(ALL(x), string()));
	int u;
	a.clear();
	while (in >> u) a.pb(u);
	return a;
}

int n, m;
vector<int> ax, ay, bx, by;

pair<int, int> a[(maxn << 1) + 5];

inline LL cross(const pair<int, int> &x, const pair<int, int> &y, const pair<int, int> &z)
{
	return LL(y.x - x.x) * (z.y - x.y) - LL(y.y - x.y) * (z.x - x.x);
}

class CheckerFreeness 
{
	public:
		string isFree(vector<string> whiteX, vector<string> whiteY, vector<string> blackX, vector<string> blackY) 
		{
			extract(whiteX, ax);
			extract(whiteY, ay);
			extract(blackX, bx);
			extract(blackY, by);
			n = SZ(ax), m = SZ(bx);
			REP(i, 0, n) a[i] = mp(ax[i], ay[i]);
			REP(i, 0, m) a[n + i] = mp(bx[i], by[i]);
			static bset le[(maxn << 1) + 5][(maxn << 1) + 5];
			REP(i, 0, n + m) REP(j, 0, n + m)
			{
				le[i][j] = bset();
				REP(k, 0, n) if (cross(a[i], a[j], a[k]) > 0) le[i][j][k] = 1;
			}
			REP(i, 0, n) REP(j, 0, m) REP(k, 0, m) if (cross(a[i], a[n + j], a[n + k]) > 0 && (le[n + k][i] & le[i][n + j] & le[n + k][n + j]).any()) return "NO";
			return "YES";
		}
};

// Powered by Greed 2.0-RC
