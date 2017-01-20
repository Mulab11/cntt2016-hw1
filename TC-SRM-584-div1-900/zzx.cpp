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
int n;
int id[10][10], S;
struct DMST{
#define N 100000
#define INF 100000000
    int n, m, cnt;
    struct node {
        int u, v, w;
    }edge[N];
    int In[N], pre[N];
    int vis[N], id[N];
    void init(int _n) {
        m = 0;
        n = _n;
    }
    void ae(int a, int b, int c) {
        edge[++m].u = a; edge[m].v = b; edge[m].w = c;
    }
    int solve(int root) {
        int res=0;
        while (1)
        {
            for (int i=1;i<=n;++i) In[i]=INF;
            for (int i=1;i<=m;++i)
            {
                int u=edge[i].u,v=edge[i].v;
                if (u!=v&&edge[i].w<In[v])
                    In[v]=edge[i].w,pre[v]=u;
            }
            for (int i=1;i<=n;++i) if (i!=root&&In[i]==INF) return -1;
            In[root]=0;
            for (int i = 0; i <= n; ++i) id[i] = vis[i] = -1;
            cnt=0;
            for (int i=1;i<=n;++i)
            {
                res+=In[i];
                int u=i;
                while (vis[u]!=i&&id[u]==-1&&u!=root)
                    vis[u]=i,u=pre[u];
                if (id[u]==-1&&u!=root)
                {
                    ++cnt;
                    for (int v=pre[u];v!=u;v=pre[v])
                        id[v]=cnt;
                    id[u]=cnt;
                }
            }
            if (cnt==0) break;
            for (int i=1;i<=n;++i) if (id[i]==-1) id[i]=++cnt;
            for (int i=1;i<=m;++i)
            {
                int u=edge[i].u,v=edge[i].v;
                edge[i].u=id[u]; edge[i].v=id[v];
                if (id[u]!=id[v]) edge[i].w-=In[v];
            }
            root=id[root]; //Important
            n=cnt; //Important
        }
        return res;
    }
}solver; //最小树形图

int val(string s) {
    return 1000 * (s[0] - '0') + 100 * (s[1] - '0') + 10 * (s[2] - '0') + s[3] - '0';
}

class FoxTheLinguist {
	public:
		int minimalHours(int n, vector<string> courseInfo) {
            int tot = 0;
            REP(i, 0, n - 1) REP(j, 0, 9) id[i][j] = ++tot;
            S = tot + 1;
            solver.init(S);
            REP(i, 0, n - 1) solver.ae(S, id[i][0],0); //根向每种语言的0级连代价为0的边
            REP(i, 0, n - 1) REP(j, 1, 9) solver.ae(id[i][j], id[i][j - 1], 0);//每种语言高级向低级连0边
            REP(i, 1, courseInfo.size() - 1) courseInfo[0] += courseInfo[i];
            stringstream fin;
            fin << courseInfo[0];
            string s;
            while (fin >> s) {
                cerr << s << endl;
                int x = s[0] - 'A', y = s[4] - 'A';
                int a = s[1] - '0', b = s[5] - '0';
                int c = val(s.substr(7, 4));
                solver.ae(id[x][a], id[y][b], c); //可以学习的连边
            }
			return solver.solve(S);
		}
};

// CUT begin
ifstream data("FoxTheLinguist.sample");

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

bool do_test(int n, vector<string> courseInfo, int __expected) {
    time_t startClock = clock();
    FoxTheLinguist *instance = new FoxTheLinguist();
    int __result = instance->minimalHours(n, courseInfo);
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
        int n;
        from_stream(n);
        vector<string> courseInfo;
        from_stream(courseInfo);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, courseInfo, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1478741361;
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
        cout << "FoxTheLinguist (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
