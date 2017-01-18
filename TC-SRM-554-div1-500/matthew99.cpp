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

class TheBrickTowerMediumDivOne 
{
	public:
		vector<int> find(vector<int> a) 
		{
			int val = accumulate(ALL(a), 0) - *min_element(ALL(a));
			vector<int> pos;
			int n = SZ(a);
			REP(i, 0, n) pos.pb(i);
			sort(ALL(pos), [&](int x, int y) { return a[x] < a[y]; });
			static bool vis[maxn + 5];
			memset(vis, 0, sizeof vis);
			vector<int> ret;
			int now = 0;
			REP(i, 0, n)
			{
				REP(j, 0, n) if (!vis[j])
				{
					int tmp = now;
					if (i) tmp += max(a[ret.back()], a[j]);
					int sum = tmp;
					int lst = j;
					bool ok = 0;
					REP(k, 0, n) if (!vis[pos[k]] && pos[k] != j) sum += max(a[lst], a[pos[k]]), lst = pos[k];
					if (sum == val) ok = 1;
					if (!ok)
					{
						sum = tmp, lst = j;
						for (int k = n - 1; k >= 0; --k) if (!vis[pos[k]] && pos[k] != j) sum += max(a[lst], a[pos[k]]), lst = pos[k];
						if (sum == val) ok = 1;
					}
					if (ok)
					{
						now = tmp;
						vis[j] = 1;
						ret.pb(j);
						break;
					}
				}
			}
			return ret;
		}
};

// Powered by Greed 2.0-RC
