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
const int N = 53;
int n, m;
int a[N], id[N][N], f[N * N], sl[N], sr[N]; //sl sr说明一行左右可能的连接方向 0说明不连 1说明一定要往上连 2说明可以往下连
char G[N][N];
bool cross[N];
int get(int u) {//并查集处理连通块
    if (u == f[u]) return u;
    return f[u] = get(f[u]);
}
void join(int u, int v) {
    f[get(u)] = get(v);
}
int pd(int x, int y) {
    return x <= n && x  && y <= m && y && G[x][y] == 'X';
}
int deg(int i, int j) { //计算一个点的度 用来判断一个点是否在拐角上.. 
    int ans = 0;
    if (pd(i + 1, j)) ++ans;
    if (pd(i - 1, j)) ++ans;
    if (pd(i, j - 1)) ++ans;
    if (pd(i, j + 1)) ++ans;
    return ans;
}
bool up(int a, int b) { //判断一个括号序列的前缀和a能否通过一个右括号转移到b
    if (a == 0) return (b == 0);
    return b == a - 1;
}
bool down(int a, int b) { //判断一个括号序列的前缀和b能否通过一个左括号转移到b
    return b == a + 1 || a == b;
}
bool same(int a, int b) {//判断两个数是否相同
    return a == b;
}
bool check(int r, int j1, int k1, int j2, int k2) { //判断左右括号序列前缀和分别为j1 k1 能否在第r行转移到j2 k2
    if (cross[r])   //如果一行是xxxxxxxxxxxxxxxxxxxxxx就特殊处理
        return (up(j1, j2) && down(k1, k2)) || (up(k1, k2) && down(j1, j2));
    bool L = 1, R = 1;
    if (!sl[r]) L = same(j1, j2); if (sl[r] == 1) L = up(j1, j2); if (sl[r] == 2) L = down(j1, j2); 
    if (!sr[r]) R = same(k1, k2); if (sr[r] == 1) R = up(k1, k2); if (sr[r] == 2) R = down(k1, k2);
    return L && R;
}
int dp() { //dp计算最多能合并多少个连通块
    static int f[N][N][N];
    CL(f, 0xff);
    f[0][0][0] = 0;
    REP(i, 1, n)
        REP(j, 0, n) 
            REP(k, 0, n) if (f[i - 1][j][k] != -1) {
                    REP(k1, j - 1, j + 1) if (k1 >= 0)
                        REP(k2, k - 1, k + 1) if (k2 >= 0) {
                            int d = max(j - k1, 0) + max(k - k2, 0); //合并的连通块数目
                            if (check(i, j, k, k1, k2)) getmax(&f[i][k1][k2], f[i - 1][j][k] + d);
                        }
                }
    int ans = 0;
    REP(i, 0, n)
        REP(j, 0, n) getmax(&ans, f[n][i][j]);
    return ans;
}
class Tunnels {
	public:
		int minimumTunnels(vector<string> frame) {
            n = frame.size(); m = frame[0].size();
            int tot = 0;
            CL(G, 0);
            REP(i, 0, n - 1) REP(j, 0, m - 1) if (frame[i][j] == 'X') 
                id[i + 1][j + 1] = ++tot, G[i + 1][j + 1] = frame[i][j];
            if (m == 1) return (bool)tot;
            CL(cross, 0); CL(sl, 0); CL(sr, 0);
            REP(i, 1, tot) f[i] = i;
            REP(i, 1, n) REP(j, 1, m) if (G[i][j] == 'X') {
                if (pd(i + 1, j)) join(id[i][j], id[i + 1][j]);
                if (pd(i - 1, j)) join(id[i][j], id[i - 1][j]);
                if (pd(i, j - 1)) join(id[i][j], id[i][j - 1]);
                if (pd(i, j + 1)) join(id[i][j], id[i][j + 1]);
            }
            int num = 0;
            REP(i, 1, n) REP(j, 1, m) if (G[i][j] == 'X' && id[i][j] == f[id[i][j]]) {
                ++num;
                int high = i, low = i, lh = -1, ll = n + 1, rh = -1, rl = n + 1;
                REP(i1, 1, n) REP(j1, 1, m) if (G[i1][j1] == 'X' && get(id[i1][j1]) == id[i][j]) {
                    getmax(&high, i1), getmin(&low, i1);
                    if (j1 == 1) getmax(&lh, i1), getmin(&ll, i1);
                    if (j1 == m) getmax(&rh, i1), getmin(&rl, i1);
                }
                if (ll == low && ll != 1 && deg(ll, 1) <= 1) sl[ll] = 1; //判断左边是否一定要往上连
                if ((!sl[lh]) && lh == high && deg(lh, 1) <= 1) sl[lh] = 2; //判断左边是否可以往下连
                if (lh == ll + 1 && ll != 1 && sl[ll]) sl[lh] = 0; //如果最上面和最下面相邻，就不能同时往上和往下
                if (rl == low && rl != 1 && deg(rl, m) <= 1) sr[rl] = 1;
                if ((!sr[rh]) && rh == high && deg(rh, m) <= 1) sr[rh] = 2;
                if (rh == rl + 1 && rl != 1 && sr[rl]) sr[rh] = 0;
                if (low == high && lh != -1 && rh != -1) cross[low] = 1;//记录哪些行是被x全部填满且上下都是空的
            }
			return num - dp();
		}
};

// CUT begin
ifstream data("Tunnels.sample");

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

bool do_test(vector<string> frame, int __expected) {
    time_t startClock = clock();
    Tunnels *instance = new Tunnels();
    int __result = instance->minimumTunnels(frame);
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
        vector<string> frame;
        from_stream(frame);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(frame, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1479108921;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 1050 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "Tunnels (1050 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
