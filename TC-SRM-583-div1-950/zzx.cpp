// BEGIN CUT HERE

// END CUT HERE
#line 5 "RandomPaintingOnABoard.cpp"
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

const int N = 21;

int sum; // the sum of digits in matrix
int n, m; // the size of matrix
int col[N], row[N]; // the sum of digits in each column / row
int a[N][N]; // the digit of (i, j)
double ans;

/*
   inclusive-exlusive principle
   E[max(a1, a2 .. an)] = E[min(a1)] + E[min(a2)] ... - E[min(a1, a2)] - ... + ...
 */

void dp(int x, bool flag) { // dynamic programming to arrange the column
    static int f[2][1351]; // f[1][x] means choose odd number of col/row(s) f[0][x] otherwise
    CL(f, 0);
    f[flag][x] = 1;
    REP(i, 0, m - 1) 
        PER(j, sum, col[i]) {
            int t1 = f[0][j] + f[1][j - col[i]]; 
            int t2 = f[1][j] + f[0][j - col[i]];
            f[0][j] = t1; f[1][j] = t2;
        }
    REP(i, 1, sum) ans += 1.0 * f[1][i] * sum / i - 1.0 * f[0][i] * sum / i;
}

void dfs(int dep, bool flag, double tmp) { //enumerate the row arrangement
    if (dep == n) {
        dp(tmp, flag);
        return;
    }
    dfs(dep + 1, flag, tmp); // don't choose this row
    REP(i, 0, m - 1) col[i] -= a[dep][i]; // choose this row
    dfs(dep + 1, flag ^ 1, tmp + row[dep]);
    REP(i, 0, m - 1) col[i] += a[dep][i];
}

int b[N][N];

void swap() { // rotate the matrix
    REP(i, 0, n - 1)
        REP(j, 0, m - 1) b[j][i] = a[i][j];
    swap(n, m);
    REP(i, 0, n - 1)
        REP(j, 0, m - 1) a[i][j] = b[i][j];
}

class RandomPaintingOnABoard
{
        public:
        double expectedSteps(vector <string> prob)
        {
            n = prob.size();
            m = prob[0].size();
            sum = 0;
            REP(i, 0, n - 1) REP(j, 0, m - 1)
                a[i][j] = prob[i][j] - '0';
            if (n >= m) swap(); 
            CL(col, 0);
            REP(i, 0, n - 1) { //initialize 
                row[i] = 0;
                REP(j, 0, m - 1) {
                    row[i] += a[i][j], col[j] += a[i][j];
                }
                sum += row[i];
            }
            ans = 0;
            dfs(0, 0, 0);
            return ans;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"10",
 "01"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 3.0; verify_case(0, Arg1, expectedSteps(Arg0)); }
	void test_case_1() { string Arr0[] = {"11",
 "11"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 3.6666666666666665; verify_case(1, Arg1, expectedSteps(Arg0)); }
	void test_case_2() { string Arr0[] = {"11",
 "12"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 3.9166666666666665; verify_case(2, Arg1, expectedSteps(Arg0)); }
	void test_case_3() { string Arr0[] = {"0976",
 "1701",
 "7119"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 11.214334077031307; verify_case(3, Arg1, expectedSteps(Arg0)); }
	void test_case_4() { string Arr0[] = {"000000000000001000000",
 "888999988889890999988",
 "988889988899980889999",
 "889898998889980999898",
 "988889999989880899999",
 "998888998988990989998",
 "998988999898990889899"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 1028.7662876159634; verify_case(4, Arg1, expectedSteps(Arg0)); }

// END CUT HERE

};
