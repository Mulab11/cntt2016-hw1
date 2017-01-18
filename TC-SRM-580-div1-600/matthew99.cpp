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

const int maxn = 2550;

int n;

pair<int, int> a[maxn + 5];

bool has[maxn + 5];

class ShoutterDiv1 
{
	public:
		int count(vector<string> s1000, vector<string> s100, vector<string> s10, vector<string> s1, vector<string> t1000, vector<string> t100, vector<string> t10, vector<string> t1) 
		{
			string S1000 = accumulate(ALL(s1000), string());
			string S100 = accumulate(ALL(s100), string());
			string S10 = accumulate(ALL(s10), string());
			string S1 = accumulate(ALL(s1), string());
			string T1000 = accumulate(ALL(t1000), string());
			string T100 = accumulate(ALL(t100), string());
			string T10 = accumulate(ALL(t10), string());
			string T1 = accumulate(ALL(t1), string());
			n = SZ(S1000);
			REP(i, 0, n) a[i] = mp((S1000[i] - '0') * 1000 + (S100[i] - '0') * 100 + (S10[i] - '0') * 10 + S1[i] - '0', (T1000[i] - '0') * 1000 + (T100[i] - '0') * 100 + (T10[i] - '0') * 10 + T1[i] - '0');
			sort(a, a + n);
			int Maxx = -oo, Miny = oo;
			REP(i, 0, n) chkmax(Maxx, a[i].x), chkmin(Miny, a[i].y);
			vector<int> all;
			REP(i, 0, n)
			{
				has[i] = 0;
				REP(j, 0, n) if (a[j].x <= a[i].x && a[i].y <= a[j].y && (i < j || a[i] != a[j])) 
				{
					has[i] = 1;
					break;
				}
				if (!has[i]) all.pb(i);
			}
			int N = SZ(all);
			static int le[maxn + 5], ri[maxn + 5];
			int j = 0;
			REP(i, 0, N)
			{
				if (a[all[i]].x <= Miny) { le[i] = 0; continue; }
				while (j < i && a[all[j]].y < a[all[i]].x) ++j;
				if (j == i) return -1;
				le[i] = le[j] + 1;
			}
			j = N - 1;
			for (int i = N - 1; i >= 0; --i)
			{
				if (a[all[i]].y >= Maxx) { ri[i] = 0; continue; }
				while (j > i && a[all[j]].x > a[all[i]].y) --j;
				if (j == i) return -1;
				ri[i] = ri[j] + 1;
			}
			int ret = 0;
			REP(i, 0, n)
			{
				int tmp = 0;
				if (a[i].x > Miny) REP(k, 0, N) if (a[all[k]].y >= a[i].x) { tmp += le[k] + 1; break; }
				if (a[i].y < Maxx) for (int k = N - 1; k >= 0; --k) if (a[all[k]].x <= a[i].y) { tmp += ri[k] + 1; break; }
				REP(k, 0, N) if (a[all[k]].x <= a[i].x && a[i].y <= a[all[k]].y) chkmin(tmp, le[k] + ri[k] + 1);
				ret += tmp;
			}
			return ret;
		}
};

// Powered by Greed 2.0-RC
