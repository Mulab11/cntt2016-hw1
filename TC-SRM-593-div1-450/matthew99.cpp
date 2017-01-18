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
const int maxabs = 1000010;

class MayTheBestPetWin 
{
	public:
		int calc(vector<int> A, vector<int> B) 
		{
			int sumA = accumulate(ALL(A), 0);
			int sumB = accumulate(ALL(B), 0);
			static bitset<maxabs + 5> dp;
			dp = bitset<maxabs + 5>();
			dp[0] = 1;
			REP(i, 0, SZ(A))
				dp |= dp << (A[i] + B[i]);
			int ret = oo;
			REP(i, 0, sumA + sumB + 1) if (dp[i]) chkmin(ret, max(i - sumA, sumB - i));
			return ret;
		}
};

// Powered by Greed 2.0-RC
