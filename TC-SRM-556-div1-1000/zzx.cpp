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
 * CQOI 2014危桥
 * 假设第一次跑网络流a1到a2流an−x，a1到b2流x，b1到b2流bn−x，b1到a2流x 
 * 在交换之后，由于是无向图，a1到a2依然能流an−x，b2到b1也依然能流bn−x。
 * 此时由于还是满流的，那么a1到b1流x，b2到a2流x。
 * 把两次综合起来看，第一次a1到b2流x，第二次a1到b1流x
 */
#define inf 0x3f3f3f3f
char S[55][55];
int d[55],v[55],cur[55],tot,s,t,h[55],n;
struct edge
{
    int from,to,cap,flow,ne;
}E[100005];
void Addedge(int from,int to,int cap) // add edges
{
    E[++tot]=(edge){from,to,cap,0,h[from]};
    h[from]=tot;
    E[++tot]=(edge){to,from,0,0,h[to]};
    h[to]=tot;
}
void Build()
{
    tot=1;
    for (int i=s;i<=t;i++)
        h[i]=0;
    for (int i=1;i<=n;i++)
        for (int j=0;j<n;j++)
        {
            if (S[i][j]=='O') Addedge(i,j+1,2);
            if (S[i][j]=='N') Addedge(i,j+1,inf);
        }
}
bool bfs()
{
    for (int i=s;i<=t;i++)
        v[i]=0;
    queue<int> q;
    q.push(s);
    v[s]=1;
    d[s]=0;
    while (!q.empty())
    {
        int x=q.front();
        q.pop();
        for (int i=h[x];i;i=E[i].ne)
        {
            edge e=E[i];
            if (!v[e.to]&&e.cap>e.flow)
            {
                v[e.to]=1;
                d[e.to]=d[x]+1;
                q.push(e.to);
            }
        }
    }
    return v[t];
}
int dfs(int x,int a)
{
    if (x==t||!a) return a;
    int flow=0;
    for (int &i=cur[x];i;i=E[i].ne)
    {
        edge &e=E[i];
        if (d[e.to]!=d[x]+1) continue;
        int f=dfs(e.to,min(a,e.cap-e.flow));
        if (f>0)
        {
            e.flow+=f;
            E[i^1].flow-=f;
            flow+=f;
            a-=f;
            if (!a) break;
        }
    }
    return flow;
}
int dinic() //dinic algorithm
{
    int flow=0;
    while (bfs())
    {
        for (int i=s;i<=t;i++)
            cur[i]=h[i];
        flow+=dfs(s,inf);
    }
    return flow;
}

class OldBridges {
    public:
        string isPossible(vector<string> bridges, int a1, int a2, int an, int b1, int b2, int bn) {
            n = bridges.size();
            s=0,t=n+1;
            REP(i, 1, n) REP(j, 0, n - 1) S[i][j] = bridges[i - 1][j];
            an*=2,bn*=2;
            a1++,a2++,b1++,b2++;
            Build();
            Addedge(s,a1,an),Addedge(a2,t,an);
            Addedge(s,b1,bn),Addedge(b2,t,bn); // first flow (A1, B1) -> (A2, B2)
            if (dinic()==an+bn) {
                Build();
                Addedge(s,a1,an),Addedge(a2,t,an);
                Addedge(s,b2,bn),Addedge(b1,t,bn);//flow (A1, B2)  -> (B1, A2)
                if (dinic()==an+bn) return "Yes";
                else return "No";
            }
            return "No";
        }
};

// CUT begin
ifstream data("OldBridges.sample");

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

bool do_test(vector<string> bridges, int a1, int a2, int an, int b1, int b2, int bn, string __expected) {
    time_t startClock = clock();
    OldBridges *instance = new OldBridges();
    string __result = instance->isPossible(bridges, a1, a2, an, b1, b2, bn);
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
        vector<string> bridges;
        from_stream(bridges);
        int a1;
        from_stream(a1);
        int a2;
        from_stream(a2);
        int an;
        from_stream(an);
        int b1;
        from_stream(b1);
        int b2;
        from_stream(b2);
        int bn;
        from_stream(bn);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(bridges, a1, a2, an, b1, b2, bn, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1484053623;
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
        cout << "OldBridges (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
