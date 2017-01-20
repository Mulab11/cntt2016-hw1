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
/*
 * dynamic programming
 * first we notice that if there is only one string then the best strategy is look like ABCD..HHHHH..XYZ
 * 25charaters occur once and one occurs multiple times
 * second, the value of one arrangement is (Ra - La) + (Rb - Lb) ... + (Rz - Lz) = sigma Ri - sigma Li
 * so we can deal the contribution separately 
 * f[i][j][k] means the minimum contribution we have dealt first i strings, there are i charaters which has occurred, j charater can't be used any more
 * we can transform this dp by considering the number of new charaters of this string and the number of charaters which ends in this string.
 * we can calculate this contribution at beginning
 */
const int N = 52;
int f[N][30][30];
int g[N][30][30];
int a[N], n, num[N];
int C(int a, int b, int d) { // calc the sum of one series
    return (a + a + d * (b - 1)) * b / 2;
}
int calc(int L, int R, int l, int r) {// calculate the array g
    int ans = 1e9;
    int x = 25;
    if (R - L + 1 <= 26) return C(L, l, 1) - C(R - r + 1, r, 1);
    REP(c, 0, x) {
        vector<int> v;
        REP(i, 1, c) v.PB(1);
        REP(i, 1, 26 - x) v.PB(R - L + 1 - 25);
        REP(i, 1, x - c) v.PB(1);
        int tmp = 0, cur = L - 1;
        REP(i, 0, l - 1) cur += v[i], tmp += cur;
        cur = R + 1;
        REP(i, 0, r - 1) cur -= v[26 - i - 1], tmp -= cur;
        getmin(&ans, tmp);
    }
    return ans;
}
class StringWeight {
	public:
		int getMinimum(vector<int> L) {
            n = L.size();
            REP(i, 1, n) a[i] = L[i - 1];
            REP(i, 1, n) if (a[i] < 26) num[i] = a[i]; else num[i] = 26;
            int cur = 0;
            REP(i, 1, n) {
                REP(j, 0, num[i]) REP(k, 0, num[i]) 
                    g[i][j][k] = calc(cur + 1, cur + a[i], j, k);
                cur += a[i];
            }
            REP(i, 0, n) REP(j, 0, 26) REP(k, 0, 26) f[i][j][k] = 1e9;
            f[0][0][0] = 0;
            REP(i, 1, n) REP(j, 0, 26) REP(k, 0, j) if (f[i - 1][j][k] < 1e9) {
                REP(na, max(num[i] - (j - k), 0), 26 - j) //enumerate the number of charaters
                REP(nb, 0, num[i]) if (k + nb <= j + na) {
                    getmin(&f[i][j + na][k + nb], f[i - 1][j][k] + g[i][nb][na]);
                }
            }
            int ans = 1e9;
            int cnt = 0;
            REP(i, 0,26) getmin(&ans, f[n][i][i]);
			return ans;
		}
};

// CUT begin
ifstream data("StringWeight.sample");

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

bool do_test(vector<int> L, int __expected) {
    time_t startClock = clock();
    StringWeight *instance = new StringWeight();
    int __result = instance->getMinimum(L);
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
        vector<int> L;
        from_stream(L);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(L, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1484119257;
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
        cout << "StringWeight (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
