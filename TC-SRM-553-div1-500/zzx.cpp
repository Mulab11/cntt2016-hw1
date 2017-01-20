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
int s[2][60][60];
int f[N][N][3]; //1 递增 2 递减
int n, m;
bool check(int i, int j, int c) {
    if (s[c ^ 1][i][j]) return false;
    if ((s[c][i][m] - s[c][i][j])) return false;
    return true;
}
int dp(int c) {

    int ans = 0;
    //f[i][j]代表第i行左侧的颜色长度为j 0代表长度一直不变 1代表递增 2代表递减
    //case1: 每一行的c都左对齐
    CL(f, 0);
    REP(i, 1, m) if (check(1, i, c)) f[1][i][0] = 1;
    REP(i, 2, n) REP(j, 0, m) if (check(i, j, c)){
        f[i][j][0] = f[i - 1][j][0];
        f[i][j][1] = f[i - 1][j][1];
        f[i][j][2] = f[i - 1][j][2];
        REP(k, 0, j - 1) (f[i][j][1] += (f[i - 1][k][1] + f[i - 1][k][0]) % mo) %= mo;
        REP(k, j + 1, m) (f[i][j][2] += (f[i - 1][k][2] + f[i - 1][k][0]) % mo) %= mo;
    }
    REP(i, 0, m) (ans += (f[n][i][0] + f[n][i][2]) % mo) %= mo;
    REP(i, 1, m) ans = (ans + f[n][i][1]) % mo; 

    //case2: 每一行的c都右对齐
    CL(f, 0);
    f[1][0][0] = check(1, m, c);
    REP(i, 2, n) REP(j, 0, m) if (check(i, j, c ^ 1)) {
        f[i][j][0] = f[i - 1][j][0];
        f[i][j][1] = f[i - 1][j][1];
        f[i][j][2] = f[i - 1][j][2];
        REP(k, 0, j - 1) (f[i][j][1] += (f[i - 1][k][1] + f[i - 1][k][0]) % mo) %= mo;
        REP(k, j + 1, m) (f[i][j][2] += (f[i - 1][k][2] + f[i - 1][k][0]) % mo) %= mo;
    }
    REP(i, 0, m) (ans += f[n][i][1]) %= mo;
    REP(i, 1, n - 1) { //去掉case1 case2的重复部分
        if (!check(i, m, c)) break;
        bool flag = 1;
        REP(j, i + 1, n) if (!check(j, m, c ^ 1)) flag = 0;
        if (flag)
        ans = (ans - 1 + mo) % mo;
    }
    return ans;
}
class TwoConvexShapes {
	public:
		int countWays(vector<string> grid) {
            CL(s, 0);
            n = grid.size(); m = grid[0].size();
            REP(i, 1, n) REP(j, 1, m) {
                s[0][i][j] = s[0][i][j - 1] + (grid[i - 1][j - 1] == 'B');
                s[1][i][j] = s[1][i][j - 1] + (grid[i - 1][j - 1] == 'W');
            }
            int ans = 0;
            //cerr << dp(0) << endl;
            if (grid[0][0] != 'W') ans = (ans + dp(0)) % mo; //(0, 0)放B的方案数
            if (grid[0][0] != 'B') ans = (ans + dp(1)) % mo; //(0, 0)放W的方案数
			return ans;
		}
};

// CUT begin
ifstream data("TwoConvexShapes.sample");

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

bool do_test(vector<string> grid, int __expected) {
    time_t startClock = clock();
    TwoConvexShapes *instance = new TwoConvexShapes();
    int __result = instance->countWays(grid);
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
        vector<string> grid;
        from_stream(grid);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(grid, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1478783079;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "TwoConvexShapes (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
