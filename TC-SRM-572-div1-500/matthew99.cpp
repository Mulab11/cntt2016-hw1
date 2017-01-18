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

int n, m;

int g[maxn + 5][9];

int pw[10];

class EllysBulls 
{
	public:
		string getNumber(vector<string> guesses, vector<int> cnt) 
		{
			pw[0] = 1;
			REP(i, 0, 9) pw[i + 1] = pw[i] * 10;
			n = SZ(guesses);
			m = SZ(guesses[0]);
			REP(i, 0, n) REP(j, 0, m) g[i][j] = guesses[i][j] - '0';
			map<vector<int>, vector<int> > all;
			int mid = m >> 1;
			REP(i, 0, pw[mid])
			{
				static int val[5];
				REP(j, 0, mid) val[j] = i / pw[j] % 10;
				vector<int> res;
				REP(j, 0, n)
				{
					int tmp = 0;
					REP(k, 0, mid) if (val[k] == g[j][k]) ++tmp;
					res.pb(cnt[j] - tmp);
				}
				all[res].pb(i);
			}
			string ret;
			bool find = 0;
			REP(i, 0, pw[m - mid])
			{
				static int val[5];
				REP(j, 0, m - mid) val[j] = i / pw[j] % 10;
				vector<int> res;
				REP(j, 0, n)
				{
					int tmp = 0;
					REP(k, 0, m - mid) if (val[k] == g[j][k + mid]) ++tmp;
					res.pb(tmp);
				}
				if (all.count(res))
				{
					vector<int> &v = all[res];
					if (SZ(v) > 1 || find) return "Ambiguity";
					find = 1;
					int tmp = i * pw[mid] + v[0];
					REP(j, 0, m) ret += tmp / pw[j] % 10 + '0';
				}
			}
			if (!find) return "Liar";
			return ret;
		}
};

// Powered by Greed 2.0-RC
