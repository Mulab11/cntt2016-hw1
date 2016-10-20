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

int n, S, T;
int R[maxn];
int dist[maxn];

void Bfs()//运行Bfs找最短路
{
    static int line[maxn];
    int h = 0, t = 0;
    memset(dist, 0x3f, sizeof(dist));//初始化
    dist[S] = 0;
    line[h++] = S;
    while (h != t) {
        int cur = line[t++];
        for (int i = 1; i <= n; ++i) {
            if (min(abs(i - cur), n - abs(i - cur)) <= R[cur] && dist[i] > dist[cur] + 1) {//判断这两个点的距离是否在范围内
                dist[i] = dist[cur] + 1;//更新距离
                line[h++] = i;
            }
        }
    }
}

class TravelOnMars {
    public:
    int minTimes(vector<int> range, int startCity, int endCity) {
        n = range.size();
        S = startCity + 1;
        T = endCity + 1;
        for (int i = 1; i <= n; ++i) R[i] = range[i - 1];
        Bfs();
        return dist[T];//返回答案
    }
};
