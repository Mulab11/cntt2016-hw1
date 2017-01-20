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
const int mod = 1e9+7;
const int maxs = (1 << 16) + 15;

int n;
int fa[maxn];
struct edge
{
    int to, next;
    edge() {}
    edge(int _t, int _n):to(_t), next(_n) {}
}e[maxn];
int head[maxn], et = -1;
int lst[maxn], lt = 0, N;
int constrait[maxn];
int f[maxn][maxs];
bool ban[maxs] = {0};

void Addedge(int a, int b)
{
    e[++et] = edge(b, head[a]), head[a] = et;
}

void Dfs(int p)//树形Dp
{
    static int *a, *b;
    memset(f[p], 0, sizeof(f[p]));
    f[p][0] = 1;
    for (int i = head[p]; i != -1; i = e[i].next) {
        Dfs(e[i].to);
        a = f[p];
        b = f[e[i].to];
        for (int j = N - 1; j >= 0; --j) {//枚举子集，合并子树
            if (!ban[j]) {
                for (int k = j; k != 0; k = (k - 1) & j) {
                    a[j] = (a[j] + (LL)a[j ^ k] * b[k]) % mod;
                }
            }
        }
    }
    if (p != 0) {
        for (int j = N - 1; j >= 0; --j) {//枚举根节点
            for (int k = 0; k < lt; ++k) {
                if (((j >> k) & 1) && (constrait[k] & j) == constrait[k]) {
                    (f[p][j] += f[p][j ^ (1 << k)]) %= mod;
                }
            }
        }
    }
}

int Solve()
{
    int ans = 0;
    Dfs(0);
    ans = f[0][(1 << lt) - 1];
    for (int i = 1; i <= n - lt; ++i) {//乘上其他位置的阶乘
        (ans = (LL)ans * i % mod) %= mod;
    }
    return ans;
}

class SimilarNames {
    public:
    int count(vector<string> names, vector<int> info1, vector<int> info2) {
        n = names.size();
        memset(fa, -1, sizeof(fa));
        memset(head, -1, sizeof(head));
        memset(ban, 0, sizeof(ban));
        sort(names.begin(), names.end());
        et = -1;
        for (int i = 0; i < n; ++i) {//处理前缀关系树
            int Max = 0;
            fa[i + 1] = 0;
            for (int j = 0; j < n; ++j) {
                if (i == j || names[i].length() <= names[j].length()) continue;
                bool ok = 1;
                for (int k = 0; k < (int)names[j].length(); ++k) {
                    if (names[i][k] != names[j][k]) {
                        ok = 0;
                        break;
                    }
                }
                if (ok) {
                    if (Max < (int)names[j].length()) {
                        Max = (int)names[j].length();
                        fa[i + 1] = j + 1;
                    }
                }
            }
        }
        for (int i = 1; i <= n; ++i) {//建树
            Addedge(fa[i], i);
        }
        lt = 0;
        memset(constrait, 0, sizeof(constrait));
        for (int i = 0; i < (int)info1.size(); ++i) {//离散化受限制位置
            lst[++lt] = info1[i];
            lst[++lt] = info2[i];
        }
        sort(lst + 1, lst + 1 + lt);
        lt = unique(lst + 1, lst + 1 + lt) - lst - 1;
        N = (1 << lt);
        for (int i = 0; i < (int)info1.size(); ++i) {//将每个位置的前缀位置压位
            constrait[lower_bound(lst + 1, lst + 1 + lt, info1[i]) - lst - 1] |= (1 << (lower_bound(lst + 1, lst + 1 + lt, info2[i]) - lst - 1));
        }
        for (int i = 0; i < N; ++i) {//处理不合法状态
            for (int j = 0; j < lt; ++j) {
                if ((i & (1 << j)) && (i & constrait[j]) != constrait[j]) {
                    ban[i] = 1;
                    break;
                }
            }
        }
        return Solve();
    }
};
