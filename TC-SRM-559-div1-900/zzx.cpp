/* Copyright 2016 AcrossTheSky */
#include <iostream>
#include <cstdio>
#include <utility>
#include <cassert>
#include <map>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <sstream>
#include <bitset>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#define REP(i, a, b) for (int i = (a); i <= (b); ++i)
#define PER(i, a, b) for (int i = (a); i >= (b); --i)
#define RVC(i, c) fot (int i = 0; i < (c).size(); ++i)
#define RED(k, u) for (int k = head[(u)]; k; k = edge[k].next)
#define lowbit(x) ((x) & (-(x)))
#define CL(x, v) memset(x, v, sizeof x)
#define MP std::make_pair
#define PB push_back
#define FR first
#define SC second
#define rank rankk
#define next nextt
#define link linkk
#define index indexx
#define abs(x) ((x) > 0 ? (x) : (-(x)))
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

template<class T> inline
bool getmin(T *a, const T &b) {
	if (b < *a) {
		*a = b;
		return true;
	}
	return false;
}

template<class T> inline
bool getmax(T *a, const T &b) {
	if (b > *a) {
		*a = b;
		return true;
	}
	return false;
}

const int mo = 1000000007;
template<class T>
T pow(T a, T b, int c = mo) {
	T res = 1;
	for (T i = 1; i <= b; i <<= 1, a = 1LL * a * a % c) if (b & i) res = 1LL * res * a % c;
	return res;
}

/*======================= TEMPLATE =======================*/
const double pi = acos(-1);
struct Point {
	double x, y;
	Point() {}
	Point(const double &_x, const double &_y) {
		x = _x, y = _y;
	}
	Point operator + (const Point &B) {
		return Point(x + B.x, y + B.y);
	}
	Point operator - (const Point &B) {
		return Point(x - B.x, y - B.y);
	}
	double ang() {
		return atan2(y, x);
	}
	void rotate(double a) {
		double x1 = x * cos(a) - y * sin(a);
		double y1 = x * sin(a) + y * cos(a);
		x = x1, y = y1;
	}
	double dis(const Point &B) {
		return sqrt((x - B.x) * (x - B.x) + (y - B.y) * (y - B.y));
	}
};
double cut(double r, double x) {
	return acos(r / x);
}
void maintain(double &x) {
	while (x >= 2.0 * pi) x -= 2.0 * pi;
	while (x < 0) x += 2.0 * pi;
}
struct Circle {
	Point o;
	double r;
	double tangent(Point P) {
		return cut(r, o.dis(P));
	}
}a[100];
pair<double, int> c[1000];
int n;
int cnt;
void add(double l, double r) {
	maintain(l); 
	maintain(r); 
	if (l < r) c[++cnt] = MP(l, 1), c[++cnt] = MP(r, -1);
	else c[++cnt] = MP(l, 1), c[++cnt] = MP(r, -1), c[++cnt] = MP(0, 1);
}
double ac(double l, double r, double x) { //calc arccos
	REP(tt, 1, 100) {
		double m = (l + r) / 2.0;
		if (cos(m) > x) l = m;
		else r = m;
	}
	return l;
}
double len(double l, double r, double x, double R) {
	REP(tt, 1, 100) {
		double m = (l + r) / 2.0;
		if (m * R < x) l = m;
		else r = m;
	}
	return l;
}
bool check(double x) {// check if x is a valid answer
	cnt = 0;
	REP(i, 2, n) {
		double d1 = (a[i].o - a[1].o).ang();
		maintain(d1);
		double d2 = a[1].tangent(a[i].o);
		double d = a[i].o.dis(a[1].o);
		double d3 = ac(1e-10, pi, (d * d + a[1].r * a[1].r - (x + a[i].r) * (x + a[i].r)) /2.0 /d / a[1].r);
		if (d3 < d2) add(d1 - d3, d1 + d3);
		else {
			d3 = d2 + len(1e-10, pi - d2, x - sqrt(d * d - a[1].r * a[1].r) + a[i].r, a[1].r);
			add(d1 - d3, d1 + d3);
		}
	}
	sort(c + 1, c + cnt + 1);
	c[cnt + 1] = MP(2.0 * pi, 0);
	int now = 0;
	double ans = 0;
	REP(i, 1, cnt) {
		now += c[i].SC;
		if (now) ans += c[i + 1].FR - c[i].FR;
	}
	return ans < 2.0 * pi - 1e-10;
}
class CircusTents {
	public:
		double findMaximumDistance(vector<int> x, vector<int> y, vector<int> R) {
			n = x.size();
			REP(i, 1, n) {
				a[i].o = Point(x[i - 1], y[i - 1]);
				a[i].r = R[i - 1];
			}
			double l = 0, r = 1e9;
			REP(tt, 1, 100) { // enumrate the answer
				double m = (l + r) / 2.0;
				if (check(m)) l = m;
				else r = m;
			}
			return l;
		}
};

// CUT begin
ifstream data("CircusTents.sample");

string next_line() {
    string s;
    getline(data, s);
    return s;
}

template <typename T> void from_stream(T &t) {
    stringstream ss(next_line());
    ss >> t;
}

void from_stream(string &s) {
    s = next_line();
}

template <typename T> void from_stream(vector<T> &ts) {
    int len;
    from_stream(len);
    ts.clear();
    for (int i = 0; i < len; ++i) {
        T t;
        from_stream(t);
        ts.push_back(t);
    }
}

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool double_equal(const double &a, const double &b) { return b==b && a==a && fabs(b - a) <= 1e-9 * max(1.0, fabs(a) ); }

bool do_test(vector<int> x, vector<int> y, vector<int> r, double __expected) {
    time_t startClock = clock();
    CircusTents *instance = new CircusTents();
    double __result = instance->findMaximumDistance(x, y, r);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (double_equal(__expected, __result)) {
        cout << "PASSED!" << " (" << elapsed << " seconds)" << endl;
        return true;
    }
    else {
        cout << "FAILED!" << " (" << elapsed << " seconds)" << endl;
        cout << "           Expected: " << to_string(__expected) << endl;
        cout << "           Received: " << to_string(__result) << endl;
        return false;
    }
}

int run_test(bool mainProcess, const set<int> &case_set, const string command) {
    int cases = 0, passed = 0;
    while (true) {
        if (next_line().find("--") != 0)
            break;
        vector<int> x;
        from_stream(x);
        vector<int> y;
        from_stream(y);
        vector<int> r;
        from_stream(r);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(x, y, r, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1481248528;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 900 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);
    set<int> cases;
    bool mainProcess = true;
    for (int i = 1; i < argc; ++i) {
        if ( string(argv[i]) == "-") {
            mainProcess = false;
        } else {
            cases.insert(atoi(argv[i]));
        }
    }
    if (mainProcess) {
        cout << "CircusTents (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
