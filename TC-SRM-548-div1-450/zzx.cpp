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
const int N = 61;
/*
 * f[i][j][k] first i position cur at j k larger
 */

bool f[N][N][N * N];
int a[N], b[N], num[N]; // initialization
int n;
class KingdomAndDice {
	public:
		double newFairness(vector<int> A, vector<int> B, int X) {
            n = A.size();
            int m = 0, z = 0;
            sort(A.begin(), A.end());
            sort(B.begin(), B.end());
            REP(i, 1, n) a[i] = A[i - 1], b[i] = B[i - 1];//最开始的数量
            REP(i, 1, n) if (a[i] == 0) ++z;
            REP(i, 1, n) REP(j, 1, n) if (a[i] > b[j]) ++m;
            b[n + 1] = X + 1;
            num[0] = n;
            REP(i, 1, n) {
                num[i] = b[i + 1] - b[i] - 1;
                REP(j, 1, n) if (a[j] > b[i] && a[j] < b[i + 1]) --num[i];
            }
            CL(f, 0); 
            REP(i, 0, z) f[i][0][m] = 1;
            REP(i, 0, z)
                REP(j, 1, n) 
                    REP(p, 0, min(i, num[j])) 
                        REP(k, j * p, n * n)
                        f[i][j][k] |= f[i - p][j - 1][k - j * p]; // dp
            int ans = -100000000;
            REP(i, 0, n * n) if (f[z][n][i]) {
                if (abs(i * 2 - n * n) < abs(ans * 2 - n * n ))
                    ans = i;
                if (abs(i * 2 - n * n) == abs(ans * 2 - n * n))
                    if (i < ans) ans = i;
            }
            if (!z) ans = m;
			return 1.0 * ans / (n * n);
		}
};

// CUT begin
ifstream data("KingdomAndDice.sample");

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

bool do_test(vector<int> firstDie, vector<int> secondDie, int X, double __expected) {
    time_t startClock = clock();
    KingdomAndDice *instance = new KingdomAndDice();
    double __result = instance->newFairness(firstDie, secondDie, X);
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
        vector<int> firstDie;
        from_stream(firstDie);
        vector<int> secondDie;
        from_stream(secondDie);
        int X;
        from_stream(X);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(firstDie, secondDie, X, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1483962627;
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
        cout << "KingdomAndDice (450 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
