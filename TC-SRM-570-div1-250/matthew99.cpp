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

const int walk[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

class RobotHerb 
{
	public:
		long long getdist(int T, vector<int> a) 
		{
			int sum = accumulate(ALL(a), 0) & 3;
			static int cnt[4];
			memset(cnt, 0, sizeof cnt);
			REP(j, 0, 4) cnt[(sum * j) & 3] += (T - j + 3) >> 2;
			int cur = 0;
			LL x = 0, y = 0;
			for (auto u : a)
			{
				REP(j, 0, 4)
				{
					x += (LL)walk[(cur + j) & 3][0] * u * cnt[j];
					y += (LL)walk[(cur + j) & 3][1] * u * cnt[j];
				}
				(cur += u) &= 3;
			}
			return abs(x) + abs(y);
		}
};

// Powered by Greed 2.0-RC
