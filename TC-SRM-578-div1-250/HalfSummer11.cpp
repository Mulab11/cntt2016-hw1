#line 2 "GooseInZooDivOne.cpp"
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
#define maxn 60
#define mo 1000000007
typedef long long ll;
using namespace std;
/* 
   在曼哈顿距离不超过dist的点之间连边，一个连通块里要么都是geese，要么都是duck。简单dp一下就能求出geese个数为偶数且非0的方案数。
*/
int n, m, cnt, D; // n, m是矩形的长宽，cnt是连通块个数, D = dist
bool bird[maxn][maxn], vis[maxn][maxn]; // bird[i][j] = 1 <==> (i, j)处有鸟。vis[i][j] = 1 <==> (i, j)处已经dfs到
int size[maxn * maxn]; // size[i]表示第i个连通块的大小
void dfs(int x, int y) { // 从(x, y)开始dfs连通块
	vis[x][y] = 1; ++size[cnt];
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			if (abs(i - x) + abs(j - y) <= D && bird[i][j] && !vis[i][j]) 
				dfs(i, j);
}
int f[maxn * maxn][2]; f[i][j]表示从前i个连通块中选出若干个，使得选出的点数奇偶性为j的方案数。
void add(int &a, int b) {
	a += b; a %= mo;
}
class GooseInZooDivOne {
	public:
		int count(vector <string> field, int dist) {
			cl(bird); cl(vis);
			D = dist; n = field.size(); m = field[0].size();
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < m; ++j)
					if (field[i][j] == 'v')
						bird[i][j] = 1;
			cnt = 0; cl(size);
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < m; ++j)
					if (bird[i][j] && !vis[i][j]) {
						++cnt; dfs(i, j); // dfs出所有的连通块
					}
			cl(f);
			f[0][0] = 1;
			for (int i = 1; i <= cnt; ++i) 
				for (int j = 0; j <= 1; ++j) {
					add(f[i][j], f[i - 1][j]);
					add(f[i][j ^ (size[i] % 2)], f[i - 1][j]);
				}
			int ans = f[cnt][0];
			add(ans, mo - 1); // 去掉没有goose的情况
			if (cnt == 1 && size[cnt] % 2 != 0) return 0; // 无解的情况：只有一个大小为奇数的连通块
			return ans;
		}
};
