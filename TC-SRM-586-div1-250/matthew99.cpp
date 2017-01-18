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

int n;

class PiecewiseLinearFunction 
{
	public:
		int maximumSolutions(vector<int> Y) 
		{
			int ret = 0;
			n = SZ(Y);
			REP(i, 0, n - 1) if (Y[i] == Y[i + 1]) return -1;
			REP(i, 0, n)
			{
				int tmp = Y[i];
				int cnt = 0;
				REP(j, 0, n) if (Y[j] == tmp) ++cnt;
				REP(j, 0, n - 1) if (LL(tmp - Y[j]) * (tmp - Y[j + 1]) < 0) ++cnt;
				chkmax(ret, cnt);
			}
			REP(i, 0, n)
			{
				double tmp = Y[i] - .5;
				int cnt = 0;
				REP(j, 0, n - 1) if ((tmp - Y[j]) * (tmp - Y[j + 1]) < 0) ++cnt;
				chkmax(ret, cnt);
			}
			return ret;
		}
};

// Powered by Greed 2.0-RC
