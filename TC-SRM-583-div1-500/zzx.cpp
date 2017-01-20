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
const int N = 51;
int head[N], cnt;
struct node {
	int p, next, w;
}edge[N * 2]; // edge node
int f[N][2], g[2][2]; // f[i][0] allude the subtree i with node path outside  f[0][1] allude that the subtree i with one path outside 
void ae(int a, int b, int c) { // add new edges
	edge[++cnt].p = b;
	edge[cnt].w = c;
	edge[cnt].next = head[a];
	head[a] = cnt;
}
void dp(int u, int fa) { //dynamic programming
	RED(k, u) {
		int v = edge[k].p;
		if (v != fa) dp(v, u); // enum each son of node u
	}
	int c = 0;
	g[c][0] = 0;
	g[c][1] = 100;
	RED(k, u) {
		int v = edge[k].p;
		if (v == fa) continue;
		c ^= 1;
		g[c][0] = g[c][1] = 100;
		if (edge[k].w != 1) getmin(&g[c][0], g[c ^ 1][0] + f[v][0]), // this edge must be chosen
			getmin(&g[c][1], g[c ^ 1][1] + f[v][0]); 
		if (edge[k].w != 2) getmin(&g[c][0], g[c ^ 1][1] + f[v][1] - 1), // this edge must not be chosen
			getmin(&g[c][1], g[c ^ 1][0] + f[v][1]);
	}
	f[u][0] = min(g[c][0], g[c][1]); // update the f array
	f[u][1] = min(f[u][0] + 1, g[c][1]);
}
int n;
class TurnOnLamps {
	public:
		int minimize(vector<int> roads, string initState, string isImportant) {
			n = roads.size() + 1;
			cnt = 0;
			CL(head, 0);
			REP(i, 0, n - 2) {
				int x = 0;
				if (initState[i] == '0' && isImportant[i] == '1') x = 1; // this edge must be chosen
				if (initState[i] == '1' && isImportant[i] == '1') x = 2; // this edge can't be chosen
				ae(roads[i], i + 1, x);
				ae(i + 1, roads[i], x);
			}
			dp(0, -1);
			return f[0][0];
		}
};

// CUT begin
ifstream data("TurnOnLamps.sample");

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

bool do_test(vector<int> roads, string initState, string isImportant, int __expected) {
    time_t startClock = clock();
    TurnOnLamps *instance = new TurnOnLamps();
    int __result = instance->minimize(roads, initState, isImportant);
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
        vector<int> roads;
        from_stream(roads);
        string initState;
        from_stream(initState);
        string isImportant;
        from_stream(isImportant);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(roads, initState, isImportant, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1481615253;
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
        cout << "TurnOnLamps (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
