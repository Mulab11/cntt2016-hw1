/*
	(Linear) sieve,
	Game theory.
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
const int MAXN = 1010101;
int a[MAXN], sg[MAXN], cnt[233];
class TheDivisionGame {
	public:
	long long countWinningIntervals(int L, int R) {
		int n = R - L + 1, sum = 0; LL ret = (LL)n * (n + 1) / 2;
		memset(sg, 0, sizeof sg); memset(cnt, 0, sizeof cnt); cnt[0] = 1;
		rep(i, L, R) a[i - L] = i;
		rep(i, 2, 66666) for (int j = ((L - 1) / i + 1) * i; j <= R; j += i)
			while (a[j - L] % i == 0) ++sg[j - L], a[j - L] /= i;
		rep(i, 0, n - 1) if (a[i] > 1) ++sg[i];
		rep(i, 0, n - 1) ret -= cnt[sum ^= sg[i]]++;
		return ret;
	}
};

/*
	Last Remote - Type gamma
*/
