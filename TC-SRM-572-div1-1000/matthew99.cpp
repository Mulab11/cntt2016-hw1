#line 5 "NextAndPrev.cpp"
#include <bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for (int i = (a), _end_ = (b); i < _end_; ++i)
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

map<int, int> goal;

class NextAndPrev
{
	public:
		int getMinimum(int nxt, int pre, string a, string b)
		{
			if (a == b) return 0;
			set<int> tmp;
			goal.clear();
			REP(i, 0, SZ(a))
			{
				int u = a[i] - 'a', v = b[i] - 'a';
				tmp.insert(v);
				if (goal.count(u)) { if (goal[u] != v) return -1; }
				goal[u] = v;
			}
			if (SZ(tmp) == 26) return -1;
			vector<pair<int, int> > all;
			for (auto x : goal) all.pb(mp(x.x - 52, x.y));
			int n = SZ(all);
			int ret = oo;
			REP(i, 0, n << 2 | 1)
			{
				bool flag = 1;
				REP(j, 0, n - 1) if (all[j].y > all[j + 1].y) { flag = 0; break; }
				if (flag)
				{
					int tmp = 0;
					for (int j = 0; j < n; )
					{
						int k = j;
						while (k < n && all[k].y == all[j].y) ++k;
						int l = min(all[j].y, all[j].x), r = max(all[j].y, all[k - 1].x);
						tmp += (all[j].y - l) * nxt + (r - all[j].y) * pre;
						j = k;
					}
					chkmin(ret, tmp);
				}
				all[0].x += 26;
				sort(ALL(all));
			}
			return ret == oo ? -1 : ret;
		}
		

};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
