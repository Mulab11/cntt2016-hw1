// BEGIN CUT HERE

// END CUT HERE
#line 5 "CoinsGame.cpp"
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

const int mo = 1000000009;
template<class T>
T pow(T a, T b, int c = mo) {
    T res = 1;
    for (T i = 1; i <= b; i <<= 1, a = 1LL * a * a % c) if (b & i) res = 1LL * res * a % c;
    return res;
}

/*======================= TEMPLATE =======================*/
/*
   HASHING
   */

int n, m;
int dirx[] = {1, -1, 0, 0};
int diry[] = {0, 0, 1, -1};
LL h[] = {721234,5433219,2219949,114309};
LL f[41 * 41][50][50];
int a[50][50];
map<LL, int> S;

class CoinsGame
{
        public:
        int ways(vector <string> board)
        {
            n = board.size(); m = board[0].size();
            CL(a, 0); CL(f, 192);
            REP(i, 1, n) REP(j, 1, m) a[i][j] = (board[i - 1][j - 1] == '#'), f[0][i][j] = 213;
            S.clear();
            int cnt = 0;
            REP(ca, 1, n * m) 
                REP(i, 1, n) REP(j, 1, m) {REP(d, 0, 3) {
                    int ii = i + dirx[d], jj = j + diry[d];
                    if (a[ii][jj]) ii = i, jj = j;
                    f[ca][i][j] += f[ca - 1][ii][jj] * h[d];
                }
                if (ca == n * m && !a[i][j]) S[f[ca][i][j]]++, ++cnt;
                }
            int ans = (pow(2, cnt) - 1 + mo) % mo;
            for (map<LL, int>::iterator it = S.begin(); it != S.end(); ++it) {
                int cnt = it -> SC;
                ans = (ans - pow(2, cnt) + 1 + mo) % mo;
            }
            return ans;

        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {".."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, ways(Arg0)); }
	void test_case_1() { string Arr0[] = {"##.#",
 ".###",
 "###.",
 "#.##"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 11; verify_case(1, Arg1, ways(Arg0)); }
	void test_case_2() { string Arr0[] = {"####",
 "#..#",
 "#..#",
 "####"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(2, Arg1, ways(Arg0)); }
	void test_case_3() { string Arr0[] = {"#.#.#"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(3, Arg1, ways(Arg0)); }
	void test_case_4() { string Arr0[] = {"........",
 "........",
 "........",
 "........",
 "........",
 "........",
 "........",
 "........"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 688856388; verify_case(4, Arg1, ways(Arg0)); }

// END CUT HERE

};