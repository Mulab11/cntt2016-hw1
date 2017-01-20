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

const int maxn = 3e3+115;

int W;
int boundary;

bool Dfs(int fr, int bh, int p)
{
	int total = fr + bh + 1;
	int nx, ny, lx, ly, det;
	if (total <= W && (fr == 0 || bh == 0)) return 1;
	if (fr == W - 1 && bh <= W - 1) return 1;
	if (bh == 0 && total % W == 1) return 1;
	if (W == 1 && (fr == 0 || bh == 0)) return 1;//判断是否可以一步达到
	if (p >= boundary) return 0;
	nx = fr / W + 1; ny = fr + 1 - (nx - 1) * W;
	lx = (total - 1) / W + 1; ly = total - (lx - 1) * W;
	if (Dfs(fr, nx * W - fr - 1, p + 1)) return 1;//如果只删除x后面的部分，显然删除越多越好
	for (int i = 1; i < nx; ++i) {//如果删除上面部分，枚举删除的元素的个数
		for (int j = 1; j <= W; ++j) {
			if (Dfs(fr - i * j, bh, p + 1)) {
				return 1;
			}
		}
	}
	det = 0;
	for (int j = 1; j + ny <= W; ++j) {//如果删除右侧，枚举删除的之前的元素的个数，之后的元素贪心删除最多
		det += (ly >= ny + j) + lx - nx;
		for (int i = 1; i < nx; ++i) {
			if (Dfs(fr - i * j, bh - det, p + 1)) {
				return 1;
			}
		}
	}
	det = 0;
	for (int j = 1; ny - j >= 1; ++j) {//左侧与右侧相同
		det += (ly >= ny - j) + lx - nx - 1;
		for (int i = 1; i <= nx; ++i) {
			if (Dfs(fr - i * j, bh - det, p + 1)) {
				return 1;
			}
		}
	}
	return 0;
}

class FoxAndAvatar {
    public:
    int minimalSteps(int n, int width, int x) {
		W = width;//答案上界为4
		if (n == 1) return 0;//特殊判断
		for (int i = 1; i <= 3; ++i) {//迭代加深搜索
			boundary = i;
			if (Dfs(x - 1, n - x, 1)) return i;
		}
        return 4;
    }
};
