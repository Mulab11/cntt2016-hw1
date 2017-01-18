#line 2 "CircusTents.cpp"
#include<vector>
#include<list>
#include<map>
#include<set>
#include<deque>
#include<stack>
#include<bitset>
#include<algorithm>
#include<functional>
#include<numeric>
#include<utility>
#include<sstream>
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<cstring>
#define cl(x) memset(x, 0, sizeof(x));
#define pii pair<int, int>
#define fr first
#define sc second
#define mp make_pair
#define pb push_back
#define oo 0x3f3f3f3f
#define maxn 60
#define pi M_PI
#define eps 1e-9
#define pdi pair<double,int>
typedef long long ll;
using namespace std;
int n;
vector <int> x, y, r; // 存放圆的信息
double mul(double x) { // 返回x^2
	return x * x;
}
double dis(double x1, double y1, double x2, double y2) { // (x1,y1), (x2,y2)之间的距离
	return sqrt(mul(x1 - x2) + mul(y1 - y2));
}
int dcmp(double x) { // 比大小用QAQ
	return fabs(x) < eps ? 0 : x > 0 ? 1 : -1;
}
double calc(double x0, double y0, double r0, double x1, double y1, double r1) { // 计算，一条边是(x0,y0),(x1,y1)的连线，一条边长度为r0,一条边长度为r1,这样的一个三角形中，r1所对角的弧度
	double d = dis(x0, y0, x1, y1);
	return acos((mul(x0 - x1) + mul(y0 - y1) + mul(r0) - mul(r1)) / 2.0 / d / r0);
}
vector <pdi> p;
bool cmp(pdi a, pdi b) {
	return fabs(a.fr - b.fr) == 0 ? a.sc > b.sc : a.fr < b.fr; 
}
void mt(double &x) { // 把x调整到[0, 2 * pi]内
	while (x < 0) x += 2 * pi;
	while (x > 2 * pi) x -= 2 * pi;
}
bool check(double lim) { // 检查圆上是否存在一点，到所有圆的距离都至少为lim
	int x0 = x[0], y0 = y[0], r0 = r[0], x1, y1, r1; // (x0,y0,r0),(x1,y1,r1)是目前考虑的一对圆
	p.clear();
	for (int i = 1; i < n; ++i) {
		x1 = x[i]; y1 = y[i]; r1 = r[i];
		double mi = dis(x0, y0, x1, y1) - r0 - r1; // 最短距离
		double mid = sqrt(mul(x1 - x0) + mul(y1 - y0) - mul(r0)) - r1; // 走直线的最长距离
		double a = acos(r0 / dis(x0, y0, x1, y1)); // 能走直线的弧度范围的一半
		double mx = (pi - a) * r0 + mid;  // 最长距离：圆上走(pi - a), 再沿着最长的直线走mid
		double b = atan2(y1 - y0, x1 - x0); // 终边上一点为(x1, y1)的角
		double l, r;
		if (dcmp(mx - lim) < 0) return 0; // lim已经超过了可能的最长距离
		if (dcmp(lim - mi) < 0) {
			p.pb(mp(0, 1)); p.pb(mp(2 * pi, -1)); // lim小于最短距离，整个圆上的点都符合要求
			continue;
		}
		if (dcmp(mid - lim) > 0) { // 走直线的情况
			double d = lim + r1;
			double t = calc(x0, y0, r0, x1, y1, d); // 计算出对应的角的弧度
			l = b + t; r = b - t; // 距离大于lim的范围
		} else { // 先走一段圆弧的情况
			double t = a + (lim - mid) / r0; // 走的圆弧的弧度 + 能走直线的弧度 = 距离小于lim的弧度
			l = b + t; r = b - t; 
		}
		mt(l); mt(r);
		if (l < r) { // 将线段[l, r]覆盖
			p.pb(mp(l, 1));
			p.pb(mp(r, -1));
		} else { // 若跨过了2 * pi,就拆成两段覆盖
			p.pb(mp(l, 1));
			p.pb(mp(2 * pi, -1));
			p.pb(mp(0, 1));
			p.pb(mp(r, -1));
		}
	}
	sort(p.begin(), p.end(), cmp);
	int now = 0;
	for (int i = 0; i < p.size(); ++i) {
		now += p[i].sc;
		if (now == n - 1) return 1; // 若存在交，说明有满足条件的点
	}
	return 0;
}
class CircusTents {
	public:
		double findMaximumDistance(vector <int> X, vector <int> Y, vector <int> R) {
			n = X.size();
			x = X; y = Y; r = R;
			double l = 0, r = 10000000, mid, ans = 0;
			for (int t = 1; t <= 1000; ++t) { // 二分答案
				mid = (l + r) * 0.5; 
				if (check(mid)) { 
					ans = mid; l = mid;
				} else {
					r = mid;
				}
			}
			return ans;
		}
};
