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

int n;
int a[100];//a[i]代表纸带上第i位置的颜色， 1 代表 Red， 2 代表 Green, 0代表Blue, -1代表*

bool check(int l, int r, int c) {//检查[l,r]这一段能否涂上c这个颜色
    REP(i, l, r) {
        if (a[i] == -1) continue;
        if (a[i] != c) return false;
    }
    return true;
}
int f[100][3];// f[i][j] 代表目前dp了前i个位置，最近一次使用的Stamp的颜色是{0, 1, 2}中的一种的情况下的最少代价

int dp(int L) { //dp判断长度为L的stamp最少需要多少次才能涂满
    REP(i, 1, n) REP(j, 0, 2) f[i][j] = 1000; 
    REP(i, L, n) {
        REP(j, 0, 2) {
            if (!check(i - L + 1, i, j)) continue; //如果发现这一段不能用j这个颜色涂（和目标冲突）就不合法
            REP(k, 0, 2)
                getmin(&f[i][j], f[i - L][k] + 1); //前一段和这一段不相交
            REP(k, i - L + 1, i - 1) getmin(&f[i][j], f[k][j] + 1); //相交的情况，那么两段必须要用同一种颜色，不然后一段就无法染上去了
        }
    }
    return min(min(f[n][0], f[n][1]), f[n][2]); //最后一次可以选择染0， 1， 2 三种颜色中的任意一种
}

class Stamp
{
        public:
        int getMinimumCost(string desiredColor, int stampCost, int pushCost)
        {
            map<char, int> S;
            S['*'] = -1;
            S['R'] = 1;
            S['G'] = 2;
            S['B'] = 0;
            n = desiredColor.size();
            REP(i, 1, n) a[i] = S[desiredColor[i - 1]];
            int ans = 1e9;
            REP(i, 1, n) { //暴力枚举L的长度
                int x = dp(i); 
                if (x != -1) getmin(&ans, i * stampCost + x * pushCost); //最终的答案等于L * stampCost + dp(L) * pushCost
            }
            return ans;
        }
        
};
