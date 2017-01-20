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

const int mo = 555555555;
template<class T>
T pow(T a, T b, int c = mo) {
	T res = 1;
	for (T i = 1; i <= b; i <<= 1, a = 1LL * a * a % c) if (b & i) res = 1LL * res * a % c;
	return res;
}

/*======================= TEMPLATE =======================*/
/* C[i] denotes if we flip column i odd times, R[i] denotes if we flip row i odd times
 * A[i][j] = C[i] ^ R[i]
 * sigma A[i][j] = (sigma C[i]) * (H - sigma(R[i])) + (sigma(R[i])) * (W - sigma(C[i]))
 * we can enumerate (sigma C[i]) and (sigma R[i]) and check if the above formula equals to S
 * the number of diffent ways of specific sigmaR and sigmaC is obvious.
 */
const int N = 3300;
int c[N][N];
int calc(int a, int b) { // calculate the number of roots of equation x1 + x2 ... + xa = b, xi >= 0
    return c[a + b - 1][b];
}
class XorBoard {
	public:
		int count(int H, int W, int R, int C, int S) {
            REP(i, 0, 3200) { // pre-calculation
                c[i][i] = c[i][0] = 1;
                REP(j, 1, i - 1) c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mo;
            }
            int ans = 0;
            REP(i, 0, H) if (R % 2 == i % 2) 
                REP(j, 0, W) if (C % 2 == j % 2) { // enumerate sigmaR and sigmaC
                    if (j * (H - i) + i * (W - j) != S) continue;
                    int tmp = 1LL * c[H][i] * c[W][j] % mo;
                    tmp = 1LL * tmp * calc(H, (R - i) / 2) % mo * calc(W, (C - j) / 2) % mo;
                    ans = (ans + tmp) % mo;
                }
			return ans;
		}
};

// CUT begin
ifstream data("XorBoard.sample");

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

bool do_test(int H, int W, int Rcount, int Ccount, int S, int __expected) {
    time_t startClock = clock();
    XorBoard *instance = new XorBoard();
    int __result = instance->count(H, W, Rcount, Ccount, S);
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
        int H;
        from_stream(H);
        int W;
        from_stream(W);
        int Rcount;
        from_stream(Rcount);
        int Ccount;
        from_stream(Ccount);
        int S;
        from_stream(S);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(H, W, Rcount, Ccount, S, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1484206445;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 555 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "XorBoard (555 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
