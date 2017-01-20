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

class TheTree {
    public:
    int maximumDiameter(vector<int> cnt) {
        int n = cnt.size();
        int Ans = n, last = 0;
        for (int i = 1; i <= n; ++i) {//对于任何cnt，如果大于2与等于2是等价的，所以只需考虑1和2的情况，直接检查每个一叶子节点最最深的点的距离即可
            if (cnt[i - 1] == 1 && cnt[i - 2] > 1) {
                Ckmax(Ans, n + (i - 1) - last * 2);
            }
            if (cnt[i - 1] > 1 && (cnt[i - 2] == 1 || i == 0)) {
                last = i - 1;
            }
        }
        if (cnt[n - 1] > 1) Ckmax(Ans, n + n - last * 2);
        return Ans;
    }
};
