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

const int maxn = 80000;

class TheSquareRootDilemma 
{
	public:
		int countPairs(int N, int M) 
		{
			static int sum[maxn + 5];
			memset(sum, 0, sizeof sum);
			for (int i = 1; i * i <= M; ++i)
				++sum[i * i];
			REP(i, 1, M + 1) sum[i] += sum[i - 1];
			int ret = 0;
			for (int i = 1; i <= N; ++i)
			{
				int Max = 1;
				for (int j = 1; j * j <= i; ++j)
					if (!(i % (j * j))) Max = j * j;
				ret += sum[M / (i / Max)];
			}
			return ret;
		}
};

// Powered by Greed 2.0-RC
