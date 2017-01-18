#line 5 "HolyNumbers.cpp"
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

const int max0 = 1000000;

vector<int> pr;
bool vis[max0 + 5];

inline LL work(LL bound, int st)
{
	if (st == SZ(pr)) return 1;
	LL ret = 0;
	ret = 0;
	if ((LL)pr[st] * pr[st] > bound)
	{
		ret += upper_bound(pr.begin() + st, pr.end(), bound) - pr.begin() - st + 1;
		return ret;
	}
	ret = 0;
	ret += work(bound, st + 1);
	for (int i = 0; bound; ++i, bound /= pr[st]) if (i & 1) ret += work(bound, st + 1);
	return ret;
}

class HolyNumbers
{
	public:
		long long count(long long upTo, int maximalPrime)
		{
			memset(vis, 0, sizeof vis);
			pr.clear();
			for (int i = 2; i <= maximalPrime; ++i)
			{
				if (!vis[i]) pr.pb(i);
				for (int j = i << 1; j <= maximalPrime; j += i) vis[j] = 1;
			}
			return work(upTo, 0);
		}


};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
