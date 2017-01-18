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

class UndoHistory 
{
	public:
		int minPresses(vector<string> a) 
		{
			int n = SZ(a);
			int ret = 0;
			REP(i, 0, n)
			{
				int tmp = 0;
				int need = 0;
				if (i)
				{
					REP(j, 0, i) REP(k, 0, min(SZ(a[i]), SZ(a[j])))
						if (a[i][k] != a[j][k]) break;
						else chkmax(tmp, k + 1);
					need += 2;
				}
				need += SZ(a[i]) - tmp;
				if (i)
				{
					if (SZ(a[i]) >= SZ(a[i - 1]) && a[i].substr(0, SZ(a[i - 1])) == a[i - 1]) chkmin(need, SZ(a[i]) - SZ(a[i - 1]));
				}
				++need;
				ret += need;
			}
			return ret;
		}
};

// Powered by Greed 2.0-RC
