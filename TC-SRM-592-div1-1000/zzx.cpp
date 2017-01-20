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
/*
 * A * A = B -> T(A) * T(A) = T(B) 
 * T(A)i = + - sqrt(T(B)i) 
 * enumerate every possible sig 2^n
 * notice that A is symmetric so B is symmetric too
 * only need to enumerate 2 ^ (n / 2) 
 */
#include <complex>
typedef complex<double> Com;
const double pi = 3.1415926535897932384626;
const int N = 30;
int n, T;
Com c[N], w[N], v[N];
int a[N];
void dft(Com *y, int k = 1)// dft
{
    Com z[N];
    CL(z, 0);
    REP(i, 0, n - 1) {
        z[i] = Com(0, 0);
        REP(j, 0, n - 1) z[i] += y[j] * w[i * j % n];
    }
    REP(i, 0, n - 1) y[i] = z[i];
    if (k == -1) REP(i, 0, n - 1) y[i] /= n;
}
int t[N], ans[N];
bool flag;
void relax() // update the answer
{
    if (flag){
        REP(i, 0, n - 1) if (t[i] < ans[i]) break;
        else if (t[i] > ans[i]) return;
    }
    REP(i, 0, n - 1) ans[i] = t[i];
    flag = 1;
}

bool check() // check if the solution is valid
{
    REP(i, 0, n - 1) {
        int sum = 0;
        REP(j, 0, n - 1) sum += t[j] * t[(i - j + n) % n];
        if (sum != a[i]) return false;
    }
    return true;
}
class SplittingFoxes2 {
    public:
        vector<int> getPattern(vector<int> V) {
            n = V.size();
            REP(i, 0, n - 1) a[i] = V[i];
            Com wn(cos(2.0 * pi / n), sin(2.0 * pi / n));
            w[0] = Com(1, 0);
            REP(i, 1, n - 1) w[i] = w[i - 1] * wn;
            REP(i, 0, n - 1) v[i] = Com(1.0 * a[i], 0);
            dft(v);
            REP(i, 1, n - 1) w[i] = w[i - 1] * Com(cos(-2.0 * pi / n), sin(-2.0 * pi / n));
            REP(i, 0, n - 1) v[i] = sqrt(v[i]); 
            int M = n / 2 + 1;
            flag = 0;
            REP(ca, 0, (1 << M) - 1) {
                REP(i, 0, n - 1) c[i] = v[i];
                REP(i, 0, n - 1) if (ca & (1 << min(i, n - i))) c[i] *= -1;
                dft(c, -1);
                REP(i, 0, n - 1) t[i] = (int)(c[i].real() + 0.512345);
                if (check()) relax();
            }
            vector<int> Ans; 
            if (!flag) Ans.PB(-1);
            else {
                REP(i, 0, n - 1) Ans.PB(ans[i]);
            }
            return Ans;
        }
};

// CUT begin
ifstream data("SplittingFoxes2.sample");

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

template <typename T> string to_string(vector<T> ts) {
    stringstream s;
    s << "[ ";
    for (int i = 0; i < ts.size(); ++i) {
        if (i > 0) s << ", ";
        s << to_string(ts[i]);
    }
    s << " ]";
    return s.str();
}

bool do_test(vector<int> amount, vector<int> __expected) {
    time_t startClock = clock();
    SplittingFoxes2 *instance = new SplittingFoxes2();
    vector<int> __result = instance->getPattern(amount);
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
        vector<int> amount;
        from_stream(amount);
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(amount, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1483601468;
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
        cout << "SplittingFoxes2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
