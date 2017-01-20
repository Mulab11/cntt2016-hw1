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
class ZKW { //ZKW费用流板子
    public:
#define INF 1000000000
#define MAXN 100000
#define MAXM 100000
        struct edge_node
        {
            int p,next;
            int w,c;
        }edge[MAXM];
        int vis[MAXN],instack[MAXN];
        int head[MAXN],slk[MAXN];
        int d[MAXN];
        int cur[MAXM];
        int cnt,S,T,index,tot;
        LL ans,flow;
        void ae(int a,int b,int weight,int cost)
        {
            edge[++cnt].p=b; edge[cnt].w=weight;
            edge[cnt].c=cost; edge[cnt].next=head[a]; head[a]=cnt;
            edge[++cnt].p=a; edge[cnt].w=0;
            edge[cnt].c=-cost; edge[cnt].next=head[b]; head[b]=cnt;
        }
        int aug(int u,int now)
        {
            if (u==T)
            {
                ans+=(LL)now*d[T];
                flow+=now;
                return now;
            }
            int res=0,tmp;
            vis[u]=instack[u]=index;
            for (int &k=cur[u];k;k=edge[k].next)
            {
                int v=edge[k].p;
                int t=d[u]+edge[k].c-d[v];
                if (edge[k].w)
                {
                    slk[v]=min(slk[v],t);
                    if (!t&&instack[v]!=index)
                    {
                        tmp=aug(v,min(now,edge[k].w));
                        res+=tmp;
                        edge[k].w-=tmp;
                        edge[k^1].w+=tmp;
                        if ((now-=tmp)==0) break;
                    }
                }
            }
            instack[u]=false;
            return res;
        }
        bool modlabel()
        {
            int del=INF;
            for (int i=1;i<=T;++i) if (vis[i]!=index)
                del=min(del,slk[i]);
            if (del==INF) return false;
            for (int i=1;i<=T;++i) if (vis[i]!=index)
                d[i]+=del;
            return true;
        }
        LL MCMF(int _S, int _T, int returnflow = 0)
        {
            S = _S, T = _T;
            flow=ans=0;
            for (int i=1;i<=T;++i) d[i]=0;
            do
                do{
                    for (int i=1;i<=T;++i) slk[i]=INF,cur[i]=head[i];
                    ++index;
                }
                while (aug(S,INF));while (modlabel());
            if (returnflow) return flow;
            return ans;
        }
        void init(int n) {
            index = cnt = 1;
            REP(i, 1, n + 2) head[i] = 0, vis[i] = -1;
        }
}solver;

const int N = 53;
int n;
struct node {
    int p, next;
    bool flag;
}edge[N * 2];
int head[N], cnt;
void ae(int a, int b) {
    edge[++cnt].p = b;
    edge[cnt].next = head[a];
    head[a] = cnt;
    edge[cnt].flag = 1;
}

int f[N][N][N][N];

vector<int> X, Y;

void dfs(vector<int> &V, int u, int fa) {
    V.PB(u);
    RED(k, u) if (edge[k].flag){
        int v = edge[k].p;
        if (v != fa) dfs(V, v, u);
    }
}

int dp(int a, int fa, int b, int fb) { //记忆化搜索
    if (f[a][fa][b][fb] != -1) return f[a][fa][b][fb];
    vector<int> X, Y;
    RED(k, a) if (edge[k].flag && edge[k].p != fa)
        X.PB(edge[k].p);
    RED(k, b) if (edge[k].flag && edge[k].p != fb)
        Y.PB(edge[k].p);


    for (int i = 0; i < X.size(); ++ i) 
        for (int j = 0; j < Y.size(); ++j) dp(X[i], a, Y[j], b);


    solver.init(X.size() + Y.size()); //费用流初始化
    int S = X.size() + Y.size() + 1, T = S + 1;

    for (int i = 0; i < X.size(); ++ i) solver.ae(S, i + 1, 1, 0);  //最大权匹配
    for (int i = 0; i < Y.size(); ++ i) solver.ae(i + 1 + X.size(), T, 1, 0);

    for (int i = 0; i < X.size(); ++ i) 
        for (int j = 0; j < Y.size(); ++j) {
            solver.ae(i + 1, j + X.size() + 1, 1, -f[X[i]][a][Y[j]][b]);
        }

    f[a][fa][b][fb] = -solver.MCMF(S, T) + 1; //最大费用流
    return f[a][fa][b][fb];
}

int solve(int a, int b) { 
    CL(f, 0xff);
    X.clear(); Y.clear();
    dfs(X, a, 0);
    dfs(Y, b, 0);
    int ans = 0;
    REP(i, 0, X.size() - 1) 
        REP(j, 0, Y.size() - 1) { //枚举两边树的根
            getmax(&ans, dp(X[i], 0, Y[j], 0));
        }
    return ans;
}

class DeerInZooDivOne {
	public:
		int getmax(vector<int> a, vector<int> b) {
            n = a.size() + 1;
            cnt = 1;
            CL(head, 0);
            REP(i, 0, a.size() - 1) ae(a[i] + 1, b[i] + 1), ae(b[i] + 1, a[i] + 1); //连边
            int ans = 0;
            REP(i, 1, n) RED(k, i) { //枚举断掉的边
                int j = edge[k].p;
                if (i > j) continue;
                edge[k].flag = 0;
                edge[k ^ 1].flag = 0;
                ans = max(ans,  solve(i, j)); 
                edge[k].flag = 1;
                edge[k ^ 1].flag = 1;
            }
			return ans;
		}
};

// CUT begin
ifstream data("DeerInZooDivOne.sample");

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

bool do_test(vector<int> a, vector<int> b, int __expected) {
    time_t startClock = clock();
    DeerInZooDivOne *instance = new DeerInZooDivOne();
    int __result = instance->getmax(a, b);
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
        vector<int> a;
        from_stream(a);
        vector<int> b;
        from_stream(b);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(a, b, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1477272969;
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
        cout << "DeerInZooDivOne (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
