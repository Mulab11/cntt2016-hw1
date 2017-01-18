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

const int max0 = 300, max1 = 150, maxabs = 70;

int n;
int val[max0 + 5][max0 + 5];

class DrawingPointsDivOne 
{
	public:
		int maxSteps(vector<int> _x, vector<int> _y) 
		{
			n = SZ(_x);
			memset(val, 0, sizeof val);
			REP(i, 0, n) val[_x[i] + maxabs][_y[i] + maxabs] = 1;
			REP(t, 1, max1)
			{
				for (int i = max0 - 1; i >= 0; --i) for (int j = max0 - 1; j >= 0; --j) if (val[i][j] == 1) val[i + 1][j + 1] = val[i + 1][j] = val[i][j + 1] = 1;
				int tot = 0;
				for (int i = max0 - 1; i >= 0; --i) for (int j = max0 - 1; j >= 0; --j) if (val[i][j])
				{
					val[i][j] = min({val[i + 1][j], val[i][j + 1], val[i + 1][j + 1]}) + 1;
					if (val[i][j] > t) ++tot;
				}
				if (tot > n) return t - 1;
			}
			return -1;
		}
};

// Powered by Greed 2.0-RC
