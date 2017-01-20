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
struct node {
    int x, y, r;
}a[100];
bool operator < (const node &A, const node &B) {
    return A.r < B.r;
}
int f[100], n;
int dist(int x, int y) { //计算距离
    return (a[x].x - a[y].x) * (a[x].x - a[y].x) + (a[x].y - a[y].y) * (a[x].y - a[y].y);
}
bool inside(int x, int y) { //判断第x个圆是否在第y个圆内
    return dist(x, y) <= a[y].r * a[y].r;
}
bool isanc(int x, int y) { //暴力判断x是否是y的祖先
    if (!y) return false;
    if (y == x) return true;
    return isanc(x, f[y]);
}
int sg[100];
vector<int> ch[100];
int dp(int);
int mex(vector<int> A) { //计算mex
    set<int> S;
    for (int i = 0; i < A.size(); ++i) S.insert(A[i]);
    REP(i, 0, 100) if (S.find(i) == S.end()) return i;
}
int rec(int x, int a) {//把选的点到根的链断开 分别计算新子树的sg
    int last = 0;
    int sum = 0;
    while (f[a] != x) {
        for (int i = 0; i < ch[x].size(); ++i) if (ch[x][i] != last) sum ^= dp(ch[x][i]);
        last = x;
        x = f[x];
    }
    return sum;
}
int dp(int a) { //记忆化搜索计算每棵树的sg值
    if (sg[a] != -1) return sg[a];
    vector<int> A;
    REP(b, 1, n) if (isanc(a, b)) A.PB(rec(b, a));
    return sg[a] = mex(A);
}
class CirclesGame {
	public:
		string whoCanWin(vector<int> x, vector<int> y, vector<int> r) {
            n = x.size();
            CL(sg, 0xff);
            REP(i, 0, n - 1) a[i + 1].x = x[i], a[i + 1].y = y[i], a[i + 1].r = r[i];
            CL(f, 0);
            sort(a + 1, a + n + 1);
            REP(i, 1, n) ch[i].clear();
            REP(i, 1, n) REP(j, i + 1, n) if (inside(i, j))  { //把圆组成的树给构出来
                f[i] = j;
                ch[j].PB(i);
                break;
            }
            int sg = 0;
            REP(i, 1, n) if (!f[i]) {
                sg ^= dp(i);//把所有树的根节点的SG值异或起来
            }
            if (sg) return "Alice";
            else return "Bob";
		}
};

// CUT begin
ifstream data("CirclesGame.sample");

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

bool do_test(vector<int> x, vector<int> y, vector<int> r, string __expected) {
    time_t startClock = clock();
    CirclesGame *instance = new CirclesGame();
    string __result = instance->whoCanWin(x, y, r);
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
        vector<int> x;
        from_stream(x);
        vector<int> y;
        from_stream(y);
        vector<int> r;
        from_stream(r);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(x, y, r, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1476759273;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 550 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "CirclesGame (550 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
