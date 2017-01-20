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

class JumpFurther {
    public:
    int furthest(int N, int badStep) {
        int det = 0;
        int S = 0;
        for (int i = 1; i <= N; ++i) {//如果直接跳合法就直接跳，否则第一步不跳就一定合法
            S += i;
            if (S == badStep) {
                det = 1;
            }
        }
        return S - det;
    }
};
