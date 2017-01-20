// BEGIN CUT HERE

// END CUT HERE
#line 5 "MagicalHats.cpp"
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

const int N = 14;
const int M = 1600000;
const int inf = mo;
char g[N][N];
int x[N], y[N];
int nx[N], ny[N];
int s[N];
int f[M];
int coin[N];
int r, c, n, m, lim;
void decode(int x, int *c) {
    REP(i, 0, n - 1) c[i] = x % 3, x /= 3;
}
int encode(int *c) {
    int x = 0;
    PER(i, n - 1, 0) x = x * 3 + c[i];
    return x;
}

bool check(int sta) {
    decode(sta, s);
    CL(nx, 0); CL(ny, 0);
    int tot = 0;
    REP(i, 0, n - 1) nx[x[i]] += s[i], ny[y[i]] += s[i], tot += s[i] - 1;
    if (tot != m) return 0;
    REP(i, 0, r - 1) if (nx[i] & 1) return 0;
    REP(i, 0, c - 1) if (ny[i] & 1) return 0;
    return 1;
}

int dp(int sta, int num, int cs) {
    if (f[sta] != -1) return f[sta];
    if (num > n) {
        if (check(sta)) return f[sta] = 0;
        else return f[sta] = inf;
    }
    decode(sta, s);
    int res = 0;
    REP(i, 0, n - 1) if (!s[i]) {
        int tmp = inf;
        s[i] = 1;
        getmin(&tmp, dp(encode(s), num + 1, cs));
        if (cs < m) { 
            s[i] = 2;
            int z = 0; if (num <= lim) z = coin[cs];
            getmin(&tmp, z + dp(encode(s),  num + 1, cs + 1));
        }
        getmax(&res, tmp);
        s[i] = 0;
    }
    return f[sta] = res;
}

class MagicalHats
{
        public:
        int findMaximumReward(vector <string> board, vector <int> coins, int numGuesses)
        {
            m = coins.size();
            REP(i, 0, m - 1) coin[i] = coins[i];
            sort(coin, coin + m);
            CL(x, 0); CL(y, 0);
            r = board.size(); c = board[0].size();
            n = 0;
            REP(i, 0, r - 1) REP(j, 0, c - 1) if (board[i][j] == 'H') x[n] = i, y[n] = j, ++n;
            CL(f, 0xff);
            lim = numGuesses;
            int ans = dp(0, 1, 0);
            if (ans == inf) return -1;
            return ans;
        }
        

};
