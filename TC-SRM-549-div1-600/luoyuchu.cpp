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

const int maxn = 14;
const int maxs = 2e6+115;

int n, m, H, coin, guess;

int row[maxn], col[maxn];//每行列的硬币数需要满足是偶数还是奇数
int three[maxn];//3的幂
char mat[maxn][maxn];//棋盘
int pos[maxn][2];//每个帽子的位置
int F[maxs];//Dp数组

void Prepare()//正在处理3的幂
{
    three[0] = 1;
    for (int i = 1; i <= 13; ++i) {
        three[i] = three[i - 1] * 3;
    }
}

int Getpos(int num, int pos)//正在取得3进制状态的某一位
{
    return (num / three[pos - 1]) % 3;
}

void Dp(int Stat)//对于Stat这个状态的Dp转移
{
    static int bt[maxn], ra[maxn], ca[maxn];//bt:每一位的状态 ra,ca：每一行每一列的硬币数
    static int tmp, res_gus, res_coin, times;//剩余的猜的次数，硬币数
    static int Max, Min;
    tmp = Stat;
    res_gus = guess;
    res_coin = coin;
    times = 0;
    for (int i = 1; i <= H; ++i) {//分解状态
        bt[i] = tmp % 3;
        times += (bt[i] > 0);
        res_gus -= (bt[i] > 0);
        res_coin -= (bt[i] == 2);
        tmp /= 3;
    }
    if (H - times < res_coin) {//装不下，不合法
        F[Stat] = -1;
        return;
    }
    if (res_coin == 0) {//检查每一行每一列帽子和硬币的和是否为偶数
        memset(ra, 0, sizeof(ra));
        memset(ca, 0, sizeof(ca));
        for (int i = 1; i <= H; ++i) {
            if (bt[i] == 2) {
                ++ra[pos[i][0]];
                ++ca[pos[i][1]];
            }
        }
        for (int i = 1; i <= n; ++i) {//不合法
            if ((row[i] + ra[i]) & 1) {
                F[Stat] = -1;
                return;
            }
        }
        for (int i = 1; i <= m; ++i) {//不合法
            if ((col[i] + ca[i]) & 1) {
                F[Stat] = -1;
                return;
            }
        }
        F[Stat] = 0;//合法
        return;
    }
    Max = -1;
    for (int i = 1; i <= H; ++i) {
        if (bt[i] == 0) {//枚举猜的是那个帽子
            Min = 2e9;
            if (F[Stat + three[i - 1]] != -1 && H - times > res_coin) {//魔术师选择不放硬币
                Ckmin(Min, F[Stat + three[i - 1]]);
            }
            if (F[Stat + three[i - 1] * 2] != -1) {
                Ckmin(Min, F[Stat + three[i - 1] * 2] + (res_gus > 0));//放硬币
            }
            if (Min < 1e9) Ckmax(Max, Min);
        }
    }
    F[Stat] = Max;
}

class MagicalHats {
    public:
    int findMaximumReward(vector<string> board, vector<int> coins, int numGuesses) {
        int Ans = 0;
        int N;
        Prepare();
        n = board.size();
        m = board[0].length();
        H = 0;
        coin = coins.size();
        guess = numGuesses;
        memset(row, 0, sizeof(row));
        memset(col, 0, sizeof(col));
        for (int i = 1; i <= n; ++i) {//统计帽子
            for (int j = 1; j <= m; ++j) {
                mat[i][j] = board[i - 1][j - 1];
                if (mat[i][j] == 'H') {
                    ++H;
                    pos[H][0] = i;
                    pos[H][1] = j;
                    ++row[i];
                    ++col[j];
                }
            }
        }
        N = three[H];
        for (int i = N - 1; i >= 0; --i) {//Dp
            Dp(i);
        }
        sort(coins.begin(), coins.end());//在硬币量一定时，魔术师一定从小到大给硬币
        if (F[0] < 0) Ans = -1;
        else {
            for (int i = 0; i < F[0]; ++i) {
                Ans += coins[i];
            }
        }
        return Ans;
    }
};
