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

class TriangleXor 
{
	public:
		int theArea(int n) 
		{
			double ret = 0;
			if (!(n & 1)) ret = n * .25;
			double lst = 0;
			REP(i, 0, n)
			{
				//1/nx
				//-1/(i + 1)x + 1
				double now = 1 / (1. / (i + 1) + 1. / n);
				if (!(i & 1)) ret += now;
				else if (i != n - 1) ret -= now;
				double h = (now - lst) / n;
				if (!(i & 1)) ret += (n - 2 * now) * h / 2;
				else ret += (n - 2 * lst) * h / 2;
				lst = now;
			}
			return ret;
		}
};

// Powered by Greed 2.0-RC
