// BEGIN CUT HERE

// END CUT HERE
#line 5 "CheckerFreeness.cpp"
#include <bits/stdc++.h>

using namespace std;

#define SZ(x) (int)(x).size()
#define pb push_back
#define mp make_pair
#define fi first
#define se second

typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<double> VD;
typedef long long ll;
typedef pair<int,int> pii;

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(x > y) x = y;}

struct point {
	double x, y;
	point(double _x = 0, double _y = 0):x(_x), y(_y) {}
	friend point operator - (const point &p, const point &q) {
		return point(p.x - q.x, p.y - q.y);
	}
};

point rotate(const point &p, double a) {// 将点p绕原点逆时针旋转角a
	double cosa = cos(a), sina = sin(a);
	return point(p.x * cosa + p.y * sina, p.y * cosa - p.x * sina);
}

vector<point> w, b;

int ch(const string &s) {// 将字符串变成数
	int ret = 0;
	for(int i = 0; i < SZ(s); ++i)
		ret = ret * 10 + s[i] - '0';
	return ret;
}

void get(const vector<string> &sx, const vector<string> &sy, vector<point> &v) {// 将sx，sy连接起来，分别构成x，y，然后变成点集v
	v.clear();
	string x, y;
	for(int i = 0; i < SZ(sx); ++i) x += sx[i];
	for(int i = 0; i < SZ(sy); ++i) y += sy[i];
	x += ' ', y += ' ';
	for(int i = 0, j = 0; i < SZ(x) && j < SZ(y); ++i, ++j) {
		int k = i, r = j;
		while(x[k] != ' ') ++k;
		while(y[r] != ' ') ++r;
		v.pb(point(ch(x.substr(i, k - i)), ch(y.substr(j, r - j))));
		i = k, j = r;
	}
}

struct CheckerFreeness {
    string isFree(vector <string> whiteX, vector <string> whiteY, vector <string> blackX, vector <string> blackY) {
		get(whiteX, whiteY, w), get(blackX, blackY, b);
		for(int i = 0; i < SZ(w); ++i)
			for(int j = i + 1; j < SZ(w); ++j) {// 枚举两个白点
				// 以w[i]为原点，(w[i],w[j])为x轴
				double a = atan2(w[j].y - w[i].y, w[j].x - w[i].x);
				point u = point(0, 0), v = rotate(w[j] - w[i], a);
				vector<double> upu, upv;
				vector<point> dn;
				for(int k = 0; k < SZ(b); ++k) {// 处理黑点
					point cur = rotate(b[k] - w[i], a);// 绕w[i]逆时针旋转角a
					if(cur.y > 0) upu.pb(atan2(cur.y, cur.x)), upv.pb(atan2(cur.y - v.y, cur.x - v.x));// x轴上方的点
					else dn.pb(cur);// x轴下方的点
				}
				// 角度从小到大，方便后面的二分
				sort(upu.begin(), upu.end());
				sort(upv.begin(), upv.end());
				for(int k = 0; k < SZ(dn); ++k) {
					// 判断射线(d[k], u)和(d[k], v)中间是否夹了点
					point diru = u - dn[k], dirv = v - dn[k];// diru -> 射线(d[k], u), dirv -> 射线(d[k], v)
					double au = atan2(diru.y, diru.x), av = atan2(dirv.y, dirv.x);// 射线的倾斜角
					int su = upper_bound(upu.begin(), upu.end(), au) - upu.begin();// diru右边的点
					int sv = lower_bound(upv.begin(), upv.end(), av) - upv.begin();// dirv右边的点
					if(su > sv) return "NO";// 中间夹了点，不满足checker-free
				}
			}
		return "YES";
    }
};
