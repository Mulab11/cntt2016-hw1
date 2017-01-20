#include <bits/stdc++.h>

#define dig(...) fprintf(stderr, __VA_ARGS__)

using namespace std;

template <class TAT>
void Ckmax(TAT &a, const TAT &b)
{
    if (a < b) a = b;
}
template <class TAT>
void Ckmin(TAT &a, const TAT &b)
{
    if (a > b) a = b;
}

typedef long long LL;

const int maxn = 2e4+115;

int P[maxn][3];
int pt;

int Cross(int x1, int y1, int x2, int y2)
{
    return x1 * y2 - y1 * x2;
}

class FindPolygons {
    public:
    double minimumPolygon(int L) {
        int Min = 2e9;
        int Hl = L / 2;
        pt = 0;//搜索三角形
        for (int i = 1; i <= L; ++i) {//搜索出(0,0)到哪些(x,y)的距离为整数
            for (int j = 0; i * i + j * j <= Hl * Hl; ++j) {
                int tt = sqrt(i * i + j * j);
                if (tt * tt == i * i + j * j) {
                    P[++pt][0] = i;
                    P[pt][1] = j;
                    P[pt][2] = tt;
                }
            }
        }
        for (int i = 1; i <= pt; ++i) {//枚举两个为整数的(x,y)并判断可行
            for (int j = i + 1; j <= pt; ++j) {
                int tt = sqrt((P[i][0] - P[j][0]) * (P[i][0] - P[j][0]) + (P[i][1] - P[j][1]) * (P[i][1] - P[j][1]));
                if (tt * tt == (P[i][0] - P[j][0]) * (P[i][0] - P[j][0]) + (P[i][1] - P[j][1]) * (P[i][1] - P[j][1])) {
                    if (P[i][2] + P[j][2] + tt == L && tt <= Hl) {
                        if (Cross(P[i][0], P[i][1], P[j][0], P[j][1])) {
                            Min = min(Min, max(abs(tt - P[i][2]), max(abs(tt - P[j][2]), abs(P[j][2] - P[i][2]))));
                        }
                    }
                }
            }
        }
        if (Min < 1e9) return Min;
        if (L & 1) return -1;//奇数无解
        if (L == 2) return -1;//L=2无解
        return ((L / 2) & 1);//矩形
    }
};
