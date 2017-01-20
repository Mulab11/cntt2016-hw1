// BEGIN CUT HERE

// END CUT HERE
#line 5 "CurvyonRails.cpp"
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
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <sstream>
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

template<class T> inline
void read(T *a) {
    char c;
    while (isspace(c = getchar())) {}
    bool flag = 0;
    if (c == '-') flag = 1, *a = 0;
    else
        *a = c - 48;
    while (isdigit(c = getchar())) *a = *a * 10 + c - 48;
    if (flag) *a = -*a;
}

const int mo = 1000000007;
template<class T>
T pow(T a, T b, int c = mo) {
    T res = 1;
    for (T i = 1; i <= b; i <<= 1, a = 1LL * a * a % c) if (b & i) res = 1LL * res * a % c;
    return res;
}

/*======================= TEMPLATE =======================*/

class ZKW { //template of ZKW MCMF
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
        int cnt,n ,m,index,tot;
        int S, T;
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
            return MP(flow, ans);
        }
        void init(int n) {
            cnt = 1;
            REP(i, 1, n + 2) head[i] = 0;
        }
}solver;

const int N = 30;
int tot;
int id[N][N][3];
int tp[N][N];
int n, m;
int s, t;

class CurvyonRails
{
        public:
        int getmin(vector <string> field) {
            n = field.size(); m = field[0].size();
            tot = 2;
            REP(i, 0, n - 1) REP(j, 0, m - 1) tp[i][j] = (i & 1) ^ (j & 1);
            //color the grid using black and white
            int numb = 0, numw = 0;
            REP(i, 0, n - 1)
                REP(j, 0, m - 1) if (field[i][j] != 'w') {// number the grid
                    id[i][j][0] = ++tot;
                    id[i][j][1] = ++tot; // edge between the same line
                    id[i][j][2] = ++tot; // edge between the same column
                }
            s = tot + 1, t = tot + 2;
            solver.init(tot);//initialize the MCMF solver
            REP(i, 0, n - 1)
                REP(j, 0, m - 1) if (field[i][j] != 'w') { // empty grid
                    if (tp[i][j]) {//black grid
                        ++numb; // inc the number of black grids
                        solver.ae(s, id[i][j][0], 2, 0);
                        solver.ae(id[i][j][0], id[i][j][1], 1, 0); // meizi grid
                        solver.ae(id[i][j][0], id[i][j][1], 1, field[i][j] == 'C'); // jilao grid
                        solver.ae(id[i][j][0], id[i][j][2], 1, 0); // meizi grid
                        solver.ae(id[i][j][0], id[i][j][2], 1, field[i][j] == 'C'); // jilao grid
                    } else {
                        ++numw;
                        solver.ae(id[i][j][0], t, 2, 0);
                        solver.ae(id[i][j][1], id[i][j][0], 1, 0);
                        solver.ae(id[i][j][1], id[i][j][0], 1, field[i][j] == 'C');
                        solver.ae(id[i][j][2], id[i][j][0], 1, 0);
                        solver.ae(id[i][j][2], id[i][j][0], 1, field[i][j] == 'C');
                    }
                }
            REP(i, 0, n - 1)
                REP(j, 0, m - 1) if (field[i][j] != 'w' && tp[i][j]) { // add edges between grid
                    if (i && field[i - 1][j] != 'w') solver.ae(id[i][j][1], id[i - 1][j][1], 1, 0);
                    if (j && field[i][j - 1] != 'w') solver.ae(id[i][j][2], id[i][j - 1][2], 1, 0);
                    if (i < n - 1 && field[i + 1][j] != 'w') 
                        solver.ae(id[i][j][1], id[i + 1][j][1], 1, 0); 
                    if (j < m - 1 && field[i][j + 1] != 'w') 
                        solver.ae(id[i][j][2], id[i][j + 1][2], 1, 0);
                }
            if (numw != numb) return -1; // if the number of 2 color is not equal then return -1
            pair<LL, LL> ans = solver.MCMF(s, t);
            if (ans.FR != 2LL * numb) return -1;
            return ans.SC;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {".."
,".."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(0, Arg1, getmin(Arg0)); }
	void test_case_1() { string Arr0[] = {"wCCww"
,"wCC.."
,"..w.."
,"....w"
,"ww..w"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(1, Arg1, getmin(Arg0)); }
	void test_case_2() { string Arr0[] = {"C.w"
,"..."
,".C."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(2, Arg1, getmin(Arg0)); }
	void test_case_3() { string Arr0[] = {"."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(3, Arg1, getmin(Arg0)); }
	void test_case_4() { string Arr0[] = {"w"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(4, Arg1, getmin(Arg0)); }
	void test_case_5() { string Arr0[] = {"CC..CCCw.CwC..CC.w.C",
 "C.CCCwCCC.w.w..C.w..",
 "wwww...CC.wC.Cw.CC..",
 "CC..CC.w..w.C..CCCC.",
 "CC.CCC..CwwCCC.wCC..",
 "w.C..wwCC.CC.wwwCC..",
 ".CC.CC..CCC..CC.CC.C",
 "Cw....C.C.CCC...CC..",
 "CC.C..Cww.C.CwwwC..w",
 "wCCww..C...CCCCCCC.w",
 "C.CCw.CC.ww...C.CCww",
 "C.C.C.CCwCC..wCCw.Cw",
 "CCC.C...w..C.wC.wCCw",
 "CC.C..C..CCC.CC.C...",
 "C.ww...CCC..CC...CCC",
 "...CCC.CwwwC..www.C.",
 "wwCCCCC.w.C.C...wCwC",
 "CCwC.CwCCC.C.w.Cw...",
 "C.w.wC.CC.CCC.C.w.Cw",
 "CCw.CCC..C..CC.CwCCw",
 "C.wwwww.CwwCCwwwwwww"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 9; verify_case(5, Arg1, getmin(Arg0)); }

// END CUT HERE

};
// BEGIN CUT HERE
