#include <bits/stdc++.h>
using namespace std;

#define dig(...) fprintf(stderr, __VA_ARGS__)

template <class TAT>
void Ckmin(TAT &a, const TAT &b)
{
	if (a > b) a = b;
}
template <class TAT>

void Ckmax(TAT &a, const TAT &b)
{
	if (a < b) a = b;
}

typedef long long LL;

using namespace std;

const int maxn = 55;

int n, m;
LL a[maxn], b[maxn];
int f[maxn][maxn];

class AstronomicalRecords {
public:
    int minimalPlanets(vector<int> A, vector<int> B) {
		int Ans = 0;
		n = A.size();
		m = B.size();
		for (int ap = 0; ap < n; ++ap) {
			for (int bp = 0; bp < m; ++bp) {//枚举两个记录中的哪两个行星是同一个行星
				for (int i = 1; i <= n; ++i) a[i] = (LL)A[i - 1] * B[bp];
				for (int i = 1; i <= m; ++i) b[i] = (LL)B[i - 1] * A[ap];//计算出其他行星的大小的比例
				memset(f, 0, sizeof(f));
				for (int i = ap + 2; i <= n; ++i) {//在枚举的位置的之前与之后做最长公共子序列
					for (int j = bp + 2; j <= m; ++j) {
						f[i][j] = max(f[i][j - 1], f[i - 1][j]);
						if (a[i] == b[j]) Ckmax(f[i][j], f[i - 1][j - 1] + 1);
					}
				}
				for (int i = ap; i >= 1; --i) {
					for (int j = bp; j >= 1; --j) {
						f[i][j] = max(f[i + 1][j], f[i][j + 1]);
						if (a[i] == b[j]) Ckmax(f[i][j], f[i + 1][j + 1] + 1);
					}
				}
				Ckmax(Ans, 1 + f[1][1] + f[n][m]);//更新答案
			}
		}
        return n + m - Ans;
    }
};
