#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define bin(x) (1<<(x))
#define LX_JUDGE

using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

template<typename T> inline void upmax(T &x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T &x, T y) { x > y ? x = y : 0; }

class AstronomicalRecords {
private :
	int n, m;
	int dp[105][105];
	inline int calc(vector<LL> A, vector<LL> B, int p, int q) {
		rep (i, 0, n-1)  A[i] *= q;
		rep (i, 0, m-1)  B[i] *= p;
		rep (i, 0, n-1) rep (j, 0, m-1) {
			if (A[i] == B[j]) {
				dp[i + 1][j + 1] = dp[i][j] + 1;
			} else {
				dp[i + 1][j + 1] = max(dp[i + 1][j], dp[i][j + 1]);
			}
		}
		return n + m - dp[n][m];
	}
public :
	int minimalPlanets(vector<int> A, vector<int> B) {
		n = A.size(), m = B.size();
		vector<LL> nA(n);
		vector<LL> nB(m);
		rep (i, 0, n-1) nA[i] = A[i];
		rep (i, 0, m-1) nB[i] = B[i];
		int res = n + m;
		rep (i, 0, n-1) rep (j, 0, m-1) {
			upmin(res, calc(nA, nB, A[i], B[j]));
		}
		return res;
	}
};
