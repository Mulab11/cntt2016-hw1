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
const int maxm = 2555;

int n, m, N, M, nt;
int ce[maxn][maxn];
int val[maxn];
bitset<105> eq[maxn][maxn];
bitset<105> mat[maxm];
bitset<105> now[maxm];

bool Gauss()//高斯消元判断是否有解
{
    static bool vis[maxn*3];
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            if (vis[j] == 0 && mat[j][i] == 1) {
                vis[j] = 1;
                for (int k = 1; k <= M; ++k) {
                    if (vis[k] == 0 && mat[k][i] == 1) {
                        mat[k] = mat[k] ^ mat[j];
                    }
                }
                break;
            }
        }
    }
    for (int i = 1; i <= M; ++i) {
        if (mat[i][N + 1] == 1 && mat[i].count() == 1) {
            return 0;
        }
    }
    int p = 1;
    for (int i = 1; i <= M; ++i) {
        if (mat[i].count() > 0) {
            mat[p] = mat[i];
            ++p;
        }
    }
    M = p;
    return 1;
}

void Dfs(int p)//枚举求解字典序最小
{
    if (p == N + 1) {
        return;
    }
    for (int i = 0; i < 2; ++i) {
        M = nt + 1;
        val[p] = i;
        for (int j = 1; j <= nt; ++j) {
            mat[j] = now[j];
        }
        mat[M].reset();
        mat[M][p] = 1;
        mat[M][N + 1] = i;
        if (Gauss()) {
            nt = M;
            for (int j = 1; j <= M; ++j) {
                now[j] = mat[j];
            }
            Dfs(p + 1);
            return;
        }
    }
}

vector<string> Solve()
{
    vector<string> ans;
    ans.clear();
    N = n + m - 1;
    for (int i = 1; i <= m; ++i) {//确定了第一行第一列就可以确定整个网格，以第一行第一列设未知数
        eq[1][i].reset();
        eq[1][i][i] = 1;
    }
    for (int i = 2; i <= n; ++i) {
        eq[i][1].reset();
        eq[i][1][i + m - 1] = 1;
    }
    for (int i = 2; i <= n; ++i) {
        for (int j = 2; j <= m; ++j) {
            eq[i][j] = eq[i - 1][j] ^ eq[i][j - 1] ^ eq[i - 1][j - 1];
        }
    }
    M = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (ce[i][j] != -1) {
                mat[++M] = eq[i][j];
                mat[M][N + 1] = ce[i][j];
            }
        }
    }
    if (Gauss() == 0) return ans;//判断是否有解
    nt = M;
    for (int i = 1; i <= M; ++i) now[i] = mat[i];
    Dfs(1);//由于要保证字典序最小，暴力地按顺序枚举未知数是否可以为0,每次在方程组中加入一条限制，判断是否有解
    for (int i = 1; i <= n; ++i) {
        string tmp;
        tmp.clear();
        for (int j = 1; j <= m; ++j) {
            bool v = 0;
            for (int k = 1; k <= N; ++k) {
                if (eq[i][j][k]) {
                    v ^= val[k];//求出所有格子的种类
                }
            }
            tmp += (v) ? 'Z' : 'N';
        }
        ans.push_back(tmp);
    }
    return ans;
}

class ThreeColorability {
    public:
    vector<string> lexSmallest(vector<string> cells) {
        n = cells.size();
        m = cells[0].length();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (cells[i][j] == '?') ce[i + 1][j + 1] = -1;
                else ce[i + 1][j + 1] = (cells[i][j] == 'Z');
            }
        }
        return Solve();//我们发现如果一个2x2的各自中左对角线的数量为奇数一定不合法，而如果每个2x2的格子中左对角线的数量都是偶数，则可以归纳证明一定有合法解，如果将左对角线的格子标记为1，否则为0，所以题目限制转变为每个2x2的格子异或为0。
    }
};
