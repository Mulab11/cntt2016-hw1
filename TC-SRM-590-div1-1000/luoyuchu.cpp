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
const int maxd = maxn * maxn;
const int maxb = maxd * 11;

int n;
int S, T;
int mat[maxn][maxn], dir[maxn][maxn], wa[maxn];
int tip[maxn][maxn];
struct edge
{
    int to, next, flow;
    edge() {}
    edge(int _t, int _n, int _f):to(_t), next(_n), flow(_f) {}
}e[maxb];
int head[maxd], et = -1, dt = 0;
int dist[maxd], cur[maxd];

void Addedge(int fr, int to, int flow)//加边
{
    e[++et] = edge(to, head[fr], flow), head[fr] = et;
    e[++et] = edge(fr, head[to], 0), head[to] = et;
}

void Build()//建边
{
    S = 0;
    memset(head, -1, sizeof(head));
    et = -1; dt = 0;//对于每个城市，我们建立他的最短路的长度的个数-1的点，之间用边连成一条链，边权为对应长度的不满意值
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j < mat[0][i]; ++j) {
            tip[i][j] = ++dt;
        }
        if (mat[0][i] != 1) {
            Addedge(S, tip[i][1], (wa[i] - 1) * (wa[i] - 1));
        }
        for (int j = 1; j < mat[0][i] - 1; ++j) {
            Addedge(tip[i][j], tip[i][j + 1], (wa[i] - j - 1) * (wa[i] - j - 1));
        }
    }
    T = ++dt;
    for (int i = 1; i <= n; ++i) {
        if (mat[0][i] != 1) {
            Addedge(tip[i][mat[0][i] - 1], T, (wa[i] - mat[0][i]) * (wa[i] - mat[0][i]));
        }
        else {
            Addedge(S, T, (wa[i] - 1) * (wa[i] - 1));
        }
    }
    for (int i = 1; i <= n; ++i) {//我们会发现，只要保证重建之后的图满足有直接连边的城市的距离值之差的绝对值不超过1,则一定可以建出这样的图，所以只要在有直接连边的城市之间约束好割边的关系即可
        for (int j = i + 1; j <= n; ++j) {
            if (dir[i][j] == 1) {
                for (int k = 1; k <= min(mat[0][i] - 1, mat[0][j] - 2); ++k) {//有直接连边的城市之间一个城市的第i个点向另一个城市的第i-1号点连边
                    Addedge(tip[j][k + 1], tip[i][k], 1e9);
                }
                for (int k = 1; k <= min(mat[0][j] - 1, mat[0][i] - 2); ++k) {//两边都这么做
                    Addedge(tip[i][k + 1], tip[j][k], 1e9);
                }
            }
        }
    }
}

void Bfs()//Bfs求出距离标号
{
    static int line[maxd + 5];
    int h = 0, t = 0;
    memset(dist, 0x3f, sizeof(dist));
    dist[T] = 0;
    line[h++] = T;
    while (h != t) {
        int now = line[t++];
        for (int i = head[now]; i != -1; i = e[i].next) {
            if (e[i ^ 1].flow > 0 && dist[e[i].to] > dist[now] + 1) {
                dist[e[i].to] = dist[now] + 1;
                line[h++] = e[i].to;
            }
        }
    }
}

int Dinic(int p, int res)//Dinic增广
{
    int flow = 0, ff;
    if (p == T || res == 0) return res;
    for (int &i = cur[p]; i != -1; i = e[i].next) {
        if (dist[p] == dist[e[i].to] + 1 && e[i].flow > 0) {
            ff = Dinic(e[i].to, min(res, e[i].flow));
            flow += ff;
            res -= ff;
            e[i].flow -= ff;
            e[i ^ 1].flow += ff;
            if (res == 0) return flow;
        }
    }
    return flow;
}
    
int Solve()
{
    int Ans = 0;
    Build();
    while (1) {//最大流=最小割
        Bfs();
        if (dist[S] > 1e9) break;
        memcpy(cur, head, sizeof(cur));
        Ans += Dinic(S, 1e9);
    }
    return Ans;
}

class FoxAndCity {
    public:
    int minimalCost(vector<string> linked, vector<int> want) {
        n = linked.size() - 1;
        memset(mat, 0x3f, sizeof(mat));
        memset(dir, 0, sizeof(dir));
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= n; ++j) {
                if (linked[i][j] == 'Y') {
                    mat[i][j] = 1;
                    dir[i][j] = 1;
                }
            }
            mat[i][i] = 0;
        }
        for (int k = 0; k <= n; ++k) {//floyd求最短路
            for (int i = 0; i <= n; ++i) {
                for (int j = 0; j <= n; ++j) {
                    Ckmin(mat[i][j], mat[i][k] + mat[k][j]);
                }
            }
        }
        for (int i = 1; i <= n; ++i) {
            wa[i] = want[i];
        }
        return Solve();//利用最小割解决问题
    }
};
