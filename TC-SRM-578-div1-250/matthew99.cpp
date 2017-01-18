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

const int oo = 0x3f3f3f3f;

const int maxn = 60;

const int Mod = 1e9 + 7;

int fa[maxn * maxn + 5];

int get(int x) { return fa[x] == x ? x : fa[x] = get(fa[x]); }

class GooseInZooDivOne 
{
	public:
		int count(vector<string> g, int d) 
		{
			int n = SZ(g), m = SZ(g[0]);
			vector<pair<int, int> > all;
			REP(i, 0, n) REP(j, 0, m) if (g[i][j] == 'v') all.pb(mp(i, j));
			int N = SZ(all);
			REP(i, 0, N) fa[i] = i;
			REP(i, 0, N) REP(j, 0, i) if (abs(all[i].x - all[j].x) + abs(all[i].y - all[j].y) <= d) fa[get(i)] = get(j);
			int dp[2] = {1, 0};
			REP(i, 0, N) if (fa[i] == i)
			{
				int sta = 0;
				REP(j, 0, N) if (get(j) == i) sta ^= 1;
				int nxt[2] = {dp[0], dp[1]};
				REP(j, 0, 2) (nxt[j ^ sta] += dp[j]) %= Mod;
				memcpy(dp, nxt, sizeof dp);
			}
			int ret = (dp[0] - 1) % Mod;
			(ret += Mod) %= Mod;
			return ret;
		}
};

// Powered by Greed 2.0-RC
