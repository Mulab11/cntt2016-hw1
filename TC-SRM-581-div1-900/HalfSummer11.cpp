#line 2 "YetAnotherBoardGame.cpp"
#include<vector>
#include<list>
#include<map>
#include<set>
#include<deque>
#include<stack>
#include<bitset>
#include<algorithm>
#include<functional>
#include<numeric>
#include<utility>
#include<sstream>
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<cstring>
#define cl(x) memset(x, 0, sizeof(x));
#define pii pair<int, int>
#define fr first
#define sc second
#define mp make_pair
#define pb push_back
#define oo 0x3f3f3f3f
#define maxn 15
typedef long long ll;
using namespace std;
/*
   枚举第一行的操作情况。接着，每一行所操作的格子集合都可以由上一行依然为白的格子确定，只需要确定当前行采用哪种type的操作。
   dfs的复杂度是O(3 ^ m)的。假设第一行操作了i个格子，这i个列的操作种类就已经确定了，剩下来的m - i个列最多产生2 ^ (m - i)个分支。总的复杂度就是\sum_{i = 0}^{m} C(m, i) 2 ^ (m - i) = \sum_{i = 0}^m C(m, i) * 2 ^ m, 相当于是枚举了所有子集的子集，复杂度就是O(3 ^ m).
*/
int n, m, ans; // n,m是棋盘的行数和列数
int a[maxn][maxn], col[maxn]; // a[][]记录当前棋盘的情况，col[i]记录第i列的种类：第一种操作/第二种操作/暂未确定
void flip(int x, int y, int k) { // 对于位置(x, y)进行type (k + 1) 这个操作
	if (k) a[x][y] ^= 1;
	if (x > 0) a[x - 1][y] ^= 1;
	if (x < n - 1) a[x + 1][y] ^= 1;
	if (y > 0) a[x][y - 1] ^= 1;
	if (y < m - 1) a[x][y + 1] ^= 1;
}
void dfs(int now, int sta, int cnt) { // now是当前要操作的列，sta是到目前为止每一列的使用情况，cnt是目前使用的操作次数
	if (now == n) { // 已经操作完了
		bool flag = 1;
		for (int j = 0; j < m; ++j)
			if (a[now - 1][j]) flag = 0; // 需要都是黑色的
		if (flag) ans = min(ans, cnt);
		return;
	}
	for (int k = 0; k <= 1; ++k) { // 枚举当前行的操作种类
		bool flag = 1;
		int tmp = sta;
		for (int i = 0; i < m; ++i) 
			col[i] = tmp % 3, tmp /= 3;
		for (int j = 0; j < m; ++j)
			if (a[now - 1][j] && (col[j] != k + 1 && col[j] != 0))  // 当前操作不合法
				flag = 0;
		if (!flag) continue;
		int ext = 0, mod = 0;
		for (int j = 0; j < m; ++j)
			if (a[now - 1][j]) {
				flip(now, j, k); col[j] = k + 1; ++ext; // 进行对应操作，并且对列的状况 / 使用次数 进行修改
				mod |= (1 << j);
			}
		int nsta = 0;
		for (int j = m - 1; j >= 0; --j)
			nsta = nsta * 3 + col[j];
		dfs(now + 1, nsta, cnt + ext);
		for (int j = 0; j < m; ++j)
			if (mod & (1 << j))
				flip(now, j, k); // 复原
	}
}
class YetAnotherBoardGame {
	public:
		int minimumMoves(vector <string> board) {
			n = board.size(); m = board[0].size();
			ans = oo;
			for (int k = 0; k <= 1; ++k) { // 枚举第一行的操作种类
				for (int s = 0; s < (1 << m); ++s) { // 枚举第一行进行操作的格子集合
					for (int i = 0; i < n; ++i)
						for (int j = 0; j < m; ++j)
							a[i][j] = (board[i][j] == 'W');
					cl(col);
					for (int i = 0; i < m; ++i)
						if (s & (1 << i)) {
							col[i] = k + 1;
							flip(0, i, k);
						}
					int sta = 0;
					for (int i = m - 1; i >= 0; --i)
						sta = sta * 3 + col[i];
					dfs(1, sta, __builtin_popcount(s)); 
				}
			}
			return (ans == oo) ? -1 : ans;
		}
};
