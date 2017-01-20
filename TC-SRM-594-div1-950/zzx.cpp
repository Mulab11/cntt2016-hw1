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
int m, ans;

bool Single(int n, int x) {
    if (x == n - 1 && x < m) return 1;
    if (x == m - 1 && n <= 2 * m - 1) return 1;
    if (x == 0 && n <= m) return 1;
    if (x == n - 1 && x % m == 0) return 1;
    if (x == 0 && m == 1) return 1;
    return 0;
}

void solve(int level, int n, int x) {
    if(n == 1) {
        getmin(&ans, level);
        return;
    }
    if (Single(n,x)) {
        getmin(&ans, level + 1);
        return;
    }
    if(level + 2 >= ans) return;
    int r = x / m;
    REP(i, 1, r) REP(j, 1, m) solve(level + 1, n - i * j, x - i * j);
    int tmp;
    int tt = min(n, (r + 1) * m);
    solve(level + 1, tt, x);
    tt = n; tmp = x;
    REP(i, 1, x % m) {
        int h = (n - i) / m + 1;
        tt -= h;
        tmp -= (r + 1);
        REP(j, 0, r) solve(level + 1, tt + i * j, tmp + i * j);
    }

    tt = n; tmp = x;
    REP(i, 1, m - 1 - x % m) {
        int h = (n - i - x % m - 1 + m) / m;
        tt -= h;
        tmp -= r;
        REP(j, 0, r) solve(level + 1, tt + j * i, tmp + j * i);
    }
}
class FoxAndAvatar {
    public:
        int minimalSteps(int n, int width, int x){
            m = width;
            ans = 4;
            solve(0, n, x-1);
            return ans;
        }
};

// CUT begin
ifstream data("FoxAndAvatar.sample");

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

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(int n, int width, int x, int __expected) {
    time_t startClock = clock();
    FoxAndAvatar *instance = new FoxAndAvatar();
    int __result = instance->minimalSteps(n, width, x);
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
        int n;
        from_stream(n);
        int width;
        from_stream(width);
        int x;
        from_stream(x);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, width, x, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1484797553;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 950 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "FoxAndAvatar (950 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
