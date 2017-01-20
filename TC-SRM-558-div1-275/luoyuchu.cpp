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

int n;
int f[maxn];//dp数组
int ys[maxn * 7];//映射表，将'R','G','B','*'表示为1,2,3,0

class Stamp {
    public:
    int getMinimumCost(string dc, int stampCost, int pushCost) {
		int Ans = 2e9;
		n = dc.length();
		ys['R'] = 1;
		ys['G'] = 2;
		ys['B'] = 3;
		ys['*'] = 0;
		for (int L = 1; L <= n; ++L) {//枚举刷子长度
			memset(f, 0x3f, sizeof(f));
			f[0] = 0;
			for (int i = 0; i < n; ++i) {//从f[i]转移到f[j]
				int hc = 0;
				for (int j = i + 1; j <= n; ++j) {//条件是[i,j]中只有小于等于一种的颜色
					if (hc == 0) hc = ys[dc[j - 1]];
					else if (ys[dc[j - 1]] != 0 && ys[dc[j - 1]] != hc) {
						break;
					}
					if (j - i >= L) {
						Ckmin(f[j], f[i] + (j - i + L - 1) / L);
					}
				}
			}
			if (f[n] <= n) {//更新最小值
				Ckmin(Ans, f[n] * pushCost + stampCost * L);
			}
		}
        return Ans;//返回答案
    }
};


