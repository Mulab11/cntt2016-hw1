/*
	Arithmetics
	Knapsack dp
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
bool mark[1234567];
class MayTheBestPetWin {
	public:
	int calc(vector <int> A, vector <int> B) {
		memset(mark, 0, sizeof mark); mark[0] = 1;
		int n = A.size(), sA = 0, sB = 0, sAB = 0, ret = 1234567;
		rep(i, 0, n - 1) sA += A[i], sB += B[i]; sAB = sA + sB;
		rep(i, 0, n - 1) red(j, sAB, 0) if (j >= A[i] + B[i]) mark[j] |= mark[j - A[i] - B[i]];
		rep(i, 0, sAB) if (mark[i]) ret = min(ret, max(abs(i - sB), abs(sA - i)));
		return ret;
	}
};

/*
	Easy pp
	Easy life
*/
