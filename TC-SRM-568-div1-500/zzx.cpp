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
const int N = 60;
int n, v[N * 2], a[N * 2][N * 2]; // a[i][j] = b[i] + c[j] 其中 min{b[i]} = 0 min{c[j]} >= 0
int vis[N * 2];
int idx = 0;
bool bfs(int u, int x, int pd = 0) {// 枚举每个连通块的某一个元素, 就可以推出其他的元素 其中b[i] >= pd c[i] >= 0
    static queue<int> q;
    while (!q.empty()) q.pop();
    v[u] = x;
    q.push(u);
    ++idx;
    vis[u] = idx;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u < n && v[u] < pd) return 0;
        if (v[u] < 0) return 0;
        REP(i, 0, 2 * n - 1) if (a[u][i] != -1 && vis[i] != idx) {
            vis[i] = idx;
            v[i] = a[u][i] - v[u];
            q.push(i);
        } else if (a[u][i] != -1 && v[i] + v[u] != a[u][i]) return 0;
    }
    return 1;
}
class EqualSums {
	public:
		int count(vector<string> board) {
            n = board.size();
            CL(a, 0xff);
            REP(i, 0, n - 1) 
                REP(j, 0, n - 1)
                if (isdigit(board[i][j])) a[i][j + n] = a[j + n][i] = board[i][j] - '0'; 
            CL(vis, 0);
            int ans1 = 1, ans2 = 1;
            REP(i, 0, n - 1) if (!vis[i]) { 
                int num = 0, num2 = 0;
                REP(j, 0, 9) if (bfs(i, j)) ++num; // b[i] >= 0
                REP(j, 0, 9) if (bfs(i, j, 1)) ++num2; //容斥 b[i] >= 0的解减去 b[i] >= 1的解就是答案了
                ans1 = 1LL * ans1 * num % mo;
                ans2 = 1LL * ans2 * num2 % mo;
            }
			return (ans1 - ans2 + mo) % mo;
		}
};

// CUT begin
ifstream data("EqualSums.sample");

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

bool do_test(vector<string> board, int __expected) {
    time_t startClock = clock();
    EqualSums *instance = new EqualSums();
    int __result = instance->count(board);
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
        vector<string> board;
        from_stream(board);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(board, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1479293207;
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
        cout << "EqualSums (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
