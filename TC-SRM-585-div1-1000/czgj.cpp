/*
	Geometry
	Three pointers(?)
	Queue && prefix sum
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
#define X first
#define Y second
using namespace std;
const int MAXN = 234567;
typedef long long LL;
typedef pair<int, int> PI;
PI operator -(const PI& a, const PI& b){
	return PI(a.X - b.X, a.Y - b.Y);
}
LL cross(const PI& a, const PI& b){
	return (LL)a.X * b.Y - (LL)a.Y * b.X;
}
LL cross(const PI& a, const PI& b, const PI& O){
	return cross(a - O, b - O);
}
vector<PI> pts;
bool check(const PI &A, const PI &B){
	rep(i, 0, (int)pts.size() - 1) if (cross(pts[i], B, A) < 0) return 0;
	return 1;
}
LL q[MAXN], sum[MAXN];
class EnclosingTriangle {
	public:
	long long getNumber(int m, vector <int> x, vector <int> y) {
		LL ret = 0; int n = x.size(); pts.resize(n);
		rep(i, 0, n - 1) pts[i] = PI(x[i], y[i]);
		static vector<PI> A; A.clear();
		rep(i, 0, m - 1) A.push_back(PI(0, i)); // add points
		rep(i, 0, m - 1) A.push_back(PI(i, m));
		red(i, m, 1) A.push_back(PI(m, i));
		red(i, m, 1) A.push_back(PI(i, 0));
		m = 4 * m; 
		for (int i = 0, j = 0, k = 1, l = 0; i < m; ++i){
			while (k < m && !check(A[k], A[i])) ++k; // the last point
			while (j < m && check(A[i], A[j])){ // the second point
				int t = q[j]; while (t < m && check(A[j], A[t])) ++t; // find the upperbound
				++j; q[j] = t; sum[j] = sum[j - 1] + t; // prefixsum
			}
			while (l <= j && k >= q[l]) ++l; // let lowerbound > k
			l = max(l, i + 2); // note that q[x] --> pts[x - 1]
			ret += sum[j] - sum[l - 1] - (LL)k * (j - l + 1);
			if (j == k + 1) --ret; // duplicate points
		}
		return ret;
	}
};

/*
	sometimes naive.
*/
