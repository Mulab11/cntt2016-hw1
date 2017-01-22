
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
bool f[55][2505];
class KingdomAndDice {
    public:
    double newFairness(vector <int> fi, vector <int> se, int X) {
        sort(se.begin(), se.end());
        int n = fi.size(), m = 0, tot = 0, cnt, ans, mx = 999999999;
        for (int i = 0; i < n; ++i) {
            m += fi[i] == 0;
            for (int j = 0; j < n; ++j)
                tot += fi[i] > se[j];
        }
        for (int i = 0; i <= m; ++i) f[i][tot] = 1;
        for (int i = 0; i < n; ++i) {
            int l = se[i] + 1, r = i == n - 1 ? X : se[i + 1] - 1;
            cnt = r - l + 1;
            for (int j = 0; j < n; ++j)
                if (fi[j] >= l && fi[j] <= r) --cnt;
            cnt = min(cnt, m);
            for (int j = 0; j < cnt; ++j)
                for (int k = m - 1; ~k; --k)
                    for (int p = tot; p <= n * n; ++p)
                        if (f[k][p] && p + i + 1 <= n * n) f[k + 1][p + i + 1] = 1;
        }
        ans = tot;
        for (int j = tot; j <= n * n; ++j)
            for (int i = 0; i <= m; ++i)
                if (f[i][j] && abs(n * n - j * 2) < mx) {ans = j; mx = abs(n * n - j * 2);}
        return 1.0 * ans / n / n;
    }
};

