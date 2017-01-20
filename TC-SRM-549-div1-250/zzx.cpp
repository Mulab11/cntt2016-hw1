// BEGIN CUT HERE

// END CUT HERE
#line 5 "PointyWizardHats.cpp"
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

const int N = 100;

int n, m;
int g[100][100];
int link[N];
bool vis[N];

bool find(int u) {
    REP(i, 0, m - 1) if (!vis[i] && g[u][i]) {
        vis[i] = 1;
        if (link[i] == -1 || find(link[i])) {
            link[i] = u;
            return true;
        }
    }
    return false;
}

class PointyWizardHats
{
        public:
        int getNumHats(vector <int> h1, vector <int> r1, vector <int> h2, vector <int> r2)
        {
            CL(g, 0);
            n = h1.size();
            m = h2.size();
            CL(link, 0xff);
            REP(i, 0, n - 1) 
                REP(j, 0, m - 1) if (h1[i] * r2[j] > h2[j] * r1[i] && r1[i] < r2[j])
                g[i][j] = 1;
            int ans = 0;
            REP(i, 0, n - 1)  {
                CL(vis, 0);
                ans += find(i);
            }
            return ans;
        }
        

};
