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
int f[N][N][N][2], a[N][N], h[N][N][N];
int n, m;
class WallGameDiv1 {
	public:
		int play(vector<string> costs) {
            CL(f, 0);
            n = costs.size(); m = costs[0].size();
            REP(i, 0, n - 1) REP(j, 0, m - 1) a[i + 1][j + 1] = costs[i][j] - '0';
            REP(i, 1, n) REP(j, 1, m) {
                h[i][j][j] = a[i][j];
                REP(k, j + 1, m) h[i][j][k] = h[i][j][k - 1] + a[i][k];
            }
            REP(i, 1, m) f[n][i][i][0] = 0;
            PER(i, n - 1, 1) {
                REP(j, 1, m) f[i][0][j][0] = 1e9;
                REP(j, 1, m) f[i][j][m + 1][1] = 1e9;
                f[i][1][m][0] = f[i + 1][1][1][0] + a[i + 1][1];
                f[i][1][m][1] = f[i + 1][m][m][0] + a[i + 1][m];
                PER(l, m - 2, 0) 
                    REP(j, 1, m - l) {
                        int k = j + l;
                        f[i][j][k][0] = max(f[i + 1][j][j][0] + a[i + 1][j], 
                                min(f[i][j - 1][k][0] + a[i][j - 1], f[i][j][k + 1][1] + h[i][j + 1][k + 1]));

                        f[i][j][k][1] = max(f[i + 1][k][k][0] + a[i + 1][k], 
                                min(f[i][j][k + 1][1] + a[i][k + 1], f[i][j - 1][k][0] + h[i][j - 1][k - 1]));
                    }
            }
            int ans = 1e9;
            REP(i, 1, m) {
                getmin(&ans, f[1][i][i][0] + a[1][i]);
            }
			return ans;
		}
};

// CUT begin
ifstream data("WallGameDiv1.sample");

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

bool do_test(vector<string> costs, int __expected) {
    time_t startClock = clock();
    WallGameDiv1 *instance = new WallGameDiv1();
    int __result = instance->play(costs);
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
        vector<string> costs;
        from_stream(costs);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(costs, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1477447745;
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
        cout << "WallGameDiv1 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
