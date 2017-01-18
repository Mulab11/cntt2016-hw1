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

const int maxn = 50;

int n;

class LittleElephantAndString 
{
	public:
		int getNumber(string _a, string _b) 
		{
			string a = _a, b = _b;
			sort(ALL(_a)), sort(ALL(_b));
			if (_a != _b) return -1;
			n = SZ(a);
			int j = n - 1;
			int ret = n;
			for (int i = n - 1; i >= 0; --i, --j)
			{
				while (j >= 0 && a[j] != b[i]) --j;
				if (j < 0) break;
				--ret;
			}
			return ret;
		}
};

// Powered by Greed 2.0-RC
