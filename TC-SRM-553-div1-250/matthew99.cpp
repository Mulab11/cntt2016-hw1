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

class Suminator 
{
	public:
		int findMissing(vector<int> a, int val) 
		{
			static LL _stk[maxn + 5];
			int tot = 0;
			REP(i, 0, SZ(a))
			{
				if (a[i] <= 0)
				{
					if (!tot) _stk[tot++] = 0;
					else if (tot > 1) _stk[tot - 2] += _stk[tot - 1], --tot;
				}
				else _stk[tot++] = a[i];
			}
			if ((!tot && !val) || (tot && _stk[tot - 1] == val)) return 0;
			static pair<int, LL> stk[maxn + 5];
			tot = 0;
			REP(i, 0, SZ(a))
			{
				if (a[i] == 0)
				{
					if (!tot) stk[tot++] = mp(0, 0LL);
					else if (tot > 1) stk[tot - 2].x += stk[tot - 1].x, stk[tot - 2].y += stk[tot - 1].y, --tot;
				}
				else if (!~a[i]) stk[tot++] = mp(1, 0LL);
				else stk[tot++] = mp(0, (LL)a[i]);
			}
			if (!tot)
			{
				if (!val) return 1;
				return -1;
			}
			LL dif = val - stk[tot - 1].y;
			if (dif < 0) return -1;
			if (!dif)
			{
				if (stk[tot - 1].x) return -1;
				return 1;
			}
			if (!stk[tot - 1].x) return -1;
			if (dif % stk[tot - 1].x) return -1;
			return dif / stk[tot - 1].x;
		}
};

// Powered by Greed 2.0-RC
