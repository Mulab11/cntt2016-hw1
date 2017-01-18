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

int cnt[maxn + 5];

class TomekPhone 
{
	public:
		int minKeystrokes(vector<int> a, vector<int> b) 
		{
			sort(ALL(a), greater<int>());
			memset(cnt, 0, sizeof cnt);
			for (auto u : b) REP(i, 1, u + 1) ++cnt[i];
			int ret = 0;
			for (auto u : a)
			{
				bool find = 0;
				REP(i, 1, maxn + 1) if (cnt[i]) { ret += u * i, --cnt[i], find = 1; break; }
				if (!find) return -1;
			}
			return ret;
		}
};

// Powered by Greed 2.0-RC
