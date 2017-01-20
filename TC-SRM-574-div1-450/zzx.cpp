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
const int N = 18;
LL f[1 << N][N];
int n;
int getnext(int s, int a) {
    REP(i, a + 1, n - 1) if (s & (1 << i)) return i;
    REP(i, 0, a - 1) if (s & (1 << i)) return i;
}
int getprev(int s, int a) {
    PER(i, a - 1, 0) if (s & (1 << i)) return i;
    PER(i, n - 1, a) if (s & (1 << i)) return i;
}
void dp() {
    REP(i, 1, (1 << n) - 1) 
        REP(j, 0, n - 1) if (i & (1 << j)) if (f[i][j]) {
            int l = getprev(i, j), r = getnext(i, j);
            if (l == r) continue;
            if (l > r) REP(k, r + 1, l - 1) if (i & (1 << k)); else {
                f[i | (1 << k)][k] += f[i][j];
            }
            if (l < r) {
                REP(k, r + 1, n - 1) if (i & (1 << k)); else {
                    f[i | (1 << k)][k] += f[i][j];
                }
                REP(k, 0, l - 1) if (i & (1 << k)); else {
                    f[i | (1 << k)][k] += f[i][j];
                }
            }
        }
}
class PolygonTraversal {
	public:
		long long count(int N, vector<int> points) {
            n = N;
            CL(f, 0);
            int now = 0, p = 0;
            REP(i, 0, points.size() - 1) {
                p = points[i] - 1;
                now |= (1 << p);
            }
            f[now][p] = 1;
            dp();
            LL ans = 0;
            p = points[0] - 1;
            int l = (p + 1)  % n, r = (p - 1 + n) % n;
            REP(i, 0, n - 1) if (i != l && i != r && i != p) ans = (ans + f[(1 << n) - 1][i]);
            return ans;
		}
};

// CUT begin
ifstream data("PolygonTraversal.sample");

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

bool do_test(int N, vector<int> points, long long __expected) {
    time_t startClock = clock();
    PolygonTraversal *instance = new PolygonTraversal();
    long long __result = instance->count(N, points);
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
        int N;
        from_stream(N);
        vector<int> points;
        from_stream(points);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, points, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1478823893;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 450 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "PolygonTraversal (450 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
