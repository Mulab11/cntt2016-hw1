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
int A[maxn];

bool Check(int L)//检查二分的值是否合法
{
    int last = -2e9;//上一个元素的值
    for (int i = 1; i <= n; ++i) {
        Ckmax(last, last + 1);
        Ckmax(last, A[i] - L);
        Ckmax(last, 1);
        if (last > A[i] + L) return 0;
    }
    return 1;
}

class KingdomAndTrees {
    public:
    int minLevel(vector<int> heights) {
        n = heights.size();
        for (int i = 0 ;i < n; ++i) A[i + 1] = heights[i];
        int l = 0, r = 1e9;
        int mid;//二分
        while (l != r) {
            mid = (l + r) / 2;
            if (Check(mid)) r = mid;
            else l = mid + 1;
        }
        return l;
    }
};
