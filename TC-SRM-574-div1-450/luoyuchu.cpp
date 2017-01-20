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

const int maxn = 19;
const int maxs = (1 << 18) + 15;

class PolygonTraversal {
    public:
    long long count(int n, vector<int> points) {
		static LL f[maxs][maxn];//f[i][j]表示但前已经经过的点的集合为i，上一个点是j
		int N = (1 << n);
		int s = 0;
		int cnt0, cnt1;
		memset(f, 0, sizeof(f));
		for (int i = 0; i < (int)points.size(); ++i) {
			s |= (1 << (points[i] - 1));
		}
		f[s][points.back() - 1] = 1;//初始状态
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < n; ++j) {
				if (f[i][j]) {
					cnt0 = __builtin_popcount(i) - 1;//当前已经选取的点的个数
					cnt1 = 0;
					for (int k = (j + 1) % n; k != j; (k += 1) %= n) {
						cnt1 += ((i >> k) & 1);
						if ((i >> k) & 1) continue;
						if (cnt1 > 0 && cnt0 - cnt1 > 0) {//如果要选的点与上一个点之间的两段都有选过的点，则一定可以与一条线段相交
							f[i | (1 << k)][k] += f[i][j];
						}
					}
				}
			}
		}
		LL Ans = 0;
		for (int i = 0; i < n; ++i) {//统计答案
			if ((i + 1) % n != points[0] - 1 && (points[0]) % n != i) {
				Ans += f[N - 1][i];
			}
		}
		return Ans;
    }
};

