#line 2 "CircusTents.cpp"  
#include <bits/stdc++.h> 

using namespace std;  

#define ui unsigned
#define ll long long

#define pii std::pair<int,int>
#define pdd std::pair<double,double>
#define mp std::make_pair
#define fi first
#define se second

#define SZ(x) (int)(x).size()
#define pb push_back

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(x > y) x = y;}

const int N = 50;
const double eps = 1e-12;
const double pi = acos(-1.0);

struct point {
	double x, y;
	point(double _x = 0, double _y = 0):x(_x), y(_y) {}
};

int n;// 圆数
point o[N + 9];// 圆心坐标
double r[N + 9];// 半径
vector<pdd> seg;// 区间集合

#define sqr(x) ((x) * (x))

double dist(const point &p, const point &q) {
	// 求两点之间的距离
	return sqrt(sqr(p.x - q.x) + sqr(p.y - q.y));
}

void addseg(double l, double r) {
	// 添加一个角度区间[l, r]
	while(l <= -pi) l += 2 * pi;
	while(r > pi) r -= 2 * pi;
	if(l <= r) seg.pb(mp(l, r));
	else seg.pb(mp(l, pi)), seg.pb(mp(-pi, r));
}

bool check(double dis) {
	seg.clear();
	for(int i = 1; i < n; ++i) {
		double d = dist(o[i], o[0]);// 圆心i和圆心0的距离
		double l = sqrt(sqr(d) - sqr(r[0]));// 圆心i到圆0的切线长度
		double t = l - r[i];// 切线长度 - 圆i的半径
		double alpha = atan2(o[i].y - o[0].y, o[i].x - o[0].x);// 以圆心0为原点，圆心i的方位角
		if(dis <= t) {
			if(dis < d - r[0] - r[i]) continue;// dis < 最小距离 显然无法构成区间
			double theta = acos((sqr(r[0]) + sqr(d) - sqr(dis + r[i])) / (2 * r[0] * d));// 余弦定理
			addseg(alpha - theta, alpha + theta);
		}
		else {
			double theta = acos((sqr(r[0]) + sqr(d) - sqr(l)) / (2 * r[0] * d));// 余弦定理
			double arc = (pi - theta) * r[0];// 最长弧长
			if(dis >= t + arc) return false;// 整个圆都被覆盖了，显然答案 < dis
			double beta = (dis - t) / r[0];// 角 * 半径 = 弧长
			addseg(alpha - theta - beta, alpha + theta + beta);
		}
	}
	sort(seg.begin(), seg.end());
	double ri = -pi;
	for(int i = 0; i < SZ(seg); ++i) {
		if(seg[i].fi > ri) return true;// 有未被覆盖的区间，这个区间内的点的 remoteness 都 >= dis
		else chkmax(ri, seg[i].se);
	}
	return ri < pi;// 检查结尾是否有空余区间
}

class CircusTents {  
public:  
	double findMaximumDistance(vector <int> x, vector <int> y, vector <int> r) {  
		n = SZ(x);
		for(int i = 0; i < n; ++i)
			o[i] = point(x[i], y[i]), ::r[i] = r[i];
		// 二分答案
		double le = 0, ri = 1e6;
		int cnt = 100;// 限制搜索次数以防超时
		while(ri - le > eps && cnt--) {
			double mid = (le + ri) / 2;
			if(check(mid)) le = mid;
			else ri = mid;
		}
		return (le + ri) / 2;
	}    
};  
