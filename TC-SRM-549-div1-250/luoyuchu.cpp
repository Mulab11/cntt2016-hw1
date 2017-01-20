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

int n, m;
struct edge
{
    int to, next;
    edge() {}
    edge(int _t, int _n):to(_t), next(_n) {}
}e[maxn * maxn];
int head[maxn], et = -1;
int lk[maxn];
bool vis[maxn];

void Addedge(int x, int y)//加边
{
    e[++et] = edge(y, head[x]), head[x] = et;
}

bool Dfs(int p)//二分图增广
{
    for (int i = head[p]; i != -1; i = e[i].next) {
        if (vis[e[i].to]) continue;
        vis[e[i].to] = 1;
        if (lk[e[i].to] == -1) {
            lk[e[i].to] = p;
            return 1;
        }
        else if (Dfs(lk[e[i].to]) == 1) {
            lk[e[i].to] = p;
            return 1;
        }
    }
    return 0;
}

int Solve()
{
    int Ans = 0;
    for (int i = 1; i <= n; ++i) {//二分图匹配
        memset(vis, 0, sizeof(vis));
        Ans += Dfs(i);
    }
    return Ans;
}

class PointyWizardHats {
    public:
    int getNumHats(vector<int> topHeight, vector<int> topRadius, vector<int> bottomHeight, vector<int> bottomRadius) {
        n = topHeight.size();
        m = bottomHeight.size();
        memset(head, -1, sizeof(head));
        memset(lk, -1, sizeof(lk));
        et = -1;
        for (int i = 0; i < n; ++i) {//判断两个圆锥是否能够组合
            for (int j = 0; j < m; ++j) {
                if (topRadius[i] >= bottomRadius[j]) continue;//顶部半径小于底部半径
                if (topHeight[i] * bottomRadius[j] > bottomHeight[j] * topRadius[i]) {//且顶部斜率大于底部斜率
                    Addedge(i + 1, j + 1);//加边
                }
            }
        }
        return Solve();//二分图匹配
    }
};
