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

class BigFatInteger {
    public:
    int minOperations(int A, int B) {
        int tmp = A;
        int ys[35][2], yt = 0;
        int Ans = 0;
        for (int i = 2; i * i <= tmp; ++i) {//对于每一个质数因子都是一个倍增的过程
            if (tmp % i == 0) {
                ys[++yt][0] = i;
                ys[yt][1] = 0;
                while (tmp % i == 0) {
                    tmp /= i;
                    ++ys[yt][1];
                }
            }
        }
        if (tmp != 1) {
            ys[++yt][0] = tmp;
            ys[yt][1] = 1;
        }
        for (int i = 1; i <= yt; ++i) {
            ys[i][1] *= B;
            for (int j = 0; j <= 29; ++j) {
                if ((1 << j) >= ys[i][1]) {
                    Ckmax(Ans, j);//求出最大的倍增的次数
                    break;
                }
            }
        }
        return Ans + yt;//加上质数因子的个数即可
    }
};
