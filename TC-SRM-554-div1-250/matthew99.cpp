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

class TheBrickTowerEasyDivOne 
{
	public:
		int find(int redCount, int redHeight, int blueCount, int blueHeight) 
		{
			if (redHeight == blueHeight) return ((min(redCount, blueCount) + 1) << 1) - 1 - (redCount == blueCount);
			return (min(redCount, blueCount) + 1) * 3 - 2 - (redCount == blueCount);
		}
};

// Powered by Greed 2.0-RC
