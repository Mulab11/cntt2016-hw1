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
const int N = 100;
/*
 * dynamic programming
 * f[i][j][x][y]: already choose i digits j in the front and the former one is larger or equal target latter one is > = < target
 */
string f[N][N][2][3]; 
bool vis[N][N][2][3];// check if the status has already visited
string s, t;
int n;
string dp(int l, int p, int x, int y) {
    if (l < 0) {
        if (x == 0 || y != 2) return "";
        else return "A";
    }
    if (vis[l][p][x][y]) return f[l][p][x][y];
    vis[l][p][x][y] = 1;
    string res = "A";
    string tmp;
    if (!x || s[l] >= t[p]) { // put the digit in the front
        tmp = dp(l - 1, p + 1, x && s[l] == t[p], y);
        if (tmp != "A") getmin(&res, s[l] + tmp);
    } 
    int yy = y;
    if (s[l] > t[l + p]) yy = 1; // update new y
    if (s[l] < t[l + p]) yy = 2;
    tmp = dp(l - 1, p, x, yy);  // put the digit in the back
    if (tmp != "A") getmin(&res, tmp + s[l]);
    return f[l][p][x][y] = res;
}
class LeftRightDigitsGame2 {
	public:
		string minNumber(string d, string A) {
            CL(vis, 0);
            n = d.size();
            s = d, t = A;
            string ans = dp(n - 1, 0, 1, 0);
            if (ans == "A") ans = "";// no solution
			return ans;
		}
};

// CUT begin
ifstream data("LeftRightDigitsGame2.sample");

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

bool do_test(string digits, string lowerBound, string __expected) {
    time_t startClock = clock();
    LeftRightDigitsGame2 *instance = new LeftRightDigitsGame2();
    string __result = instance->minNumber(digits, lowerBound);
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
        string digits;
        from_stream(digits);
        string lowerBound;
        from_stream(lowerBound);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(digits, lowerBound, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1484053767;
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
        cout << "LeftRightDigitsGame2 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
