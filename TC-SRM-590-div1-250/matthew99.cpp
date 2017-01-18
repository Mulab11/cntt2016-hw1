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

class FoxAndChess 
{
	public:
		string ableToMove(string a, string b) 
		{
			int n = SZ(a);
			vector<pair<int, int> > u, v;
			REP(i, 0, n) if (a[i] == 'L') u.pb(mp(-1, i)); else if (a[i] == 'R') u.pb(mp(1, i));
			REP(i, 0, n) if (b[i] == 'L') v.pb(mp(-1, i)); else if (b[i] == 'R') v.pb(mp(1, i));
			if (SZ(u) != SZ(v)) return "Impossible";
			REP(i, 0, SZ(u))
			{
				if (u[i].x != v[i].x) return "Impossible";
				if ((v[i].y - u[i].y) / u[i].x < 0) return "Impossible";
			}
			return "Possible";
		}
};

// Powered by Greed 2.0-RC
