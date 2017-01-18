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

class ColorfulChocolates 
{
	public:
		int maximumSpread(string a, int K) 
		{
			int n = SZ(a);
			int ret = 1;
			REP(i, 0, 26)
			{
				vector<int> p;
				REP(j, 0, n) if (a[j] == 'A' + i) p.pb(j);
				REP(j, 0, SZ(p))
				{
					REP(k, 0, n)
					{
						int tmp = 0;
						REP(l, 0, min(SZ(p) - j, n - k))
						{
							tmp += abs(k + l - p[j + l]);
							if (tmp > K) break;
							chkmax(ret, l + 1);
						}
					}
				}
			}
			return ret;
		}
};

// Powered by Greed 2.0-RC
