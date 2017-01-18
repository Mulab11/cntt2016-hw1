#line 5 "FlippingBitsDiv1.cpp"
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
#define ctz __bultin_ctz
#define bcnt __builtin_popcount

template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

typedef long long LL;

const int oo = 0x3f3f3f3f;

const int maxn = 300, max0 = 17;

int n, m;

bool a[maxn + 5];

class FlippingBitsDiv1
{
	public:
		int getmin(vector <string> _S, int M)
		{
			m = M;
			string S;
			for (auto u : _S) S += u; 
			n = SZ(S);
			REP(i, 0, n) a[i] = S[i] == '1';
			int ret = oo;
			if ((m << 1) >= n)
			{
				int cnt[2] = {0, 1};
				REP(i, M, n) ++cnt[a[i] == a[i - M]];
				REP(i, 0, 2) chkmin(ret, cnt[i]);
			}
			else if (m * max0 >= n)
			{
				int tmp = (n + m - 1) / m;
				REP(i, 0, 1 << tmp)
				{
					int tot = 0;
					REP(j, 0, tmp - 1) tot += (i >> j & 1) ^ (i >> (j + 1) & 1); 
					REP(j, 0, m)
					{
						int cnt[2] = {0};
						int cur = 0;
						for (int k = j; k < n; k += m)
						{
							++cnt[a[k] ^ (i >> cur & 1)];
							++cur;
						}
						tot += min(cnt[0], cnt[1]);
					}
					chkmin(ret, tot);
				}
			}
			else
			{
				REP(i, 0, 1 << m)
				{
					static int dp[2];
					memset(dp, oo, sizeof dp);
					dp[0] = bcnt(i);
					for (int j = m; j < n; j += m)
					{
						int cnt[2] = {0};
						REP(k, j, min(n, j + m)) ++cnt[a[k] == (a[k - j] ^ (i >> (k - j) & 1))];
						static int nxt[2];
						memset(nxt, oo, sizeof nxt);
						REP(a, 0, 2) if (dp[a] < oo) REP(b, 0, 2) chkmin(nxt[b], dp[a] + (a != b) + cnt[b]);
						memcpy(dp, nxt, sizeof dp);
					}
					REP(j, 0, 2) chkmin(ret, dp[j]);
				}
			}
			return ret;
		}


};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
