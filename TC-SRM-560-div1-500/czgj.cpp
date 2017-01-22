/*
	Brute force, implementation.
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
const int MAXN = 300;
bool a[MAXN][MAXN], b[MAXN][MAXN];
class DrawingPointsDivOne {
	public:
	int maxSteps(vector <int> x, vector <int> y) {
		int n = x.size();
		memset(a, 0, sizeof a);
		rep(i, 0, n - 1) a[x[i] + 71][y[i] + 71] = 1;
		rep(ret, 0, 150){
			int N = 142 + ret;
			red(i, N, 1) red(j, N, 1) a[i][j] = a[i][j] || a[i - 1][j] || a[i][j - 1] || a[i - 1][j - 1]; 
			memcpy(b, a, sizeof b);
			red(t, ret + 1, 1) rep(i, 1, 142 + t) rep(j, 1, 142 + t) b[i][j] = b[i][j] && b[i + 1][j] && b[i][j + 1] && b[i + 1][j + 1];
			int cnt = 0; rep(i, 1, N) rep(j, 1, N) cnt += b[i][j];
			if (cnt != n) return ret;
		}
		return -1;
	}
};

/*
	yiorutvnxd,mbguerkytlwoejfioytoweifj,sdhgsiu
		- Yakumo Yukari
*/
