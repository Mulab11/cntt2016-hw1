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

#define ctz __builtin_ctzll
#define bcnt __builtin_popcountll

template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

typedef long long LL;

const int oo = 0x3f3f3f3f;

const int maxn = 600;
const int maxm = 36;

const int lim = 20;

int n;
string b;

vector<LL> all;

class MapGuessing 
{
	public:
		long long countPatterns(string a, vector<string> code) 
		{
			n = SZ(a);
			b = accumulate(ALL(code), string(""));
			all.clear();
			REP(i, 0, n)
			{
				int cur = i;
				LL tot = 0;
				string tmp = string(n, '?');
				LL Max = 0;
				REP(j, 0, SZ(b))
				{
					if (b[j] == '<') --cur;
					else if (b[j] == '>') ++cur;
					else
					{
						tmp[cur] = b[j];
						tot |= 1LL << cur;
						bool failed = 0;
						REP(k, 0, n) if (tmp[k] != '?' && tmp[k] != a[k]) { failed = 1; break; }
						if (!failed) Max = tot;
					}
					if (cur < 0 || cur >= n) 
					{
						Max = -1;
						break;
					}
				}
				if (~Max) all.pb(Max);
			}
			if (SZ(all) <= lim)
			{
				int N = SZ(all);
				static LL dp[2][(1 << lim) + 5];
				memset(dp, 0, sizeof dp);
				dp[0][0] = 1;
				REP(i, 0, n)
				{
					int cur = i & 1;
					memcpy(dp[!cur], dp[cur], sizeof dp[!cur]);
					int S = 0;
					REP(j, 0, N) if (!(all[j] >> i & 1)) S |= 1 << j;
					REP(j, 0, 1 << N) if (dp[cur][j]) dp[!cur][j | S] += dp[cur][j];
				}
				LL ret = 0;
				REP(i, 0, (1 << N) - 1) ret += dp[n & 1][i];
				return ret;
			}
			set<LL> S;
			REP(i, 0, SZ(all))
			{
				LL x = all[i];
				REP(j, 0, 1 << bcnt(x))
				{
					LL tmp = 0;
					int cnt = 0;
					REP(l, 0, n) 
						if (x >> l & 1) tmp |= LL(j >> (cnt++) & 1) << l;
						else tmp |= LL(a[l] - '0') << l;
					S.insert(tmp);
				}
			}
			return SZ(S);
		}
};

// Powered by Greed 2.0-RC
