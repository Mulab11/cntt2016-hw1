#include <bits/stdc++.h>

using namespace std;

#define dig(...) fprintf(stderr, __VA_ARGS__)
template <class TAT>
inline void Ckmin(TAT &a, const TAT &b)
{
	if (a > b) a = b;
}
template <class TAT>
inline void Ckmax(TAT &a, const TAT &b)
{
	if (a < b) a = b;
}
typedef long long LL;

const int maxn = 55;

int n, Ms;
char A[maxn];

int Check(int x)//检查一x这个位置的字母为组成部分，且x位置不移动的最长连续字串
{
    char c;//这个位置字母
    int lp = x - 1, rp = x + 1, lc = 0, rc = 0, res = Ms;//lp,rp:左右的下一个与c相同的字母;lc,rc:左右的连续字串的长度
    c = A[x];
    while (rp < n && A[rp] != c) ++rp;
    while (lp >= 0 && A[lp] != c) --lp;
    while (1) {//每次将距离小的那一边的字母移动过来
        if (lp == -1 && rp == n) break;//两边无字母
        if (lp == -1) {//左边无字母
            if (rp - (x + rc) - 1 <= res) {
                res -= rp - (x + rc) - 1;//将剩余移动步数减去
                ++rc;//计数器增加
                ++rp;
                while (rp < n && A[rp] != c) ++rp;//寻找下一个相同字母
            }
            else {
                break;
            }
        }
        else if (rp == n) {//右边无字母
            if ((x - lc) - lp - 1 <= res) {
                res -= (x - lc) - lp - 1;
                ++lc;
                --lp;
                while (lp >= 0 && A[lp] != c) --lp;
            }
            else {
                break;
            }
        }
        else if (rp - (x + rc) - 1 < (x - lc) - lp - 1) {//右边距离更小
            if (rp - (x + rc) - 1 <= res) {
                res -= rp - (x + rc) - 1;
                ++rc;
                ++rp;
                while (rp < n && A[rp] != c) ++rp;
            }
            else {
                break;
            }
        }
        else {
            if ((x - lc) - lp - 1 <= res) {//左边距离更小
                res -= (x - lc) - lp - 1;
                ++lc;
                --lp;
                while (lp >= 0 && A[lp] != c) --lp;
            }
            else {
                break;
            }
        }
    }
    return 1 + rc + lc;
}

class ColorfulChocolates {
    public:
    int maximumSpread(string chocolates, int maxSwaps) {
        int Ans = 0;
        Ms = maxSwaps;
        n = chocolates.length();
        for (int i = 0; i < n; ++i) {
            A[i] = chocolates[i];
        }
        for (int j = 0; j < n; ++j) {
            Ckmax(Ans, Check(j));//枚举x这个位置的字母为组成部分，且x位置不移动的最长连续字串
        }
        return Ans;//返回答案
    }
};
