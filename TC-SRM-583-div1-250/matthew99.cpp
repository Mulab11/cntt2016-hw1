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

int n;
int a[maxn + 5];

int dis[maxn + 5];

void dfs(int x)
{
	REP(i, 0, n) if (abs(i - x) <= a[x] || n - abs(i - x) <= a[x]) if (chkmin(dis[i], dis[x] + 1)) dfs(i);
}

class TravelOnMars 
{
	public:
		int minTimes(vector<int> range, int startCity, int endCity) 
		{
			n = SZ(range);
			REP(i, 0, n) a[i] = range[i];
			memset(dis, oo, sizeof dis);
			dis[startCity] = 0;
			dfs(startCity);
			return dis[endCity];
		}
};

// Powered by Greed 2.0-RC
