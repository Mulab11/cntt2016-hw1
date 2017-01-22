/*
	Expected value
	Geometry
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
#define X first
#define Y second
using namespace std;
typedef long long LL;
typedef pair<int, int> PI;
PI operator -(const PI& a, const PI& b){
	return PI(a.X - b.X, a.Y - b.Y);
}
int cross(const PI& a, const PI& b){
	return a.X * b.Y - a.Y * b.X;
}
int dot(const PI& a, const PI& b){
	return a.X * b.X + a.Y * b.Y;
}
class Constellation {
	public:
	double expectation(vector <int> x, vector <int> y, vector <int> prob) {
		int n = x.size(); double ret = 0;
		vector<PI> pts(n);
		rep(i, 0, n - 1) pts[i] = PI(x[i], y[i]);
		rep(i, 0, n - 1) rep(j, 0, n - 1) if (i != j){ // i->j, calculate expected, signed area of triangle-OIJ
			int area2 = cross(pts[i], pts[j]); // area * 2
			double p = 1; // prob
			rep(k, 0, n - 1){
				if (k == i || k == j) p *= prob[k] * 0.001;
				else{
					int c = cross(pts[j] - pts[i], pts[k] - pts[i]);
					// ban if on the other side, or on the same line but outside the segment IJ
					if (c < 0 || (c == 0 && (dot(pts[j] - pts[i], pts[k] - pts[i]) < 0 || dot(pts[i] - pts[j], pts[k] - pts[j]) < 0)))
						p *= 1 - prob[k] * 0.001;
				}
			}
			ret += area2 * p / 2;
		}
		return ret;
	}
};

/*
	It is totally a circle-road!
*/
