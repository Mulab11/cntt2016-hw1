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

const int mo = 1000000009;
template<class T>
T pow(T a, T b, int c = mo) {
	T res = 1;
	for (T i = 1; i <= b; i <<= 1, a = 1LL * a * a % c) if (b & i) res = 1LL * res * a % c;
	return res;
}

/*======================= TEMPLATE =======================*/
const int N = 100;
int s[N][N];
struct node {
    int p, next;
}edge[N];
int head[N], cnt, n;
void ae(int a, int b) {
    edge[++cnt].p = b;
    edge[cnt].next = head[a];
    head[a] = cnt;
}
int f[N][N][N], c[N][N];

void dfs(int u, int fa) {
    s[u][fa] = 1;
    RED(k, u) {
        int v = edge[k].p;
        if (v != fa) {
            dfs(v, u);
            s[u][fa] += s[v][u];
        }
    }
}

int s1, s2, fa1, fa2, len;
 
void move(int u, int fa, int step, int k)
{
    if (step == len) {
        if (s[u][fa] == k) s2 = u, fa2 = fa;
        return;
    }
    RED(kk, u) {
        int v = edge[kk].p;
        if (v != fa) move(v, u, step + 1, k);
    }
}

void find(int k)
{
    len = n - 2 * k + 1, s1 = s2 = -1;
    REP(i, 1, n) {
        RED(kk, i) {
            int j = edge[kk].p;
            if (s[j][i] == k) {
                s1 = j, fa1 = i, s2 = fa2 = -1;
                move(i, j, 1, k);
                if (s2 != -1) break;
            }
        }
        if (s2 != -1) break;
    }
}

int g[N];

void dp1(int u, int fa) {
    int r = s[u][fa] - 1;
    g[u] = 1;
    RED(k, u) {
        int v = edge[k].p;
        if (v == fa) continue;
        dp1(v, u);
        g[u] = 1LL * g[u] * g[v] % mo 
            * c[r][s[v][u]] % mo;
        r -= s[v][u];
    }
}

int solve1(int k) {
    find(k);
    if (s1 == -1 || s2 == -1) return 0;
    dp1(s1, fa1);
    dp1(s2, fa2);
    return 2LL * g[s1] * g[s2] % mo;

}

int all, res;

int r[N][N];

void dp(int u, int fa) {
    int now = 1, tmp;
    f[u][0][0] = f[u][0][1] = f[u][1][0]
        = 1;
    RED(k, u) {
        int v = edge[k].p;
        if (v == fa) continue;
        dp(v, u);
        tmp = s[v][u];
        now += tmp;
        memcpy(r, f[u], sizeof r);
        CL(f[u], 0);
        f[u][now][0] = 1LL * r[now - tmp][0]
            * f[v][tmp][0] % mo 
            * c[now - 1][tmp] % mo;
        
        f[u][0][now] = 1LL * r[0][now - tmp]
            * f[v][0][tmp] % mo 
            * c[now - 1][tmp] % mo;

        for (int a = 0; a < now; a++) {
            for (int b = 0; a + b < now; b++) {
                for (int p = 0; p <= a && p <= tmp; p++) {
                    int &to = f[u][a][b];
                    for (int q = 0; q <= b && p + q <= tmp; q++) {
                        if (now - a - b >= tmp - p - q) {
                            if (now - a - b > 0 && tmp - p - q == now - a - b) continue;
                            to = (to + 1ll * r[a - p][b - q] * f[v][p][q] % mo * c[a][p] % mo * c[b][q] % mo) % mo;
                        }
                    }
                }
            }
        }

    }
}

int solve2(int k) {
    int ans = 0;
    all = 2 * k - n, res = n - all;
    CL(f, 0);
    REP(i, 1, n) {
        dp(i, 0);
        ans = (ans + f[i][res/2][res/2])
            % mo;
    }
    REP(i, 1, all - 1) ans = 1LL * ans * i 
        % mo;
    return ans;
}


class InducedSubgraphs {
	public:
		int getCount(vector<int> edge1, vector<int> edge2, int k) {
            CL(s, 0);
            REP(i, 0, 50) {
                c[i][i] = c[i][0] = 1;
                REP(j, 1, i - 1) c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mo;
            }
            CL(head, 0); cnt = 0;
            n = edge1.size() + 1;
            if (k == n || k == 1) {
                int ans = 1;
                REP(i, 1, n) ans = 1LL * ans * i % mo;
                return ans;
            }
            REP(i, 0, n - 2) ae(edge1[i] + 1, edge2[i] + 1), ae(edge2[i] + 1, edge1[i] + 1);
            REP(i, 1, n) dfs(i, 0);
            if (2 * k <= n) return solve1(k);
            else return solve2(k);
		}
};

// CUT begin
ifstream data("InducedSubgraphs.sample");

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

bool do_test(vector<int> edge1, vector<int> edge2, int k, int __expected) {
    time_t startClock = clock();
    InducedSubgraphs *instance = new InducedSubgraphs();
    int __result = instance->getCount(edge1, edge2, k);
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
        vector<int> edge1;
        from_stream(edge1);
        vector<int> edge2;
        from_stream(edge2);
        int k;
        from_stream(k);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(edge1, edge2, k, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1478599161;
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
        cout << "InducedSubgraphs (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
