/*
	Judge if all integer points lie on the same line.
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
typedef pair<int, int> PI;
vector<PI> pts;
PI operator -(const PI& a, const PI& b){
	return PI(a.first - b.first, a.second - b.second);
}
LL cross(const PI& a, const PI& b){
	return (LL)a.first * b.second - (LL)a.second * b.first;
}
class ConvexPolygonGame {
	public:
	string winner(vector <int> x, vector <int> y) {
		pts.clear();
		int n = x.size(); x.push_back(x[0]); y.push_back(y[0]);
		int l = *min_element(x.begin(), x.end()), r = *max_element(x.begin(), x.end());
		rep(xp, l, r){
			int yl, yr;
			rep(i, 0, n - 1){
				int x1 = x[i], x2 = x[i + 1];
				int y1 = y[i], y2 = y[i + 1];
				if (x1 == xp && x2 == xp){
					yl = min(y1, y2) + 1;
					yr = max(y1, y2) - 1;
					break;
				}
				if (x1 < x2){
					if (x1 == xp) yl = y1 + 1;
					if (x2 == xp) yl = y2 + 1;
					if (x1 < xp && xp < x2) yl = (int)ceil(y1 + 1.0 * (xp - x1) * (y2 - y1) / (x2 - x1));
				}
				if (x2 < x1){
					if (x1 == xp) yr = y1 - 1;
					if (x2 == xp) yr = y2 - 1;
					if (x2 < xp && xp < x1) yr = (int)floor(y1 + 1.0 * (xp - x1) * (y2 - y1) / (x2 - x1));
				}
			}
			rep(yp, yl, yr) pts.push_back(PI(xp, yp));
			if (pts.size() > 233333) return "Masha"; // Too many points, break
		}
		rep(i, 2, (int)pts.size() - 1) // judge if on the same line
			if (cross(pts[1] - pts[0], pts[i] - pts[0])) return "Masha";
		return "Petya";
	}
};

/*
	long time no Geometry
	miss her
*/
