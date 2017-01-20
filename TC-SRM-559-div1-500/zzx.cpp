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
const int N = 200;
struct node {
	int p, next;
}edge[N];
int head[N], cnt;
void ae(int a, int b) {
	edge[++cnt].p = b;
	edge[cnt].next = head[a];
	head[a] = cnt;
}
LL f[N], h[N];
int size[N], n;
void dp(int u, int fa) {//calc size height of node u
	h[u] = 0;
	size[u] = 1;
	int son = 0;
	int sl = 0, sr = 0;
	int hl = 0, hr = 0;
	LL fl = 1, fr = 1;
	RED(k, u) {
		int v = edge[k].p;
		if (v != fa) {
			son++;
			dp(v, u);
			getmax(&h[u], h[v] + 1);
			size[u] += size[v];
			if (!sl) sl = size[v], fl = f[v], hl = h[v];
			else sr = size[v], fr = f[v], hr = h[v];
		}
	}
	if (!son) { // if u is a leaf
		f[u] = 1;
		return;
	}
	if (son > 2) return; // if u has more than 2 sons, it's illegal
	if (son == 1) f[u] = (sl == 1); // if u has 1 son, it's legal iff its son is a leaf
	else {
		if (sl == sr && __builtin_popcount(sl + 1) == 1) { // merge 2 sons
			f[u] += 2LL * fl * fr;
			return;
		}
		if (sl < sr) swap(sl, sr), swap(fl, fr), swap(hl, hr);
		if (hl == hr + 1 && __builtin_popcount(sr + 1) == 1) f[u] += fl * fr;
		if (hl == hr && __builtin_popcount(sl + 1) == 1) f[u] += fl * fr;
	}
}
class HatRack {
	public:
		long long countWays(vector<int> knob1, vector<int> knob2) {
			n = knob1.size() + 1;
			cnt = 0;
			CL(head, 0);
			REP(i, 0, n - 2) ae(knob1[i], knob2[i]), ae(knob2[i], knob1[i]);
			LL ans = 0;
			REP(i, 1, n){ // enumerate the root
				CL(f, 0); CL(h, 0);
				dp(i, 0);
				ans += f[i];
			}
			return ans;
		}
};

// CUT begin
ifstream data("HatRack.sample");

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

bool do_test(vector<int> knob1, vector<int> knob2, long long __expected) {
    time_t startClock = clock();
    HatRack *instance = new HatRack();
    long long __result = instance->countWays(knob1, knob2);
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
        vector<int> knob1;
        from_stream(knob1);
        vector<int> knob2;
        from_stream(knob2);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(knob1, knob2, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1481198392;
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
        cout << "HatRack (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
