#include <bits/stdc++.h>
using namespace std;
const int MAXN = 55;

class Constellation{
public:
	struct Point{
		int x, y;
		Point(){}
		Point(int a, int b): x(a), y(b) {}
		Point operator - (const Point &rhs) const{
			return Point(x - rhs.x, y - rhs.y);
		}
	}p[MAXN];
	double prob[MAXN]; int n;
	inline int Cross(Point a, Point b){return a.x * b.y - a.y * b.x;}
	inline int Dot(Point a, Point b){return a.x * b.x + a.y * b.y;}
	double expectation(vector <int> x, vector <int> y, vector <int> prob_){
		int i, j, k, c; double s, ans = 0.0;
		n = x.size();
		for(i = 0; i < n; ++ i){
			p[i] = Point(x[i], y[i]);
			prob[i] = prob_[i] * 0.001;
		}
		for(i = 0; i < n; ++ i)
			for(j = 0; j < n; ++ j){
				if(i == j) continue;
				for(k = 0, s = 1.0; k < n; ++ k)
					if(k == i || k == j) s *= prob[k];
					else{
						c = Cross(p[j] - p[i], p[k] - p[i]);
						if(c < 0 || (c == 0 && Dot(p[k] - p[i], p[j] - p[i]) * Dot(p[k] - p[j], p[j] - p[i]) < 0))
							s *= 1.0 - prob[k];
					}
				ans += s * Cross(p[i], p[j]);
			}
		return ans / 2.0;
	}
};
