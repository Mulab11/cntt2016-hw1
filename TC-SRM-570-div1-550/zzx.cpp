// BEGIN CUT HERE

// END CUT HERE
#line 5 "CentaurCompany.cpp"
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

const int N = 50;
double f[N][2][N][N];
struct node {
    int p, next;
}edge[N * 2];
int head[N], cnt;
void ae(int a, int b ){
    edge[++cnt].p = b;
    edge[cnt].next = head[a];
    head[a] = cnt;
}

double g[2][N][N];
int n;

void dp(int u, int fa) {// dp to calculate the possibility of obtaining (i, j)
    RED(k, u) {
        int v = edge[k].p;
        if (v != fa) dp(v, u);
    }
    //dp f[u][0]
    CL(g, 0);
    int c = 0;
    g[0][0][0] = 0.5; 
    RED(k, u) { 
        int v = edge[k].p;
        if (v == fa) continue;
        c ^= 1;
       CL(g[c], 0);// a beibao dynamic programming
        REP(i, 0, n)
            REP(j, 0, i) 
                REP(k1, 0, i)
                    REP(k2, 0, min(j, k1))  // enum the value of certain 
                    g[c][i][j] += (f[v][0][k1][k2] + f[v][1][k1][k2]) 
                    * g[c ^ 1][i - k1][j - k2];
    }
    REP(i, 0, n) REP(j, 0, i) f[u][0][i][j] = g[c][i][j];

    CL(g, 0);
    c = 0;
    g[0][1][1] = 0.5;
    RED(k, u) {//enumerate descendant
        int v = edge[k].p;
        if (v == fa) continue;
        c ^= 1;
        CL(g[c], 0); // another beibao dynamic programming
        REP(i, 0, n)
            REP(j, 0, i) 
                REP(k1, 0, i)
                    REP(k2, 0, min(j, k1)) 
                    g[c][i][j] += f[v][0][k1][k2] * g[c ^ 1][i - k1][j - k2]
                    + f[v][1][k1][k2] * g[c ^ 1][i - k1][j - k2 + 1];
    }
    REP(i, 0, n) REP(j, 0, i) f[u][1][i][j] = g[c][i][j];
}


class CentaurCompany
{
        public:
        double getvalue(vector <int> a, vector <int> b)
        {
            CL(f, 0); CL(head, 0); cnt = 0;
            n = a.size() + 1;
            REP(i, 1, n - 1) ae(a[i - 1], b[i - 1]), ae(b[i - 1], a[i - 1]); // add the edges
            dp(1, 0);
            double ans = 0;
            REP(i, 0, n) // enum the number of nodes of the human company
                REP(j, 0, i) { // enum the number of connected components
                    double tmp = 2.0 * j - 2  - i; // the value of (i, j) is 2j-2-i
                    if (tmp > 0) ans += tmp * (f[1][0][i][j] + f[1][1][i][j]);
                }
            return ans * 2.0;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 0.0; verify_case(0, Arg2, getvalue(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,3,4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 0.125; verify_case(1, Arg2, getvalue(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {1,2,3,2,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,3,4,5,6}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 0.375; verify_case(2, Arg2, getvalue(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {1,2,3,4,5,6,7,8,9}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,3,4,5,6,7,8,9,10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 0.41796875; verify_case(3, Arg2, getvalue(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 15.500000001076842; verify_case(4, Arg2, getvalue(Arg0, Arg1)); }
	void test_case_5() { int Arr0[] = {10, 7, 2, 5, 6, 2, 4, 9, 7}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {8, 10, 10, 4, 1, 6, 2, 2, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 0.646484375; verify_case(5, Arg2, getvalue(Arg0, Arg1)); }

// END CUT HERE

};
