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

class XorCards 
{
	public:
		long long numberOfWays(vector<long long> a, long long limit) 
		{
			const int max0 = 50;
			static LL base[max0 + 5];
			memset(base, -1, sizeof base);
			for (auto u : a)
			{
				for (int i = max0 - 1; i >= 0; --i)
					if (u >> i & 1)
					{
						if (!~base[i])
						{
							base[i] = u;
							break;
						}
						else u ^= base[i];
					}
			}
			LL ret = 0;
			LL now = 0;
			int cnt = SZ(a);
			for (int i = max0 - 1; i >= 0; --i)
			{
				if (~base[i])
				{
					--cnt;
					LL nxt = -1;
					if ((now >> i) < (limit >> i)) ret += 1LL << cnt;
					else if ((now >> i) == (limit >> i)) nxt = now;
					now ^= base[i];
					if ((now >> i) < (limit >> i)) ret += 1LL << cnt;
					else if ((now >> i) == (limit >> i)) nxt = now;
					if (~nxt) now = nxt;
					else break;
				}
				if (!i && now <= limit) ret += 1LL << cnt;
			}
			return ret;
		}
};

// Powered by Greed 2.0-RC
