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
PII a[N];
int n, m, K;
bool vis[N];
LL c[N][N];
int num[N];
LL ans;
void dp(int p) {
    static LL f[2][N];
    CL(f, 0);
    f[0][0] = 1;
    int r = 0;
    REP(i, 1, 50) if (vis[i]) {
        r ^= 1;
        CL(f[r], 0);
        int st = 1;
        if (a[p].SC == i) st = 0;
        REP(j, 0, K - 1)
            REP(k, st, num[i]) {
                if (k > j) break;
                f[r][j] = (f[r][j] + f[r ^ 1][j - k] * c[num[i]][k]);
            }
    }
    int x = a[p].FR;
    ++p;
    ans += f[r][K - 1];
    REP(i, 1, K - 1) REP(j, p, n) if (!vis[a[j].SC]) 
        ans += f[r][i - 1] * c[n - j][K - i - 1];
}

bool cmp(const PII &A, const PII &B){
    if (A.FR == B.FR) return vis[A.SC] < vis[B.SC];
    return A.FR < B.FR;
}
class Excavations {
	public:
		long long count(vector<int> kind, vector<int> depth, vector<int> found, int K) {
            n = kind.size();
            REP(i, 1, n) a[i] = MP(depth[i - 1], kind[i - 1]);
            m = found.size();
            CL(vis, 0);
            for (int i = 0; i < found.size(); ++i) vis[found[i]] = 1;
            ::K = K;
            REP(i, 0, 50) {
                c[i][0] = c[i][i] = 1;
                REP(j, 1, i - 1) c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) ;
            }
            sort(a + 1, a + n + 1, cmp);
            CL(num, 0);
            set<int> S;
            ans = 0;
            REP(i, 1, n) {
                if (vis[a[i].SC]) S.insert(a[i].SC);
                if (S.size() == m && vis[a[i].SC]) {
                    dp(i);
                }
                ++num[a[i].SC];
            }
			return ans;
		}
};

// CUT begin
ifstream data("Excavations.sample");

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

bool do_test(vector<int> kind, vector<int> depth, vector<int> found, int K, long long __expected) {
    time_t startClock = clock();
    Excavations *instance = new Excavations();
    long long __result = instance->count(kind, depth, found, K);
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
        vector<int> kind;
        from_stream(kind);
        vector<int> depth;
        from_stream(depth);
        vector<int> found;
        from_stream(found);
        int K;
        from_stream(K);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(kind, depth, found, K, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1478693011;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 600 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "Excavations (600 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
