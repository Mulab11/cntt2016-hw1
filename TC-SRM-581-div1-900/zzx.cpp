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
const int N = 14;
int n, m, a[N], c[N];
int ans;
int all; //all 表示每一列的操作种类
void trans(int &a, int b, int c) {//将a这个状态应用c这个操作 操作的位置为b
    a = a ^ (b << 1) ^ (b >> 1);
    if (c) a ^= b;
    a &= ((1 << m) - 1);
}
int subset(int a) { //判断a是否是all或all的补集的子集
    if ((a & all) == a) return 0;
    if ((a ^ all) == (a | all)) return 1;
    return -1;
}
void solve(int s, int flag) { //模拟当第一行进行的操作种类为flag 操作位置为s的情况下 整个棋盘的操作情况
    int num = __builtin_popcount(s);
    if (num >= ans) return;
    REP(i, 0, n - 1) c[i] = a[i];
    trans(c[0], s, flag);
    c[1] ^= s;
    REP(i, 1, n - 1) {
        num += __builtin_popcount(c[i - 1]);
        if (num >= ans) return;
        int tp = subset(c[i - 1]);
        if (tp == -1) return;
        if (i != n - 1)
            c[i + 1] ^= c[i - 1];
        trans(c[i], c[i - 1], tp);
    }
    if (!c[n - 1]) {
        ans = num;
    }
}
void check(int s) {//枚举当列的操作种类为s的时候 第一行的操作 因为第一行的操作一旦确定 后面的操作也确定了
    all = s;
    for (int t = s; ; t = (t - 1) & s) {
        solve(t, 0);
        if (!t) break;
    }
    s ^= ((1 << m) - 1);
    for (int t = s; t; t = (t - 1) & s) {
        solve(t, 1);
    }
}
class YetAnotherBoardGame {
	public:
		int minimumMoves(vector<string> board) {
            ans = 1000;
            n = board.size(); m = board[0].size();
            REP(i, 0, n - 1) {
                a[i] = 0;
                REP(j, 0, m - 1) if (board[i][j] == 'W') a[i] |= (1 << j);
            }
            REP(i, 0, (1 << m) - 1) check(i); //枚举每一列的操作情况
            if (ans == 1000) ans = -1;
			return ans;
		}
};

// CUT begin
ifstream data("YetAnotherBoardGame.sample");

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
    YetAnotherBoardGame *instance = new YetAnotherBoardGame();
    int __result = instance->minimumMoves(board);
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
        int T = time(NULL) - 1479281849;
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
        cout << "YetAnotherBoardGame (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
