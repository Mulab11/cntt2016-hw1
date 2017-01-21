#include <bits/stdc++.h>

using namespace std; 

int n ; 

const int MAXN = 110 ;  

const double pi = acos(-1); 

struct Point {
		double x, y; 
		Point(double a_ = 0,  double b_ = 0) {
				x = a_ ,  y = b_ ;  
		}
		double len() {
				return sqrt(x * x + y * y); 
		}
		Point operator - (const Point ano) const {
				return Point(x - ano.x,  y - ano.y) ;  
		}
}; 

struct Cir {
		Point p; 
		double r; 
		Cir(){}
		Cir(Point p_,  double r_) {
				p = p_,  r = r_ ;  
		}
} c[MAXN]; 

double theta[MAXN],  len[MAXN] ; 


double abstheta(double theta) {
		for(; theta < 0; theta += 2 * pi); 
		for(; theta > 2 * pi; theta -= 2 * pi); 
		return theta; 
}


double dis(double theta, int u) {
		theta = abstheta(theta); 
		if (theta > pi) theta = 2 * pi - theta; 
		double l = len[u], l1 = l * l - c[0].r * c[0].r; 
		double tmpt = acos((c[0].r * c[0].r + l * l - l1) / (2 * l * c[0].r)); 
		if (theta <= tmpt) {
				return sqrt(c[0].r * c[0].r + len[u] * len[u] - 2 * len[u] * c[0].r * cos(theta)) - c[u].r; 
		} else {
				double dis = sqrt(c[0].r * c[0].r + len[u] * len[u] - 2 * len[u] * c[0].r * cos(tmpt)) - c[u].r; 
				return dis + (theta - tmpt) * c[0].r; 
		}
}


bool check(double d) {
		vector<double> ava; 
		ava.clear(); 
		for(int i = 1; i < n; i ++) {
				theta[i] = atan2(c[i].p.y, c[i].p.x); 
				len[i] = c[i].p.len(); 
				double l = 0, r = pi, tmp = pi + 1; 
				for(int j = 1; j <= 100; j ++) {
						double mid = (l + r) / 2; 
						if (dis(mid, i) >= d) tmp = mid, r = mid;  else l = mid; 
				}
				if (tmp > pi + 0.5) return 0; 
				ava.push_back(abstheta(tmp + theta[i])), ava.push_back(abstheta(theta[i] - tmp)); 
		}
		sort(ava.begin(), ava.end()); 
		ava.push_back(*ava.begin() + 2 * pi); 
		for(int i = 0; i < ava.size() - 1; i ++)
		{
				double tmpf = (ava[i] + ava[i + 1]) / 2; 
				bool flag = 1; 
				for(int j = 1; j < n; j ++)
						if (dis(tmpf - theta[j], j) < d) {flag = 0; break; }
				if (flag) return 1; 
		}
		return 0; 
}
class CircusTents {
		public:

				double findMaximumDistance(vector<int> x,  vector<int> y,  vector<int> r) {
						n = x.size(); 
						for(int i = 0; i < n; i ++) c[i] = Cir(Point(x[i], y[i]), r[i]); 
						for(int i = 1; i < n; i ++) c[i].p = c[i].p - c[0].p; 
						double l = 0, rr = 50000, tmp = 0; 
						for(int i = 1; i <= 100; i ++) {
								double mid = (l + rr) / 2; 
								if (check(mid)) tmp = mid, l = mid;  else rr = mid; 
						}
						return tmp; 
				}
}; 
