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

int fa[26];

inline int get(int x) { return fa[x] == x ? x : fa[x] = get(fa[x]); }

class GooseTattarrattatDiv1 
{
	public:
		int getmin(string s) 
		{
			int cnt[26] = {0};
			int n = SZ(s);
			REP(i, 0, n) ++cnt[s[i] - 'a'];
			REP(i, 0, 26) fa[i] = i;
			for (int i = 0, j = n - 1; i < j; ++i, --j)
				fa[get(s[i] - 'a')] = get(s[j] - 'a');
			int ret = n;
			REP(i, 0, 26) if (fa[i] == i)
			{
				int Max = 0;
				REP(j, 0, 26) if (get(j) == i) chkmax(Max, cnt[j]);
				ret -= Max;
			}
			return ret;
		}
};

// Powered by Greed 2.0-RC
