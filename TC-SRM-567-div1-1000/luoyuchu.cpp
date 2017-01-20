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
const int mod = 1e9+9;

class Mountains {
    public:
    int n, w;
    int h[maxn];//山的高度
    bool vis[maxn][maxn];//每座山在每列是否可见
    map<pair<vector<char>, int>, int> F;//记忆化数组
    vector<char> tmp;

    int Depth_first_search(vector<char> stat, int p)//Dfs搜索，但前每列的最高高度为stat[i]，还有0~p的山没有确定位置
    {
        int sum = 0;
        for (int i = 0; i < w; ++i) {//枚举山峰的位置
            bool ok = 1;
            for (int j = 0; j < w; ++j) {//每个位置山的高度
                if ((h[p] - abs(j - i) > stat[j]) != vis[p][j]) {
                    ok = 0;
                    break;
                }
            }
            if (ok) {
                if (p == 0) {//Dfs搜索的终点
                    sum += 1;
                }
                else {
                    tmp = stat;//tmp为新的状态
                    for (int j = 0; j < w; ++j) {
                        if (vis[p][j]) {
                            tmp[j] = h[p] - abs(j - i);
                        }
                    }
                    if (F.count(make_pair(tmp, p - 1)) == 0) (sum += Depth_first_search(tmp, p - 1)) %= mod;
                    else (sum += F[make_pair(tmp, p - 1)]) %= mod;
                }
            }
        }
        return F[make_pair(stat, p)] = sum;
    }
    
    int countPlacements(vector<int> heights, vector<string> visibility) {
        vector<char> initial;
        n = heights.size();
        w = visibility[0].length();
        for (int i = 0; i < n; ++i) h[i] = heights[i];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < w; ++j) {
                vis[i][j] = (visibility[i][j] == 'X');
            }
        }
        initial.resize(w);
        Depth_first_search(initial, n - 1);
        return F[make_pair(initial, n - 1)];
    }
};

