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

class FoxAndFencing 
{
	public:
		string WhoCanWin(int mov1, int mov2, int rng1, int rng2, int d) 
		{
			if (d <= mov1 + rng1) return "Ciel";
			if (d + mov1 <= mov2 + rng2) return "Liss";
			if (mov1 > mov2 && (mov2 << 1) + rng2 < mov1 + rng1) return "Ciel";
			if (mov2 > mov1 && (mov1 << 1) + rng1 < mov2 + rng2) return "Liss";
			return "Draw";
		}
};

// Powered by Greed 2.0-RC
