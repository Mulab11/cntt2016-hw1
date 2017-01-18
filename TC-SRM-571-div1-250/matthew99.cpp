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

int n;

vector<int> ans;

void dfs(int x)
{
	if (SZ(ans) >= 50) return;
	if (x > n) return;
	if (x) ans.pb(x);
	REP(i, 0, 10) 
	{
		if (!x && !i) continue;
		dfs(x * 10 + i);
	}
}

class FoxAndMp3 
{
	public:
		vector<string> playList(int _n) 
		{
			n = _n;
			ans.clear();
			dfs(0);
			vector<string> ret;
			REP(i, 0, SZ(ans))
			{
				ostringstream out;
				out << ans[i] << ".mp3";
				ret.pb(out.str());
			}
			return ret;
		}
};

// Powered by Greed 2.0-RC
