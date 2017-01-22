/*
	Conclusion
	Brute force
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
const int MX = 2500 * 2500 + 233;
const int NN = 20000;
int Sqrt[MX], x[NN], y[NN], l[NN];
int vn = 0;
class FindPolygons {
	public:
	double minimumPolygon(int L) {
		if (L % 2 == 1 || L == 2) return -1; // No solution when L is odd.
		// Judge if there is a valid triangle.
		rep(i, 1, 2500) Sqrt[i * i] = i;
		vn = 0;
		rep(i, 0, L) rep(j, 0, L){ // Pre-process grid points P that |OP| is an integer
			int t = i * i + j * j;
			if (t > (L / 2) * (L / 2)) break; // triangle inequality, |OP| < L / 2
			if (Sqrt[t]) ++vn, x[vn] = i, y[vn] = j, l[vn] = Sqrt[t];
		}
		int ret = 23333;
		rep(i, 1, vn) rep(j, i + 1, vn){
			if (x[i] * y[j] == x[j] * y[i]) continue; // OPQ on the same line
			int t = (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]); // t^2 = |PQ| 
			if (t < MX && Sqrt[t] && l[i] + l[j] + Sqrt[t] == L) // if ok
				ret = min(ret, max({l[i], l[j], Sqrt[t]}) - min({l[i], l[j], Sqrt[t]}));
		}
		return ret < 23333 ? ret : L / 2 % 2; // make a rectangle in case of no valid triangles
	}
};

/*
	Sokomadeda!
*/
