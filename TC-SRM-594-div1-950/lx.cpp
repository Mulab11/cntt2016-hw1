#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define bin(x) (1<<(x))
#define LX_JUDGE

using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

template<typename T> inline void upmax(T &x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T &x, T y) { x > y ? x = y : 0; }

class FoxAndAvatar {
public :
	int W, ans;
	 
	// 有 n 个数，在第 x 个位置，能否一步达目标。  
	bool check(int n, int x) {
		if (x == n - 1 && x % W == 0)
			return 1;
		if (x == 0 && W == 1)
			return 1;
		if (x == n - 1 && x < W)
			return 1;
		if (x == W - 1 && n <= 2 * W - 1)
			return 1;
		if (x == 0 && n <= W)
			return 1;
		return 0;
	}
	 
	void Dfs(int step, int n, int x) {
		if (n == 1) {
			upmin(ans, step);
			return ;
		} 
		if (check(n, x)) {
			upmin(ans, step + 1);
			return ;
		}
		if (step + 2 >= ans)  return ;		//最优性剪枝
		int rows = x / W;			// x 上方有几行
		//up 
		rep (i, 1, rows) {			// 删除 x 上方的数，n 和 x 同时变化，只与删除矩形大小有关，枚举量 O(n)
			rep (j, 1, W) {
				Dfs(step + 1, n - i * j, x - i * j);
			}
		}
		//down						// x 不变的情况下，n 越小越好，删除 x 下方全部删除是更优的，枚举量 O(1)
		int x2;
		int n2 = min(n, (rows + 1) * W);
		Dfs(step + 1, n2, x);
		//left
		n2 = n, x2 = x;
		rep (i, 1, x % W) {			// 删除 x 左边的数，因为 n 越小越好，所以删除的时候一定会删除到最后一行，枚举量 O(n)
			int h = (n - i) / W + 1;
			n2 -= h;
			x2 -= (rows + 1);
			rep (j, 0, rows) {
				Dfs(step + 1, n2 + i * j, x2 + i * j);
			}
		}
		//right
		n2 = n, x2 = x;
		rep (i, 1, W - 1 - x % W) {	// 同 left 的分析。  
			int h = (n - i - x % W - 1 + W) / W;
			n2 -= h;
			x2 -= rows;
			rep (j, 0, rows) {
				Dfs(step + 1, n2 + i * j, x2 + i * j);
			}
		}
	}
	 
	// 搜索：答案的上界为 4，最后一步可以 O(1) check，只需要搜索两步即可。  
	// 复杂度：O(n^2)。
	int minimalSteps(int n, int wid, int x) {
		ans = 4;
		W = wid;
		Dfs(0, n, x - 1);
		return ans;
	}
};
