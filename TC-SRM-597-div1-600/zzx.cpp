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
int n;
LL area(int x1, int y1, int x2, int y2) { //计算叉积
    return 1LL * x1 * y2 - 1LL * x2 * y1;
}
int gcd(int a, int b) { // 计算gcd
    if (!b) return a;
    return gcd(b,a % b);
}
double eval(int x1, int y1, int x2, int y2, int x) { //计算x在直线上的y坐标
    return 1.0 * y1 + 1.0 * (y2 - y1) / (x2 - x1) * (x - x1);
}
PII t[210000];
vector<PII> P;
class ConvexPolygonGame {
	public:
		string winner(vector<int> X, vector<int> Y) {
            n = X.size();
            P.clear();
            CL(t, 0);
            LL side = 0, s = 0;
            int x1 = 1e9, x2 = -1e9;
            X.PB(X[0]); Y.PB(Y[0]);
            REP(i, 0, n - 1) side += gcd(abs(X[i + 1] - X[i]), abs(Y[i + 1] - Y[i])),
                s += area(X[i], Y[i], X[i + 1], Y[i + 1]);
            s = abs(s);
            LL num = side + (s + 2 - side) / 2 - n; //计算所有合法点的个数 Pick定理
            if (num > 200001) return "Masha"; //如果点大于这个数的话 那么一定就会存在三点共线
            if (num < 3) return "Petya";
            REP(i, 0, n - 1) getmin(&x1, X[i]), getmax(&x2, X[i]);
            PII *v = t + 101000;
            REP(i, 0, n - 1) { //把每个x合法的y区间给求出来
                int x1 = X[i], x2 = X[i + 1];
                int y1 = Y[i], y2 = Y[i + 1];
                if (x1 == x2)
                    v[x1] = MP(min(y1, y2) + 1, max(y1, y2) - 1);
                else if (x1 < x2) {
                    REP(j, x1 + 1, x2 - 1) {
                        v[j].FR = ceil(eval(x1, y1, x2, y2, j));
                    }
                    v[x1].FR = y1 + 1;
                    v[x2].FR = y2 + 1;
                } else {
                    REP(j, x2 + 1, x1 - 1) v[j].SC = floor(eval(x2, y2, x1, y1, j));
                    v[x1].SC = y1 - 1;
                    v[x2].SC = y2 - 1;
                }
            }
            REP(i, x1, x2){  //把每个合法的点都存下来
                REP(j, v[i].FR, v[i].SC) P.PB(MP(i, j));
            }

            REP(i, 2, P.size() - 1) if (area(P[i].FR - P[0].FR, P[i].SC - P[0].SC, P[1].FR - P[0].FR, P[1].SC - P[0].SC) != 0)
                return "Masha";
            
			return "Petya";
		}
};

// CUT begin
ifstream data("ConvexPolygonGame.sample");

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

bool do_test(vector<int> X, vector<int> Y, string __expected) {
    time_t startClock = clock();
    ConvexPolygonGame *instance = new ConvexPolygonGame();
    string __result = instance->winner(X, Y);
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
        vector<int> X;
        from_stream(X);
        vector<int> Y;
        from_stream(Y);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(X, Y, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1476933621;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 600 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "ConvexPolygonGame (600 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
