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

class EllysRoomAssignmentsDiv1 
{
	public:
		double getAverage(vector<string> ratings) 
		{
			vector<int> a;
			istringstream in(accumulate(ALL(ratings), string()));
			int x;
			while (in >> x) a.pb(x);
			int tmp = a[0];
			sort(ALL(a), greater<int>());
			int n = SZ(a);
			int num = (n + 19) / 20;
			double u = 0;
			int tot = n / num;
			bool find = 0;
			REP(i, 0, tot)
			{
				bool failed = 0;
				REP(j, 0, num) if (a[i * num + j] == tmp) { failed = 1; break; }
				if (!failed) REP(j, 0, num) u += a[i * num + j];
				else find = 1;
			}
			u /= num;
			u += tmp;
			if (!find) return u / (tot + 1);
			double v = 0;
			if (n % num)
			{
				int cnt = 0;
				REP(i, tot * num, n) v += a[i], ++cnt;
				v /= cnt;
				v += u;
			}
			u /= tot;
			v /= tot + 1;
			double ret = (v * (n % num) + u * (num - n % num)) / num;
			return ret;
		}
};

// Powered by Greed 2.0-RC
