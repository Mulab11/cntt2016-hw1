#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

int ans = 4, w;
bool one_step(int n, int p)
{
	if((!p || p + 1 == n) && (w == 1 || n <= w)) return 1;	// 一列/行的头尾
	if(p % w == 0 && p + 1 == n) return 1;					// 最后一行唯一
	if(p == w - 1 && n < 2 * w) return 1;					// 最后一列唯一
	return 0;
}
void dfs(int n, int p, int d)
{
	if(d >= ans) return;
	if(n == 1) return (void) (ans = d);
	if(one_step(n, p)) return (void) (ans = d + 1);
	if(d + 2 >= ans) return;
	const int x = p / w, y = p % w;
	// 全部都在上面的，枚举删除的矩形大小即可
	for(int i = 1; i <= x; ++i)
		for(int j = 1; j <= w; ++j)
			dfs(n - i * j, p - i * j, d + 1);
	// 全部都在下面的，显然下面全删掉是最优的，所以保留的是前 x 行
	dfs(min((x + 1) * w, n), p, d + 1);
	// 当 p 不变的时候，n 越小，步数不会更大
	// 全部都在左边，则枚举一个点，把它左下角能删的都删掉
	// 因为对于同一个线段，靠左总比靠右更优
	int N, P; N = n, P = p;
	for(int i = 1; i <= y; ++i)
	{
		N -= (n - i) / w + 1, P -= x + 1;
		for(int j = 0; j <= x; ++j)
			dfs(N + j * i, P + j * i, d + 1);
	}
	N = n, P = p;
	for(int i = 1; i <= w - 1 - y; ++i)
	{
		N -= (n - i - y - 1 + w) / w, P -= x;
		for(int j = 0; j <= x; ++j)
			dfs(N + j * i, P + j * i, d + 1);
	}
}

class FoxAndAvatar
{
public:
	int minimalSteps(int n, int w, int p)
	{
		// 感觉答案不会超过 4 啊
		// 对于一般情况，均可按照下面的顺序删除：
		// 444444444
		// 33333P222
		// 111111111
		::w = w;
		dfs(n, p - 1, 0);
		return ans;
	}
}   user;
