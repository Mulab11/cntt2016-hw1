#include <bits/stdc++.h>
#define rep(i, l, r) for(int _r = r, i = l; i <= _r; ++i)
#define red(i, r, l) for(int _l = l, i = r; i >= _l; --i)
#define debug(x) cerr << #x << " = " << x << endl
#define MEM(x, y) memset(x, y, sizeof(x))
#define X first
#define Y second

using namespace std;
typedef long long LL;
typedef pair<int, int> PI;
typedef bitset<32> bits;
const LL MOD = 1e9 + 7;
const double eps = 1e-8;
const int MAXN = 20;
bits expr[MAXN], f;
int lb[13], ub[13];
double a[13], A[13];
double ret;
int n;
void dfs(int d, double sum, int k, bits B){
	if (d >= n){
		if (!k) return;
		rep(i, 0, n - 1) A[i] = a[i];
		rep(i, 0, n - 1) if (f[i])
			rep(j, 0, n - 1) if (!f[j] && expr[i][j])
				A[i] += A[j], sum -= A[j];
		rep(i, 0, n - 1) if (f[i]) A[i] += sum / k;
		rep(i, 0, n - 1) if (A[i] + eps < lb[i] || A[i] - eps > ub[i]) return;
		double val = 0;
		rep(i, 0, n - 1) rep(j, i + 1, n - 1) if (expr[i][j]) val += A[i]*A[j];
		ret = max(ret, val);
		return;
	}
	if (B[d]) f[d] = 1, dfs(d + 1, sum, k + 1, B & expr[d]), f[d] = 0;
	a[d] = lb[d]; dfs(d + 1, sum - a[d], k, B);
	a[d] = ub[d]; dfs(d + 1, sum - a[d], k, B);
	a[d] = 0;
}
class BoundedOptimization{
	public:
	double maxValue(vector <string> _expr, vector <int> _lb, vector <int> _ub, int sum){
		n = _lb.size();
		string s; rep(i, 0, (int)_expr.size() - 1) s += _expr[i];
		for (int i = 0; i < (int)s.size(); i += 3){
			int p1 = s[i] - 'a', p2 = s[i + 1] - 'a';
			expr[p1][p2] = expr[p2][p1] = 1;
		}
		int mxsum = 0;
		rep(i, 0, n - 1) lb[i] = _lb[i], mxsum += ub[i] = _ub[i];
		sum = min(sum, mxsum);
		dfs(0, sum, 0, (1 << n) - 1);
		return ret;
	}
};

