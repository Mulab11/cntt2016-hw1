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

class TeamContest 
{
	public:
		int worstRank(vector<int> a) 
		{
			int w = min({a[0], a[1], a[2]}) + max({a[0], a[1], a[2]});
			rotate(a.begin(), a.begin() + 3, a.end());
			a.pop_back(), a.pop_back(), a.pop_back();
			int n = SZ(a);
			sort(ALL(a));
			int ret = 1;
			for (int i = n - 1, j = 0; i > j + 1; --i, j += 2)
			{
				while (i > j + 1 && a[i] + a[j] <= w) ++j;
				if (i > j + 1) ++ret;
			}
			return ret;
		}
};

// Powered by Greed 2.0-RC
