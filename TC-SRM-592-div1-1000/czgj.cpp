/*
	DFT
	Force
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
typedef complex<double> cplx;
const int MAXN = 233;
const double pi = acos(-1);
cplx w[MAXN];
vector<cplx> DFT(const vector<cplx> &a){ // n ^ 2 DFT
	int n = a.size(); vector<cplx> ret(n);
	rep(i, 0, n - 1) rep(j, 0, n - 1) ret[i] += a[j] * w[i * j % n];
	return ret;
}
bool check(const vector<int> &a, const vector<int> &b){ // Check if a is the root of b
	int n = a.size(); vector<int> c(n);
	rep(i, 0, n - 1) if (a[i] < 0) return 0;
	rep(i, 0, n - 1) rep(j, 0, n - 1) c[(i + j) % n] += a[i] * a[j];
	return b == c;
}
class SplittingFoxes2 {
	public:
	vector <int> getPattern(vector <int> a) {
		int n = a.size(); vector<cplx> A(n), B(n); vector<int> b(n), ret;
		w[0] = 1; rep(i, 1, n - 1) w[i] = w[i - 1] * cplx(cos(2 * pi / n), sin(2 * pi / n));
		rep(i, 0, n - 1) A[i] = a[i]; A = DFT(A);
		rep(i, 0, n - 1) A[i] = sqrt(A[i]);
		rep(i, 0, n - 1) w[i] = conj(w[i]); // Change DFT to IDFT
		int m = n / 2 + 1;
		rep(i, 0, (1 << m) - 1){
			rep(j, 0, m - 1) B[j] = A[j] * (i >> j & 1 ? 1.0 : -1.0);
			rep(j, 1, m - 1) B[n - j] = B[j]; B = DFT(B);
			rep(j, 0, n - 1) b[j] = (int)round(B[j].real() / n);
			if (check(b, a) && (ret.empty() || ret > b)) ret = b;
		}
		if (ret.empty()) ret.push_back(-1);
		return ret;
	}
};

/*
	Never forget that std::vector has comparisions!
*/
