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
const int N = 2600; 
int f[N];
PII a[N];
int l[N], r[N];
bool el[N], er[N];
int n;
bool cmp(const PII &A, const PII &B) {
    return A.SC - A.FR > B.SC - B.FR;
}
bool intersect(int x, int y) {
    return a[x].SC <= a[y].SC && a[x].SC >= a[y].FR;
}
int calcL(int x) {
    int res = 0;
    while (!el[x]) {
        if (x == l[x]) return -1;
        x = l[x]; ++res;
    }
    return res;

}
int calcR(int x) {
    int res = 0;
    while (!er[x]) {
        if (x == r[x]) return -1;
        x = r[x]; ++res;
    }
    return res;

}
class ShoutterDiv1 {
	public:
		int count(vector<string> s1000, vector<string> s100, vector<string> s10, vector<string> s1, vector<string> t1000, vector<string> t100, vector<string> t10, vector<string> t1) {
            CL(el, 1); CL(er, 1);
            CL(l, 0); CL(r, 0);
            REP(i, 1, s1.size() - 1) s1000[0] += s1000[i], s100[0] += s100[i], s10[0] += s10[i], s1[0] += s1[i];
            REP(i, 1, s1.size() - 1) t1000[0] += t1000[i], t100[0] += t100[i], t10[0] += t10[i], t1[0] += t1[i];
            n = s1[0].size();
            REP(i, 1, n) a[i].FR = (s1000[0][i - 1] - 0) * 1000 + (s100[0][i - 1] - '0') * 100 + (s10[0][i - 1] - '0') * 10 
                + s1[0][i - 1] - '0';

            REP(i, 1, n) a[i].SC = (t1000[0][i - 1] - 0) * 1000 + (t100[0][i - 1] - '0') * 100 + (t10[0][i - 1] - '0') * 10 
                + t1[0][i - 1] - '0';
            sort(a + 1, a + n + 1, cmp);
            REP(i, 1, n) 
                REP(j, 1, n) {
                    if (a[j].FR > a[i].SC) er[i] = 0;
                    if (a[j].SC < a[i].FR) el[i] = 0;
                }
            REP(i, 1, n) {
                l[i] = r[i] = i;
                REP(j, 1, n) if (a[j].FR <= a[i].SC && a[j].SC > a[r[i]].SC) r[i] = j;
                REP(j, 1, n) if (a[j].SC >= a[i].FR && a[j].FR < a[l[i]].FR) l[i] = j;
            }
            int ans = 0;
            REP(i, 1, n) {
                f[i] = 1e9;
                REP(j, 1, i - 1) if (a[j].FR <= a[i].FR && a[j].SC >= a[i].SC) getmin(&f[i], f[j] + 1);
                int fl = calcL(i), fr = calcR(i);
                if (fl == -1 || fr == -1) return -1;
                getmin(&f[i], fl + fr);
                ans += f[i];
            }
			return ans;
		}
};

// CUT begin
ifstream data("ShoutterDiv1.sample");

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

bool do_test(vector<string> s1000, vector<string> s100, vector<string> s10, vector<string> s1, vector<string> t1000, vector<string> t100, vector<string> t10, vector<string> t1, int __expected) {
    time_t startClock = clock();
    ShoutterDiv1 *instance = new ShoutterDiv1();
    int __result = instance->count(s1000, s100, s10, s1, t1000, t100, t10, t1);
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
        vector<string> s1000;
        from_stream(s1000);
        vector<string> s100;
        from_stream(s100);
        vector<string> s10;
        from_stream(s10);
        vector<string> s1;
        from_stream(s1);
        vector<string> t1000;
        from_stream(t1000);
        vector<string> t100;
        from_stream(t100);
        vector<string> t10;
        from_stream(t10);
        vector<string> t1;
        from_stream(t1);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(s1000, s100, s10, s1, t1000, t100, t10, t1, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1477446118;
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
        cout << "ShoutterDiv1 (600 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
