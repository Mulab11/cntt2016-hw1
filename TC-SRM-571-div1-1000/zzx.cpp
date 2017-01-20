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
const int N = 60;
double s[N], t[N];
bool vis[N][N];
double x[N], y[N], r[N];
int n;
double dis(int a, int b) { //计算两个点之间距离
    return sqrt((x[a] - x[b]) * (x[a] - x[b]) + (y[a] - y[b]) * (y[a] - y[b]));
}
bool intersect(double l1, double r1, double l2, double r2) { //判断两个区间是否有交集
    if (r1 < l2 + 1e-5 || r2 < l1 + 1e-5) return false;
    return true;
}
bool join(double &l1, double &r1, double l2, double r2) { //将两个区间合并成一个区间
    getmin(&l1, l2); getmax(&r1, r2);
}
class CandyOnDisk {
	public:
		string ableToAchieve(vector<int> X, vector<int> Y, vector<int> R, int sx, int sy, int tx, int ty) {
            n = X.size();
            if (sx == tx && sy == ty) return "YES";//先把不需要转动的部分给判掉
            REP(i, 1, n) x[i] = X[i - 1], y[i] = Y[i - 1], r[i] = R[i - 1], s[i] = 2000000000, t[i] = -1;
            CL(vis, 0);
            x[0] = sx, y[0] = sy;
            x[n + 1] = tx, y[n + 1] = ty;
            REP(i, 1, n) if (dis(0, i) <= r[i]) s[i] = t[i] = dis(0, i); 
            while (1) {  //迭代若干次更新每个盘子的区间
                bool flag = 0;
                REP(i, 1, n) REP(j, 1, n) if (i != j && !vis[i][j] && (x[i] != x[j] || y[i] != y[j]) ) { // 如果两个盘子的是同心的 要判掉
                    double d = dis(i, j);
                    double l1 = max(0.0, d - r[j]), r1 = min(r[i], d + r[j]);
                    double l2 = max(0.0, d - r[i]), r2 = min(r[j], d + r[i]);//如果一个盘子可以到另外一个盘子，那么这两个盘子可以不断重复来到达所有的合法位置
                    if (intersect(s[i], t[i], l1, r1)) {
                        vis[i][j] = 1; flag = 1;
                        join(s[i], t[i], l1, r1);
                        join(s[j], t[j], l2, r2);
                    }
                }
                if (!flag) break;
            }
            REP(i, 1, n) if (intersect(dis(i, n + 1), dis(i, n + 1), s[i], t[i])) return "YES";
			return "NO";
		}
};

// CUT begin
ifstream data("CandyOnDisk.sample");

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

bool do_test(vector<int> x, vector<int> y, vector<int> r, int sx, int sy, int tx, int ty, string __expected) {
    time_t startClock = clock();
    CandyOnDisk *instance = new CandyOnDisk();
    string __result = instance->ableToAchieve(x, y, r, sx, sy, tx, ty);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (__result == __expected) {
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
        int sx;
        from_stream(sx);
        int sy;
        from_stream(sy);
        int tx;
        from_stream(tx);
        int ty;
        from_stream(ty);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(x, y, r, sx, sy, tx, ty, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1478771823;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "CandyOnDisk (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
