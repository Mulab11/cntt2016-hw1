// BEGIN CUT HERE

// END CUT HERE
#line 5 "SparseFactorial.cpp"
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

const int N = 1100000;
int num[N];
bool flag[20][N];
LL a[N];
LL b[N];
LL lim;
int m;

LL calc(LL n, int d, int r) {//计算[0, n]有多少数mod d = r
    if (n < d) return (n >= r);
    LL ans = n / d;
    return n / d + calc(n - n / d * d, d, r);
}

void solve(int p, int q) { // solve p ^ q
    int n = pow(p, q);
    REP(i, 0, n - 1) a[i] = -1, num[i] = 0;
    REP(i, 1, q) {
        int t = pow(p, i);
        REP(j, 0, t - 1)
        flag[i][j] = 0;
    }
    REP(i, 0, lim) { // enum the i ^ 2
        REP(k, 1, q) {
            int t = pow(p, k); 
            bool vis = 1;
            if (flag[k][1LL * i * i % t]) continue; // if it is already solved 
            for (int j = 1LL * i * i % t; j < n; j += t) { // enum the j % p^k = i^2 % p^k
                ++num[j]; if (num[j] == q) a[j] = 1LL * i * i + 1;
                if (num[j] < q) vis = 0;
            }
            flag[k][1LL * i * i % t] = vis;
        }
    }
    REP(i, 0, n - 1)
        for (int j = i; j < m; j += n) 
            if (a[i] == -1) b[j] = -1;
            else if (b[j] != -1) getmax(&b[j], a[i]); // getmax
}

class SparseFactorial
{
    public:
        long long getCount(long long lo, long long hi, long long D) {
            CL(b,0);
            for (lim = 0; 1LL * lim * lim < hi; ++lim);
            while (1LL * lim * lim >= hi) --lim;
            m = D;
            for (int i = 2; i <= D; ++i) if (D % i == 0) { //分解质因子
                int t = 0;
                while (D % i == 0) D /= i, ++t;
                solve(i, t);
            }
            LL ans = 0;
            REP(i, 0, m - 1) if (b[i] != -1) {
                LL l = max(lo, b[i]), r = hi;//合并 找到最后一个才满足的因子
                if (r >= l) ans += calc(r, m, i) - calc(l - 1, m, i);
            }
            return ans;
        }

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        void test_case_0() { long long Arg0 = 4LL; long long Arg1 = 8LL; long long Arg2 = 6LL; long long Arg3 = 3LL; verify_case(0, Arg3, getCount(Arg0, Arg1, Arg2)); }
        void test_case_1() { long long Arg0 = 9LL; long long Arg1 = 11LL; long long Arg2 = 7LL; long long Arg3 = 1LL; verify_case(1, Arg3, getCount(Arg0, Arg1, Arg2)); }
        void test_case_2() { long long Arg0 = 1LL; long long Arg1 = 1000000000000LL; long long Arg2 = 4LL; long long Arg3 = 999999999996LL; verify_case(2, Arg3, getCount(Arg0, Arg1, Arg2)); }
        void test_case_3() { long long Arg0 = 55LL; long long Arg1 = 66LL; long long Arg2 = 98LL; long long Arg3 = 7LL; verify_case(3, Arg3, getCount(Arg0, Arg1, Arg2)); }
        void test_case_4() { long long Arg0 = 999990LL; long long Arg1 = 999999LL; long long Arg2 = 589824LL; long long Arg3 = 7LL; verify_case(4, Arg3, getCount(Arg0, Arg1, Arg2)); }
        void test_case_5() { long long Arg0 = 100000000LL; long long Arg1 = 100000050LL; long long Arg2 = 749910LL; long long Arg3 = 8LL; verify_case(5, Arg3, getCount(Arg0, Arg1, Arg2)); }
        void test_case_6() { long long Arg0 = 7777777776LL; long long Arg1 = 7777777777LL; long long Arg2 = 994009LL; long long Arg3 = 1LL; verify_case(6, Arg3, getCount(Arg0, Arg1, Arg2)); }

        // END CUT HERE

};
