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
int a[N][N];
int n, m;
int f[N], c[N];
vector<int> v[N];
int get(int u) { //并查集
    if (u == f[u]) return u;
    return f[u] = get(f[u]);
}
int join(int a, int b) {
    return f[get(a)] = get(b);
}
bool dfs(int a, int x) { //判断一个图是否是二分图
    c[a] = x;
    for (int i = 0; i < v[a].size(); ++i) {
        int b = v[a][i];
        if (c[b] && c[b] == x) return false;
        if (!c[b] && !dfs(b, 3 - x)) return false;
    }
    return true;
} 
bool check() {
    if (n == 1 || m == 1) return true; //trivial的情况先判掉
    REP(i, 1, n) v[i].clear();
    REP(i, 1, n) f[i] = i;
    CL(c, 0);
    REP(i, 1, m) {   // 判断行与行之间的关系，是相同还是相异
        int last = 0;
        REP(j, 1, n) if (a[j][i] != -1) {
            if (a[last][i] == a[j][i]) {
                join(j, last); //相同的话就用并查集放在一个集合里
            }
            last = j;
        }
    }
    REP(i, 1, m) {
        int last = 0;
        REP(j, 1, n) if (a[j][i] != -1) {
            if (a[last][i] != a[j][i] && last) {
                v[get(last)].PB(get(j)), v[get(j)].PB(get(last)); //不同就在集合之间连边
            }
            last = j;
        }
    }
    REP(i, 1, n) if (f[i] == i && !c[i]  && !dfs(i, 1)) return false;
    return true;
}
class ThreeColorability {
	public:
		vector<string> lexSmallest(vector<string> cells) {
            CL(a, 0xff);
            n = cells.size(); m = cells[0].size();
            REP(i, 1, n) REP(j, 1, m) if (cells[i - 1][j - 1] != '?') a[i][j] = (cells[i - 1][j - 1] == 'Z');
            REP(i, 1, n) REP(j, 1, m) if (a[i][j] == -1) { //一位一位枚举然后判断是不是合法
                a[i][j] = 0; //优先判断是不是N
                if (!check()) a[i][j] = 1; //如果N不是那就只能是Z
            }
            vector<string> e;
            if (!check()) return e; //如果不合法就返回空集
            REP(i, 1, n) REP(j, 1, m) if (a[i][j]) cells[i - 1][j - 1] = 'Z';
            else cells[i - 1][j - 1] = 'N';
            return cells;
		}
};

// CUT begin
ifstream data("ThreeColorability.sample");

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

template <typename T> string to_string(vector<T> ts) {
    stringstream s;
    s << "[ ";
    for (int i = 0; i < ts.size(); ++i) {
        if (i > 0) s << ", ";
        s << to_string(ts[i]);
    }
    s << " ]";
    return s.str();
}

bool do_test(vector<string> cells, vector<string> __expected) {
    time_t startClock = clock();
    ThreeColorability *instance = new ThreeColorability();
    vector<string> __result = instance->lexSmallest(cells);
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
        vector<string> cells;
        from_stream(cells);
        next_line();
        vector<string> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(cells, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1478158926;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 900 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "ThreeColorability (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
