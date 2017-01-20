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
int n, m; // 地图大小
int num; // Check Point 个数
int cp[N]; // 记录所有的Check Point
int id[51][51]; // 每个点的编号
char G[51][51]; //储存地图 . * #
int d[N][N]; //计算两点之间的最短路
double c1[N]; //C(i, K) / C(num, K)
double c2[N]; //C(i, K - 2) / C(num - 2, K - 2)

bool pd(int x, int y) { //判断(x,y)是否是合法的格子
    return x < n && y < m && x >= 0 && y >= 0 && G[x][y] != '#';
}

void dfs(int x, int y, int *f, int d) { //计算从(x, y)出发到每个点的最短路
    f[id[x][y]] = d;
    if (pd(x + 1, y) && f[id[x + 1][y]] == -1) dfs(x + 1, y, f, d + 1);
    if (pd(x - 1, y) && f[id[x - 1][y]] == -1) dfs(x - 1, y, f, d + 1);
    if (pd(x, y + 1) && f[id[x][y + 1]] == -1) dfs(x, y + 1, f, d + 1);
    if (pd(x, y - 1) && f[id[x][y - 1]] == -1) dfs(x, y - 1, f, d + 1);
}

bool check(int i, int j, int k) { //计算加入点k是否会影响直径i j的合法性
    int da = d[cp[i]][cp[j]], db = d[cp[i]][cp[k]], dc = d[cp[k]][cp[j]];
    return (da > db || (da == db && k > j)) && (da > dc || (da == dc && k > i));
}

class Orienteering {
	public:
		double expectedLength(vector<string> field, int K) {
            CL(d, 0xff);
            n = field.size(); m = field[0].size();
            num = 0;
            int tot = 0;
            REP(i, 0, n - 1) 
                REP(j, 0, m - 1) {
                    id[i][j] = ++tot;
                    G[i][j] = field[i][j];
                    if (G[i][j] == '*') cp[++num] = tot;
                }

            c1[num] = 1;
            PER(i, num - 1, 0) c1[i] = c1[i + 1] / (i + 1) * (i + 1 - K); // 计算系数1

            c2[num - 2] = 1;
            PER(i, num - 3, 0) c2[i] = c2[i + 1] / (i + 1) * (i - K + 3); // 计算系数2

            REP(i, 0, n - 1) REP(j, 0, m - 1) dfs(i, j, d[id[i][j]], 0);

            double ans = 0;

            REP(i, 1, tot - 1) 
                REP(j, i + 1, tot) if (d[i][j] == 1) {  //枚举每条树边
                    int x = 0; // 在一侧的Check Point个数
                    REP(k, 1, num) if (d[i][cp[k]] <= d[j][cp[k]]) ++x;
                    ans += 2.0 * (1.0 - c1[x] - c1[num - x]);
                }

            REP(i, 1, num - 1) 
                REP(j, i + 1, num) { //枚举 cp[i], cp[j] 作为直径
                    int x = 0; // 符合条件的k的个数
                    int dia = d[cp[i]][cp[j]]; //直径长度
                    REP(k, 1, num) if (check(i, j, k)) ++x;
                    ans -= c2[x] * dia * K * (K - 1) / num / (num - 1);
                }

			return ans;
		}
};

// CUT begin
ifstream data("Orienteering.sample");

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

bool double_equal(const double &a, const double &b) { return b==b && a==a && fabs(b - a) <= 1e-9 * max(1.0, fabs(a) ); }

bool do_test(vector<string> field, int K, double __expected) {
    time_t startClock = clock();
    Orienteering *instance = new Orienteering();
    double __result = instance->expectedLength(field, K);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (double_equal(__expected, __result)) {
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
        int K;
        from_stream(K);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(field, K, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1476761561;
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
        cout << "Orienteering (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
