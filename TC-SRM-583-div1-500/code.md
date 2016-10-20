```c++
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

int n;
int edge[maxn][2];
int fa[maxn];
int cnt[maxn];

int Getfa(int p)//并查集
{
    if (fa[p] == p) return p;
    return fa[p] = Getfa(fa[p]);//路径压缩
}

class TurnOnLamps {
    public:
    int minimize(vector<int> roads, string initState, string isImportant) {
        n = roads.size() + 1;
        for (int i = 0; i < n - 1; ++i) {//读入边
            edge[i][0] = roads[i] + 1;
            edge[i][1] = i + 2;
        }
        for (int i = 1; i <= n; ++i) fa[i] = i;//并查集初始化
        for (int i = 0; i < n - 1; ++i) {//将非重要边缩边
            if (isImportant[i] == '0') {
                fa[Getfa(edge[i][0])] = Getfa(edge[i][1]);
            }
        }
        for (int i = 1; i <= n; ++i) Getfa(i);
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < n - 1; ++i) {
            if (isImportant[i] == '1' && initState[i] == '0') {//将边上的计数器的加1(这里记录的奇偶性)
                cnt[fa[edge[i][0]]] ^= 1;
                cnt[fa[edge[i][1]]] ^= 1;
            }
        }
        int Ans = 0;
        for (int i = 1; i <= n; ++i) {//统计为奇数的计数器的数量
            Ans += cnt[i];
        }
        Ans /= 2;//一条路径可覆盖两个端点
        return Ans;//返回答案
    }
};

```