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
const int N = 31;
int n, m, dd;
int s[N][N], t[N][N];
int L[N][N * N * 3], R[N][N * N * 3], U[N][N * N * 3], D[N][N * N * 3];
int A(int x1, int y1, int x2, int y2) {
    return s[x2][y2] + s[x1 - 1][y1 - 1] - s[x1 - 1][y2] - s[x2][y1 - 1];
}

int B(int x1, int y1, int x2, int y2) {
    return t[x2][y2] + t[x1 - 1][y1 - 1] - t[x1 - 1][y2] - t[x2][y1 - 1];
}
int tot;

void mwju(int *a, int x1, int x2, int y1, int y2) { //在一个子矩形的范围内暴力来枚举所有的子矩形
    REP(i, x1, x2)
        REP(j, y1, y2)
            REP(i2, i, x2)
                REP(j2, j, y2) {
                    int s = A(i, j, i2, j2);
                    int d = B(i, j, i2, j2);
                    getmax(&a[d + 1800], s);
                }
    REP(i, -tot - dd, tot)
        REP(j, i, i + 2 * dd) {
            if (j > tot) break;
            getmax(&a[i + 1800], a[j + 1800]);
        }
}

class FoxAndFlowerShopDivOne {
	public:
		int theMaxFlowers(vector<string> flowers, int maxDiff) {
            CL(s, 0); CL(t, 0);
            CL(L, 0xff); CL(R, 0xff); CL(U, 0xff); CL(D, 0xff);
            n = flowers.size(); m = flowers[0].size();
            dd = maxDiff;
            REP(i, 1, n) REP(j, 1, m) {
                s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + (flowers[i - 1][j - 1] != '.');
                int x = 0;
                if (flowers[i - 1][j - 1] == 'L') x = 1;
                if (flowers[i - 1][j - 1] == 'P') x = -1;
                t[i][j] = t[i - 1][j] + t[i][j - 1] - t[i - 1][j - 1] + x; 
            }
            tot = s[n][m];
            REP(i, 1, n) mwju(U[i], 1, i, 1, m); //计算四个方向子矩形的最优值
            PER(i, n, 1) mwju(D[i], i, n, 1, m);
            REP(i, 1, m) mwju(L[i], 1, n, 1, i);
            PER(i, m, 1) mwju(R[i], 1, n, i, m);
            int ans = -1;
            REP(i, 1, n)
                REP(j, 1, m)
                    REP(i2, i, n)
                        REP(j2, j, m) { //枚举第一个矩形的位置
                            int s = A(i, j, i2, j2);
                            int d = B(i, j, i2, j2);
                            int p = -dd - d; 
                            p += 1800;
                            if (i > 1 && U[i - 1][p] >= 0) getmax(&ans, s + U[i - 1][p]); 
                            if (i2 < n && D[i2 + 1][p] >= 0) getmax(&ans, s + D[i2 + 1][p]);
                            if (j > 1 && L[j - 1][p] >= 0) getmax(&ans, s + L[j - 1][p]);
                            if (j2 < m && R[j2 + 1][p] >= 0) getmax(&ans, s + R[j2 + 1][p]);
                        }
			return ans;
		}
};

// CUT begin
ifstream data("FoxAndFlowerShopDivOne.sample");

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

bool do_test(vector<string> flowers, int maxDiff, int __expected) {
    time_t startClock = clock();
    FoxAndFlowerShopDivOne *instance = new FoxAndFlowerShopDivOne();
    int __result = instance->theMaxFlowers(flowers, maxDiff);
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
        vector<string> flowers;
        from_stream(flowers);
        int maxDiff;
        from_stream(maxDiff);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(flowers, maxDiff, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1478502039;
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
        cout << "FoxAndFlowerShopDivOne (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
