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
const int N = 2100000;
int f[N], inv[N];
int C(int a, int b) {
    return 1LL * f[a] * inv[b] % mo * inv[a - b] % mo;
}

int calc(int X, int Y, int Z) {//计算有X个R Y个G Z个B情况且相邻颜色不同的方案数
    if (X <= 0) return 0;
    int res = 0;
    REP(g, X - 1, X) //组数
        for (int ev = 0, xp = 1; ev <= g; ev++, xp = (xp + xp) % mo) { //枚举数量为偶数的组数
            if ( (g - ev + Y - Z) % 2 != 0) continue;
            int oy = (g - ev + Y - Z) / 2; // G多的
            int oz = g - ev - oy; //B多的

            if (oy >= 0 && oz >= 0 && Y - oy >= 0) {
                int r = Y - oy - ev;
                if (r < 0) continue;
                int p = C(r+g-1, r);
                p = 1LL * p * C(g,ev) % mo;
                p = 1LL * p * C(g - ev, oy) % mo;
                p = 1LL * p * xp % mo;
                res = (res + p) % mo;

            }

        }
    return res;
}
class LittleElephantAndBoard {
    public:
        int getNumber(int M, int R, int G, int B) {
            f[0] = 1;
            REP(i, 1, 2 * M) f[i] = 1LL * f[i - 1] * i % mo;
            inv[2 * M] = pow(f[2 * M], mo - 2);
            PER(i, 2 * M - 1, 0) inv[i] = 1LL * inv[i + 1] * (i + 1) % mo;
            int ans = 2LL * calc(M - R, M - G, M - B) % mo;
            ans = (ans + 2LL * calc(M - G, M - R, M - B) % mo) % mo;
            ans = (ans + 2LL * calc(M - B, M - R, M - G) % mo) % mo;
            return ans;
        }
};

// CUT begin
ifstream data("LittleElephantAndBoard.sample");

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

bool do_test(int M, int R, int G, int B, int __expected) {
    time_t startClock = clock();
    LittleElephantAndBoard *instance = new LittleElephantAndBoard();
    int __result = instance->getNumber(M, R, G, B);
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
        int M;
        from_stream(M);
        int R;
        from_stream(R);
        int G;
        from_stream(G);
        int B;
        from_stream(B);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(M, R, G, B, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1476940912;
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
        cout << "LittleElephantAndBoard (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
