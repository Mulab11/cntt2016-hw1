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
 * we write each number twice(i.e. 1 -> 1A, 1B) and match the number A and number B in pairs i.e. (2A, 1B) means A[2] = 1 
 * (2B, 1A) means A[1] = 2
 * f[i][j][k] means first i numbers remains j unmatched
 * we always consider one larger number to find another smaller number and make pair with it
 * obviously the magic number for (xA, yB) or (xB, yA) is x, because we only consider the situation that x >= y
 * there are four situation when we consider number x ascendingly in dp:
 * case1:  xA matches anonther number yB which x > y or xB matches yA
 * case2:  xA matches xB
 * case3:  xA xB both matches another number
 * case4   neither xA nor xB matched another number
 */
const int N = 52;
int f[N][N][N * N];
class LittleElephantAndPermutationDiv1 {
	public:
		int getNumber(int n, int m) {
            CL(f, 0);
            f[0][0][0] = 1;
            REP(i, 1, n) 
                REP(j, 0, i) 
                    REP(k, 0, i * i) {
                        if (k >= i) f[i][j][k] = (f[i][j][k] + 2LL * f[i - 1][j][k - i] * j % mo) % mo;
                        if (k >= i) f[i][j][k] = (f[i][j][k] + f[i - 1][j][k - i]) % mo;
                        if (k >= i * 2) f[i][j][k] = (f[i][j][k] + 1LL * f[i - 1][j + 1][k - 2 * i] * (j + 1) * (j + 1) % mo) % mo;
                        if (j) f[i][j][k] = (f[i][j][k] + f[i - 1][j - 1][k]) % mo;
                    }
            int ans = 0;
            REP(i, m, n * n) ans = (ans + f[n][0][i]) % mo;
            REP(i, 1, n) ans = 1LL * ans * i % mo;
			return ans;
		}
};

// CUT begin
ifstream data("LittleElephantAndPermutationDiv1.sample");

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

bool do_test(int N, int K, int __expected) {
    time_t startClock = clock();
    LittleElephantAndPermutationDiv1 *instance = new LittleElephantAndPermutationDiv1();
    int __result = instance->getNumber(N, K);
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
        int K;
        from_stream(K);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, K, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1483601999;
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
        cout << "LittleElephantAndPermutationDiv1 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
