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

int cnt[maxn + 5][27];

class StringGame 
{
	public:
		vector<int> getWinningStrings(vector<string> S) 
		{
			int n = SZ(S);
			memset(cnt, 0, sizeof cnt);
			REP(i, 0, n) for (auto u : S[i]) ++cnt[i][u - 'a'];
			vector<int> ret;
			REP(i, 0, n)
			{
				vector<int> res;
				REP(j, 0, n) if (j != i) res.pb(j);
				REP(t, 0, 26)
				{
					REP(j, 0, 26)
					{
						bool failed = 0;
						for (auto u : res) if (cnt[u][j] > cnt[i][j]) { failed = 1; break; }
						if (!failed)
						{
							vector<int> nxt;
							for (auto u : res) if (cnt[u][j] == cnt[i][j]) nxt.pb(u);
							res = nxt;
						}
					}
				}
				if (res.empty()) ret.pb(i);
			}
			return ret;
		}
};

// Powered by Greed 2.0-RC
