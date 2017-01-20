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

const int maxn = 55;
const int maxs = 65539;

int n, m;
struct edge
{
    int to, next, val;
    edge() {}
    edge(int _t, int _n, int _v):to(_t), next(_n), val(_v) {}
}e[maxn * 3];
int head[maxn], et = -1;
int L[maxn], R[maxn], D[maxn];
int f[maxs][maxn];

void Addedge(int a, int b, int c)//加边操作
{
    e[++et] = edge(b, head[a], c), head[a] = et;
    e[++et] = edge(a, head[b], c), head[b] = et;
}

void Spfa(int dist[])//spfa转移
{
    static int line[maxn + 5];
    static bool ever[maxn + 5];
    int h = 0, t = 0;
    for (int i = 0; i < n; ++i) {
        ever[i] = 1;
        line[h++] = i;
    }
    while (h != t) {
        int now = line[t];
        t = (t == maxn) ? 0 : (t + 1);
        ever[now] = 0;
        for (int i = head[now]; i != -1; i = e[i].next) {
            if (dist[e[i].to] > dist[now] + e[i].val) {
                dist[e[i].to] = dist[now] + e[i].val;
                if (ever[e[i].to] == 0) {
                    ever[e[i].to] = 1;
                    line[h] = e[i].to;
                    h = (h == maxn) ? 0 : (h + 1);
                }
            }
        }
    }
}

int Solve()
{
    int N = (1 << m);
    int Ans = 0;
    memset(f, 0x3f, sizeof(f));
    f[0][n - 1] = 0;//f[i][j]表示当前已经购物的商店的集合为i,当前在j商店的最早的时刻
    for (int i = 0; i < N; ++i) {//Dp求解
        Spfa(f[i]);//对于i相同的状态，直接使用最短路转移
        bool ok = 0;
        for (int j = 0; j < n; ++j) {//如果有合法状态，则可以更新答案
            if (f[i][j] < 1e9) {
                ok = 1;
                break;
            }
        }
        if (ok) Ckmax(Ans, __builtin_popcount(i));
        for (int j = 0; j < m; ++j) {//选择一个商店购物
            if ((i >> j) & 1) continue;
            if (f[i][j] <= R[j]) {
                f[i | (1 << j)][j] = max(f[i][j], L[j]) + D[j];
            }
        }
    }
    return Ans;
}

class TravellingPurchasingMan {
    public:
    int maxStores(int N, vector<string> interestingStores, vector<string> roads) {
        n = N;
        stringstream tmp;
        int u, v, c;
        memset(head, -1, sizeof(head));
        et = -1;
        for (int i = 0; i < roads.size(); ++i) {//读入边集
            tmp.clear();
            tmp << roads[i];
            tmp >> u >> v >> c;
            Addedge(u, v, c);
        }
        m = interestingStores.size();
        for (int i = 0; i < m; ++i) {//读入每家感兴趣的商店的信息
            tmp.clear();
            tmp << interestingStores[i];
            tmp >> L[i] >> R[i] >> D[i];
        }
        return Solve();//解决问题
    }
};
