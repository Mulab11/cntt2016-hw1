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
/*
 * 这就是一个结论题 
 * Bob获胜的条件是 存在一个点C使得它到B的距离比到A的距离起码大2且C存在至少3个分支的深度不小于3
 * 这个结论感觉还是不那么难想的
 * 可以猜一下然后试一下就好了
 *
 */
const int N = 60;
const int dx[] = {-1, 0, 1, 0}; //记录不同的4个方向
const int dy[] = {0, -1, 0, 1};
int n, m;
char a[N][N];
int Dis[N][N];
int da[N][N], db[N][N];
bool pd(int x, int y) {//判断一个点是否合法
    return x >= 0 && x < n && y < m && y >= 0 && a[x][y] != '#';
}

int dfs(int i, int j, int k) {//dfs记录一个点出发到其他所有点的距离以及最大的深度
    Dis[i][j] = k;
    int mx = k;
    REP(q, 0, 3) {
        int x = i + dx[q], y = j + dy[q];
        if (pd(x, y) && Dis[x][y] == -1)
            getmax(&mx, dfs(x, y, k + 1));
    }
    return mx;
}

class GameInDarknessDiv1 {
    public:
        string check(vector<string> field) {
            n = field.size();
            m = field[0].size();
            CL(Dis, 0xff);
            REP(i, 0, n - 1) REP(j, 0, m - 1) a[i][j] = field[i][j];
            REP(i, 0, n - 1) REP(j, 0, m - 1) if (a[i][j] == 'A') dfs(i, j, 0);//A到其他所有点的距离
            REP(i, 0, n - 1) REP(j, 0, m - 1) da[i][j] = Dis[i][j], Dis[i][j] = -1;//B到其他所有点的距离
            REP(i, 0, n - 1) REP(j, 0, m - 1) if (a[i][j] == 'B') dfs(i, j, 0);
            REP(i, 0, n - 1) REP(j, 0, m - 1) db[i][j] = Dis[i][j], Dis[i][j] = -1;
            REP(i, 0, n - 1) REP(j, 0, m - 1)//枚举中间点C
                if (a[i][j] != '#' && da[i][j] > db[i][j] + 1) {
                    char tmp = a[i][j];
                    a[i][j] = '#';
                    REP(k1, 0, n - 1)
                        REP(k2, 0, m - 1)
                            Dis[k1][k2] = -1;
                    int cnt = 0;
                    REP(q, 0, 3) {
                        int x = i + dx[q], y = j + dy[q];
                        if (pd(x, y) && dfs(x, y, 1) >= 3) ++cnt; //检查看看深度不小于3的分支是否有至少3个
                    }
                    if (cnt >= 3) return "Bob wins";
                    a[i][j] = tmp;
                }
            return "Alice wins";
        }
};

// CUT begin
ifstream data("GameInDarknessDiv1.sample");

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

bool do_test(vector<string> field, string __expected) {
    time_t startClock = clock();
    GameInDarknessDiv1 *instance = new GameInDarknessDiv1();
    string __result = instance->check(field);
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
        vector<string> field;
        from_stream(field);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(field, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1483345377;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 1100 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "GameInDarknessDiv1 (1100 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
