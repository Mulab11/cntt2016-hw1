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

const int maxn = 300;

int n;
int a[maxn + 5];
int m;
pair<int, int> b[maxn + 5];

class Ear 
{
	public:
		long long getCount(vector<string> redX, vector<string> blueX, vector<string> blueY) 
		{
			istringstream inrX(accumulate(ALL(redX), string()));
			n = -1;
			while (inrX >> a[++n]);
			istringstream inbX(accumulate(ALL(blueX), string()));
			m = -1;
			while (inbX >> b[++m].x);
			istringstream inbY(accumulate(ALL(blueY), string()));
			REP(i, 0, m) inbY >> b[i].y;
			sort(a, a + n);
			LL ret = 0;
			REP(i, 0, m) REP(j, 0, m) if (b[j].y < b[i].y)
			{
				int le = 0;
				int tot = 0;
				for (int k = 0; k < n && a[k] < b[j].x; ++k)
				{
					le += tot;
					if (a[k] < b[i].x && (b[j].x - a[k]) * b[i].y > b[j].y * (b[i].x - a[k])) ++tot;
				}
				int ri = 0;
				tot = 0;
				for (int k = n - 1; k >= 0 && a[k] > b[j].x; --k)
				{
					ri += tot;
					if (a[k] > b[i].x && (b[j].x - a[k]) * b[i].y < b[j].y * (b[i].x - a[k])) ++tot;
				}
				ret += (LL)le * ri;
			}
			return ret;
		}
};

// Powered by Greed 2.0-RC
