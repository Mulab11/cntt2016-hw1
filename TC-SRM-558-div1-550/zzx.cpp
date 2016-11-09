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

#include <ctime>

/*======================= TEMPLATE =======================*/
string X, Y, Z;
stringstream F;
const int N = 310;
int rx[N], bx[N], by[N];// 红的X坐标以及蓝的坐标
int n;

int area(int x1, int y1, int x2, int y2)  { // 计算叉积 
    return x1 * y2 - x2 * y1;
}

int findL(int a) { // 计算第a个蓝点在X轴投影左侧最近的一个红点
    REP(i, 1, n) if (rx[i] >= bx[a]) return i - 1;
    return n;
}

int findR(int a) { // 计算第a个蓝点在X轴投影右侧最近的一个红点
    PER(i, n, 1) if (rx[i] <= bx[a]) return i + 1;
    return 1;
}

int intersect (int a, int b) { //计算第a个蓝点和第b个蓝点所成直线在X轴上的截距
    REP(i, 1, n) if (rx[i] >= bx[a] || area(bx[a] - rx[i], by[a], bx[b] - rx[i], by[b]) <= 0) return i - 1;
    return 0;
}
class Ear {
    public:
        long long getCount(vector<string> redX, vector<string> blueX, vector<string> blueY) {
            int m = 0, t;
            { // 先处理一下格式 
                X = Y = Z = "";
                for (int i = 0; i < redX.size(); ++i) X += redX[i];
                for (int i = 0; i < blueX.size(); ++i) Y += blueX[i];
                for (int i = 0; i < blueY.size(); ++i) Z += blueY[i];
                F.clear();
                F << X;
                n = 0;
                while (F >> t) rx[++n] = t;
                F.clear();
                F << Y;
                while (F >> t) bx[++m] = t;
                F.clear();
                F << Z;
                m = 0;
                while (F >> t) by[++m] = t;
            }

            sort(rx + 1, rx + n + 1);// 对红点坐标排序

            LL ans = 0;
            REP(P, 1, m) // 枚举P点
                REP(Q, 1, m) { // 枚举Q点
                    if (by[Q] >= by[P]) continue;
                    int RA = min(intersect(Q, P), findL(P)); //A点可行的范围
                    int RB = findL(Q); // B点可行的范围
                    int LC = findR(Q); // C点可行的范围
                    REP(D, 1, n) { //枚举D点
                        if (bx[Q] >= rx[D] || bx[P] >= rx[D]) continue; //P Q点要在D点左侧
                        if (area(bx[Q] - rx[D], by[Q], bx[P] - rx[D], by[P]) >= 0) continue; //Q要在PD左侧
                        int a1 = RB - RA;
                        int num = RA;
                        ans += (2LL * a1 + num - 1) * num  * (D - LC) / 2; //等差数列求和
                    }
                }


            return ans;
        }
};

// CUT begin