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

const int max0 = 60;

int n;

bool vis[max0 + 5];

class BitwiseAnd 
{
	public:
		vector<long long> lexSmallest(vector<long long> a, int m) 
		{
			memset(vis, 0, sizeof vis);
			n = SZ(a);
			REP(i, 0, n) REP(j, 0, i) if (!(a[i] & a[j])) return {};
			REP(i, 0, n) REP(j, 0, i) REP(k, 0, j) if (a[i] & a[j] & a[k]) return {};
			REP(i, 0, n) REP(j, 0, i) REP(k, 0, max0) if ((a[i] & a[j]) >> k & 1) vis[k] = 1;
			vector<LL> ret(a);
			REP(i, n, m)
			{
				LL x = 0;
				REP(j, 0, n)
				{
					bool find = 0;
					REP(k, 0, max0) if (!vis[k] && (a[j] >> k & 1))
					{
						find = 1;
						vis[k] = 1;
						x |= 1LL << k;
						break;
					}
					if (!find) return {};
				}
				ret.pb(x);
			}
			REP(i, 0, n) REP(j, 0, max0) if (a[i] >> j & 1) vis[j] = 1;
			REP(i, n, m)
			{
				REP(j, i + 1, m)
				{
					bool find = 0;
					REP(k, 0, max0) if (!vis[k])
					{
						find = 1;
						vis[k] = 1;
						ret[i] |= 1LL << k;
						ret[j] |= 1LL << k;
						break;
					}
					if (!find) return {};
				}
			}
			sort(ALL(ret));
			return ret;
		}
};

// Powered by Greed 2.0-RC
