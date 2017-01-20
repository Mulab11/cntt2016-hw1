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
const int N = 61;
const LL inf = 0x3f3f3f3f3f3f3f3fll;

LL a[N][N][N * 2 + 10];
void add(int x, int y, int p, int q){ getmin(&a[x][y][N + q], (LL)p); }
class YamanoteLine  
{  
        public:  
        long long howMany(int n, vector <int> s1, vector <int> t1, vector <int> l1, vector <int> s2, vector <int> t2, vector <int> l2)  
        {  
            CL(a, 0x3f);
            REP(i, 0, n) a[i][i][N] = 0;

            REP(i, 0, n) add(i + 1, i, -1, 0); // d[i] + 1 <= d[i + 1]
            add(0, n, 0, 1), add(n, 0, 0, -1); // d[0] + w == d[n]

            for (int i = 0; i < s1.size(); ++ i) add(t1[i], s1[i], -l1[i], int(s1[i] > t1[i]));// d[t] - d[s] >= l | w + d[t] - d[s] >= l
            for (int i = 0; i < s2.size(); ++ i) add(s2[i], t2[i], l2[i], -int(s2[i] > t2[i]));// d[t] - d[s] <= l | w + d[t] - d[s] <= l

            //floyd
            REP(k, 0, n) REP(i, 0, n) REP(x, -N, N) if (a[i][k][N + x] < inf) 
                         REP(j, 0, n) REP(y, max(-N, -N - x), min(N, N - x)) if (a[k][j][N + y] < inf)
                         getmin(&a[i][j][N + x + y], a[i][k][N + x] + a[k][j][N + y]);

            LL l = n, r = inf;

            //getans
            REP(i, 0, n) REP(j, -N, N){
                if (j == 0) if (a[i][i][N + j] < 0) return 0; else; else
                if (a[i][i][N + j] < inf)
                    if (j > 0) getmax(&l, (-a[i][i][N + j] - 1) / j + 1); 
                    else getmin(&r, a[i][i][N + j] / (-j));
            }
            return (r < l ? 0 : (r == inf ? -1 : r - l + 1));
        }  
};

// CUT begin
ifstream data("YamanoteLine.sample");

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

bool do_test(int n, vector<int> s1, vector<int> t1, vector<int> l1, vector<int> s2, vector<int> t2, vector<int> l2, long long __expected) {
    time_t startClock = clock();
    YamanoteLine *instance = new YamanoteLine();
    long long __result = instance->howMany(n, s1, t1, l1, s2, t2, l2);
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
        int n;
        from_stream(n);
        vector<int> s1;
        from_stream(s1);
        vector<int> t1;
        from_stream(t1);
        vector<int> l1;
        from_stream(l1);
        vector<int> s2;
        from_stream(s2);
        vector<int> t2;
        from_stream(t2);
        vector<int> l2;
        from_stream(l2);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, s1, t1, l1, s2, t2, l2, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1478831196;
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
        cout << "YamanoteLine (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
