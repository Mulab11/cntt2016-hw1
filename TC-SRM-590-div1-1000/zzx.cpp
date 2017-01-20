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
const int N = 1000000;
struct node {
    int p, next,w;
}edge[N];
int head[N], h[N], cnt = 1, cur[N];
void ae(int a, int b, int c)
{
    edge[++cnt].p = b;
    edge[cnt].next = head[a];
    edge[cnt].w = c;
    head[a] = cnt;
    edge[++cnt].next = head[b];
    edge[cnt].w = 0;
    edge[cnt].p = a;
    head[b] = cnt;
}
queue<int> q;
int s, t, n, r[N];
bool bfs()
{
    while (!q.empty()) q.pop();
    REP(i, 1, t) cur[i] = head[i], h[i] = -1;
    h[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        RED(k, u) {
            int v = edge[k].p;
            if (h[v] == -1 && edge[k].w) {
                h[v] = h[u] + 1;
                if (v == t) return true;
                q.push(v);
            }
        }
    }
    return false;
}
const int inf = 1e9;
int dfs(int u, int now)
{
    if (u == t) return now;
    int tmp, res = 0;
    for (int &k = cur[u]; k; k = edge[k].next) {
        int v = edge[k].p;
        if (h[v] == h[u] + 1 && edge[k].w) {
            tmp = dfs(v, min(now, edge[k].w));
            res += tmp;
            edge[k].w -= tmp;
            edge[k ^ 1].w += tmp;
            if (!(now -= tmp)) break;
        }
    }
    if (!res) h[u] = -1;
    return res;
}
int dinic() //dinic计算最小割
{
    int ans = 0;
    while (bfs()) ans += dfs(s, inf);
    return ans;
}
int calc(int i, int x)
{
    int t = (r[i] - x) * (r[i] - x);
    return t;
}
int id[100][100];
int e[100][100];
int solve() //最小割模型
{
    cnt = 1; CL(head, 0);
    int tot = 0;
    s = n * (n - 1) + 1, t = s + 1;
    REP(i, 1, n) {
        id[i][1] = ++tot;
        if (i == 1) ae(s, id[i][1] ,calc(i, 0));
        else ae(s, id[i][1], inf);
        REP(j, 2, n - 1) {
            id[i][j] = ++tot;
            if (i != 1) ae(id[i][j - 1],tot, calc(i, j - 1)); //把每个点都拆成n - 1个点 第x条边的权就是i距离为x的时候的不开心值
            else ae(id[i][j - 1], tot, inf);
        }
        if (i == 1) ae(tot, t, inf);
        else ae(tot, t, calc(i, n - 1));
    }
    REP(x, 1, n) 
        REP(y, x + 1, n) if (e[x][y]) {
            REP(i, 2, n - 1) ae(id[x][i], id[y][i - 1], inf);//如果两个点之间有边那么要满足三角形不等式
            swap(x, y);
            REP(i, 2, n - 1) ae(id[x][i], id[y][i - 1], inf);
            swap(x, y);
        }
    return dinic();
}
class FoxAndCity {
    public:
        int minimalCost(vector<string> linked, vector<int> want) {
            n = want.size();
            CL(e, 0);
            REP(i, 1, n) r[i] = want[i - 1];
            REP(i, 1, n) REP(j, 1, n) if (linked[i - 1][j - 1] == 'Y') { 
                e[i][j] = 1;
            }
            return solve();
        }
};

// CUT begin
ifstream data("FoxAndCity.sample");

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

bool do_test(vector<string> linked, vector<int> want, int __expected) {
    time_t startClock = clock();
    FoxAndCity *instance = new FoxAndCity();
    int __result = instance->minimalCost(linked, want);
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
        vector<string> linked;
        from_stream(linked);
        vector<int> want;
        from_stream(want);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(linked, want, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1478089566;
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
        cout << "FoxAndCity (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
