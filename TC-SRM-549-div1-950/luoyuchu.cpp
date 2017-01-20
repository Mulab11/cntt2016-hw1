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

const int maxn = 7;

int n, minW, maxW, Ans;
int amount[maxn];//每种颜色方块的数量
int pre[maxn][maxn], pt[maxn];//每个方块底下的方块
int suf[maxn][maxn], st[maxn];//每个方块上面的方块
int du[maxn];//图中每个点的度数
int tip[maxn], Index;//这种颜色属于第几层

LL Pow(LL x, int y)//快速幂
{
    LL S = 1;
    while (y) {
        if (y & 1) S = S * x;
        x = x * x;
        y >>= 1;
    }
    return S;
}

bool Check()//检查这张图是否对应一个合法方案
{
    static int line[maxn], h, t, cur;
    static int list[maxn], lt;
    static int am[maxn], tmp, cnt;
    static bool ever[maxn];
    h = 0, t = 0;
    memcpy(am, amount, sizeof(am));
    memset(tip, 0, sizeof(tip));
    for (int i = 1; i <= n; ++i) {//检查每种颜色度数是否小于方块数
        if (am[i] < pt[i]) {
            return 0;
        }
    }
    for (int i = 1; i <= n; ++i) {//拓扑排序，检查是否正常分层
        if (du[i] == 0) {
            tip[i] = 1;
            line[h++] = i;
        }
    }
    while (h != t) {
        cur = line[t++];
        for (int i = 1; i <= st[cur]; ++i) {
            if (tip[suf[cur][i]] == 0 || tip[suf[cur][i]] == tip[cur] + 1) {
                tip[suf[cur][i]] = tip[cur] + 1;
            }
            else {
                return 0;
            }
            if ((--du[suf[cur][i]]) == 0) {
                line[h++] = suf[cur][i];
            }
        }
    }
    if (h != n) return 0;//是否无环
    for (int i = 2; i <= 6; ++i) {//霍尔定理，检查是否有完美匹配
        lt = 0;
        for (int j = 1; j <= n; ++j) {
            if (tip[j] == i) {
                list[++lt] = j;
            }
        }
        if (lt == 0) return 1;
        int N = (1 << lt);//先保证至少一个方块的接触
        for (int j = 1; j <= lt; ++j) {
            for (int k = 1; k <= pt[list[j]]; ++k) {
                if ((--am[pre[list[j]][k]]) < 0) {
                    return 0;
                }
            }
        }
        for (int j = 1; j < N; ++j) {//霍尔定理检查
            tmp = j;
            cnt = 0;
            memset(ever, 0, sizeof(ever));
            for (int k = 1; k <= lt; ++k) {
                if (tmp & 1) {
                    cnt -= am[list[k]] - pt[list[k]];
                    for (int p = 1; p <= pt[list[k]]; ++p) {
                        if (ever[pre[list[k]][p]] == 0) {
                            ever[pre[list[k]][p]] = 1;
                            cnt += am[pre[list[k]][p]];
                        }
                    }
                }
                tmp >>= 1;
            }
            if (cnt < 0) return 0;
        }
    }
    return 1;//返回合法
}

void Stat()
{
    static int f[65], N;//统计一种合法方案的拆解方案数
    static bool ok = 0;
    N = (1 << n);
    memset(f, 0, sizeof(f));//状态压缩Dp
    f[0] = 1;
    for (int i = 0; i < N; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (!((i >> (j - 1)) & 1)) {//是否已经扩展
                ok = 1;
                for (int k = 1; k <= pt[j]; ++k) {//是否允许扩展
                    if (!((i >> (pre[j][k] - 1)) & 1)) {
                        ok = 0;
                        break;
                    }
                }
                if (ok) {//已授权扩展
                    f[i | (1 << (j - 1))] += f[i];
                }
            }
        }
    }
    if (f[N - 1] >= minW && f[N - 1] <= maxW) {//若拆解方案数在可识别范围，则计入答案
        ++Ans;
    }
}

void Solve()
{
    register int Maxedge = n * (n - 1) / 2;
    register int N = Pow(3, Maxedge);
    register int tmp;
    for (register int i = 0; i < N; ++i) {//枚举转化之后的图，0表示无边，1表示正向边，2为反向边
        tmp = i;
        memset(pt, 0, sizeof(pt));//清零边计数器
        memset(st, 0, sizeof(st));//清零边计数器
        memset(du, 0, sizeof(du));//清零点度数
        for (register int a = 1; a <= n; ++a) {//加边
            for (register int b = a + 1; b <= n; ++b) {
                if (tmp % 3 == 1) {
                    pre[a][++pt[a]] = b;
                    suf[b][++st[b]] = a;
                    ++du[a];
                }
                if (tmp % 3 == 2) {
                    pre[b][++pt[b]] = a;
                    suf[a][++st[a]] = b;
                    ++du[b];
                }
                tmp /= 3;
            }
        }
        if (Check()) {//检验合法性
            Stat();//统计方案数
        }
    }
}

class CosmicBlocks {
    public:
    int getNumOrders(vector<int> blockTypes, int minWays, int maxWays) {
        n = blockTypes.size();
        minW = minWays;
        maxW = maxWays;
        Ans = 0;
        for (int i = 1; i <= n; ++i) amount[i] = blockTypes[i - 1];//正在复制方块数
        Solve();//开始解题
        return Ans;//成功解题！正在返回答案。
    }
};
