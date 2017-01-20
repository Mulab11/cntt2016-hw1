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
const int N = 2501;
int a[N][N], b[N][N];
int num1[N], num2[N];
int n, x;
class TreeUnion {
	public:
		double expectedCycles(vector<string> tree1, vector<string> tree2, int K) {
            REP(i, 1, tree1.size() - 1) tree1[0] += tree1[i];
            REP(i, 1, tree2.size() - 1) tree2[0] += tree2[i];
            stringstream fin; fin << tree1[0];
            CL(a, 0x3f); CL(b, 0x3f);
            n = 0;
            while (fin >> x) {
                a[n + 1][x] = a[x][n + 1] = 1;
                ++n;
            }
            n = 0;
            fin.clear(); fin << tree2[0];
            while (fin >> x) {
                b[n + 1][x] = b[x][n + 1] = 1;
                ++n;
            }
            ++n;
            REP(i, 0, n - 1) a[i][i] = b[i][i] = 0;
            REP(k, 0, n - 1)  // floyd计算每棵树两两点之间的距离
                REP(i, 0, n - 1) 
                    REP(j, 0, n - 1) getmin(&a[i][j], a[i][k] + a[k][j]), getmin(&b[i][j], b[i][k] + b[k][j]); 
            CL(num1, 0); CL(num2, 0);
            REP(i, 0, n - 1)  // 每棵树上距离为d的点对的数量
                REP(j, i + 1, n - 1) num1[a[i][j]] ++, num2[b[i][j]]++;
            double ans = 0;
            REP(i, 1, n - 1)
                REP(j, 1, n - 1) {
                    if (i + j != K - 2) continue;
                    ans += 2.0 * num1[i] * num2[j]; //统计长度为k的环的个数
                }
			return ans / (double)n / (double)(n - 1);
		}
};

// CUT begin
ifstream data("TreeUnion.sample");

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

bool do_test(vector<string> tree1, vector<string> tree2, int K, double __expected) {
    time_t startClock = clock();
    TreeUnion *instance = new TreeUnion();
    double __result = instance->expectedCycles(tree1, tree2, K);
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
        vector<string> tree1;
        from_stream(tree1);
        vector<string> tree2;
        from_stream(tree2);
        int K;
        from_stream(K);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(tree1, tree2, K, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1479279360;
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
        cout << "TreeUnion (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
