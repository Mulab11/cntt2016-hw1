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
int id[N][N];
int n, m;
class ZKW { //网络流板子 
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
        int cnt,S,T,m,index,tot;
        LL ans,flow;
        void ae(int a,int b,int weight,int cost = 0)
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
        pair<LL, LL> MCMF(int _S, int _T)
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
            return MP(ans, flow);
        }
        void init(int n) {
            cnt = 1;
            REP(i, 1, n + 2) head[i] = 0;
        }
}solver;
class BoardPainting {
	public:
		int minimalSteps(vector<string> target) {
            CL(a, 0);
            n = target.size(); m = target[0].size();
            int tot = 0;
            REP(i, 0, n - 1) REP(j, 0, m - 1) {
                a[i][j] = (target[i][j] == '#');
                if (a[i][j]) id[i][j] = ++tot;
            }
            int S = tot + 1, T = tot + 2;
            solver.init(tot);
            
            REP(i, 0, n - 1) REP(j, 0, m - 1) if (a[i][j]) {
                int hor = 0;
                if(!a[i][j - 1]) hor++;
                if(!a[i][j + 1]) hor++;
                solver.ae(S, id[i][j], hor); // S集是vertical的 如果(i, j)的左右有边界那么就要加上这个权

                int ver = 0;
                if(!a[i - 1][j]) ver++; //T集是horizonal的 如果(i, j)的上下有边界那么就要加上权
                if(!a[i + 1][j]) ver++;

                solver.ae(id[i][j], T, ver);

                if(a[i + 1][j]) solver.ae(id[i][j], id[i+1][j], 1), solver.ae(id[i + 1][j], id[i][j], 1); //如果相邻的两个不在同一个割集里面就要加上相应的权
                if(a[i][j + 1]) solver.ae(id[i][j], id[i][j+1], 1), solver.ae(id[i][j + 1], id[i][j], 1);
            }
			return solver.MCMF(S, T).SC / 2;
		}
};

// CUT begin
ifstream data("BoardPainting.sample");

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

bool do_test(vector<string> target, int __expected) {
    time_t startClock = clock();
    BoardPainting *instance = new BoardPainting();
    int __result = instance->minimalSteps(target);
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
        vector<string> target;
        from_stream(target);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(target, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1479368230;
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
        cout << "BoardPainting (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
