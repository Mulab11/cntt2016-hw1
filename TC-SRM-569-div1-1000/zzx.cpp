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

const int mo = 1000000009;
template<class T>
T pow(T a, T b, T c) {
	T res = 1;
	for (T i = 1; i <= b; i <<= 1, a = 1LL * a * a % c) if (b & i) res = 1LL * res * a % c;
	return res;
}

/*======================= TEMPLATE =======================*/
int n, K, num, m;
struct node {
    int a, b;
};
node operator + (const node &A, const node &B) {
    return (node){(A.a + B.a + (A.b + B.b) / m) % mo, (A.b + B.b) % m};
}
node operator * (const node &A, const node &B) {
    return (node){(int)((1LL * A.a * B.a * m + 1LL * A.b * B.b / m + 1LL * A.a * B.b + 1LL * A.b * B.a) % mo), A.b * B.b % m};
}
struct Matrix {
    node a[20][20];
    Matrix() {
        CL(a, 0);
    }
}A, B, C, T;
Matrix operator *(Matrix A, Matrix B) {
    CL(T.a, 0);
    REP(k, 0, K)
        REP(i, 0, K)
            REP(j, 0, K) T.a[i][j] = T.a[i][j] + A.a[i][k] * B.a[k][j];
    return T;
}
int solve() {
    Matrix A;
    REP(i, 0, K) A.a[i][i] = (node){0, 1};
    Matrix ans = A;
    for (int k = 0; n; ++k) {
        Matrix now;
        now.a[0][0] = (node){0, 1};
        REP(i, 1, K) {
            now.a[0][i] = (node){k / m, k % m};
            REP(j, 1, i) now.a[j][i] = (node){0, 1};
        }
        REP(i, 1, n % num) ans = A * now * ans;
        Matrix B = A;
        REP(i, 1, num - 1) A = A * now * B;
        n /= num;
    }
    return ans.a[0][K].a;
}
class MegaFactorial {
	public:
		int countTrailingZeros(int N, int k, int B) {
            n = N;  K = k;
            int x = 0, y = 0;
            for (int i = 2; i * i <= B; ++i) if (B % i == 0){
                x = i , y = 0;
                while (B % i == 0) B /= i, ++y;
            }
            if (B != 1 && B > x) x = B, y = 1;
            num = x, m = y;
			return solve();
		}
};

// CUT begin
ifstream data("MegaFactorial.sample");

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

bool do_test(int N, int K, int B, int __expected) {
    time_t startClock = clock();
    MegaFactorial *instance = new MegaFactorial();
    int __result = instance->countTrailingZeros(N, K, B);
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
        int B;
        from_stream(B);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, K, B, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1484870820;
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
        cout << "MegaFactorial (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
