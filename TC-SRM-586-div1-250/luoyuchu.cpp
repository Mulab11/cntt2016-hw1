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

class PiecewiseLinearFunction {
    public:
    int maximumSolutions(vector<int> Y) {
        vector<int> cy;
        int ans = 0, n;
        n = Y.size();
        cy = Y;
        sort(cy.begin(), cy.end());
        for (int i = 0; i < n; ++i) {//考虑这条直线与分段函数交与某个顶点
            int s = 0;
            for (int j = 0; j < n; ++j) {
                if (Y[j] == Y[i]) ++s;
            }
            for (int j = 0; j < n - 1; ++j) {
                if (Y[j] < Y[i] && Y[j + 1] > Y[i]) ++s;
                else if (Y[j] > Y[i] && Y[j + 1] < Y[i]) ++s;
            }
            Ckmax(ans, s);
            if (i != n - 1) {
                if (Y[i] == Y[i + 1]) {
                    Ckmax(ans, (int)2e9);
                }
            }
        }
        for (int i = 0; i < n - 1; ++i) {////考虑这条直线与分段函数不交与某个顶点，只在顶点之间相交
            int s = 0;
            for (int j = 0; j < n - 1; ++j) {
                if (Y[j] <= cy[i] && Y[j + 1] > cy[i]) ++s;
                else if (Y[j] > cy[i] && Y[j + 1] <= cy[i]) ++s;
            }
            Ckmax(ans, s);
        }
        if (ans > 1e9) return -1;//有无限多的解
        else return ans;
    }
};
