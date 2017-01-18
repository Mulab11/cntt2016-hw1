#line 5 "WolfDelaymasterHard.cpp"
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

const int Mod = 1e9 + 7;

const int maxn = 2000000;

int n;
char s[maxn + 5];

class WolfDelaymasterHard
{
	public:
		int countWords(int N, int wlen, int w0, int wmul, int wadd, int olen, int o0, int omul, int oadd)
		{
			n = N;
			memset(s, '?', sizeof s);
			LL x = w0;
			REP(i, 0, wlen) s[x] = 'w', x = (x * wmul + wadd) % n;
			x = o0;
			REP(i, 0, olen) s[x] = 'o', x = (x * omul + oadd) % n;
			static int prew[maxn + 5];
			int lstw = -1, lsto = -1;
			REP(i, 0, n + 1)
			{
				prew[i] = lstw;
				if (i < n)
				{
					if (s[i] == 'w') lstw = i;
				}
			}
			static int nxtw[maxn + 5], nxto[maxn + 5];
			lstw = lsto = n;
			for (int i = n; i >= 0; --i)
			{
				if (i < n)
				{
					if (s[i] == 'w') lstw = i;
					else if (s[i] == 'o') lsto = i;
				}
				nxtw[i] = lstw, nxto[i] = lsto;
			}
			static int sum[maxn + 5], dp[maxn + 5];
			memset(sum, 0, sizeof sum), memset(dp, 0, sizeof dp);
			sum[0] = 1, sum[2] = -1;
			int now = 0;
			REP(i, 0, n + 1) if ((i & 1) == 0)
			{
				(now += sum[i]) %= Mod;
				dp[i] = now;
				int lim = min(n, i + ((nxto[i] - i) << 1));
				int cur = i + 2;
				while (cur <= lim)
				{
					int l = cur, r = min(lim, nxtw[cur]);
					chkmax(l, i + ((prew[cur] + 1 - i) << 1));
					if (l & 1) ++l;
					if (r & 1) --r;
					if (l <= r) 
					{
						(sum[l] += dp[i]) %= Mod, (sum[r + 2] -= dp[i]) %= Mod;
					}
					cur = i + ((r + 1 - i) << 1);
				}
			}
			int ret = dp[n];
			(ret += Mod) %= Mod;
			return ret;
		}
		

};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
