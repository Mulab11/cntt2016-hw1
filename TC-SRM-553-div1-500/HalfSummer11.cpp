#line 2 "TwoConvexShapes.cpp"
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
// 由于每种颜色的格子在行/列上连续，对于每行，只要确定黑白的界线，然后，保证所有行的这个界线是不升/不降的就可以了。
bool g[maxn][maxn]; // g[i][j] 表示第i行是否可以填成前j个为一种颜色，后m-j个另一种颜色
int ans, n, m, f[maxn][maxn]; // f[i][j]表示放到第i行，分界线在j处，有几种方案
void add(int &a, int b) {
	a += b; a %= mo;
}
void calc(vector <string> grid, char c1, char c2) {
	cl(g);
	for (int i = 1; i <= n; ++i) {
		g[i][0] = 1;
		for (int j = 1; j <= m; ++j) 
			g[i][j] = (g[i][j - 1] && grid[i - 1][j - 1] != c1); // 前j个不能出现另一种颜色
		bool flag = 1;
		for (int j = m - 1; j >= 0; --j) {
			flag &= (grid[i - 1][j] != c2);
			g[i][j] &= flag; // 后m - j个不能出现第一种颜色
		}
	}
	bool flag;
	for (int i = 1; i <= n; ++i) { // 若干行全黑，若干行全白的情况，在B从左边/B从右边开始延伸的情况中，都会被计算到。将上面若干行全黑的情况在calc(W,B)中去掉，将上面若干行全白的情况在calc(B,W)中去掉
		flag = 1;
		for (int j = 1; j <= i; ++j)
			flag &= g[j][m];
		for (int j = i + 1; j <= n; ++j)
			flag &= g[j][0];
		if (flag) add(ans, mo - 1);
	}
	cl(f);
	f[0][0] = 1; // 计算分界线从上到下不降的情况
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j <= m; ++j)
			if (g[i][j])
				for (int k = 0; k <= j; ++k)
					add(f[i][j], f[i - 1][k]);
	for (int j = 0; j <= m; ++j) 
		add(ans, f[n][j]);
	cl(f);
	f[0][m] = 1; // 计算分界线从上到下不升的情况
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j <= m; ++j)
			if (g[i][j]) 
				for (int k = j; k <= m; ++k)
					add(f[i][j], f[i - 1][k]);
	for (int j = 0; j <= m; ++j) 
		add(ans, f[n][j]);
	for (int j = 0; j <= m; ++j) { // 分解线从上到下都一样的情况被计算了两次，这里去掉
		flag = 1;
		for (int i = 1; i <= n; ++i)
			if (!g[i][j]) { 
				flag = 0; break; 
			}
		if (flag) add(ans, mo - 1);
	}
}
class TwoConvexShapes {
	public:
		int countWays(vector <string> grid) {
			n = grid.size(); m = grid[0].size();
			ans = 0;
			calc(grid, 'W', 'B'); // 计算B从最左边开始延伸的情况
			calc(grid, 'B', 'W'); // 计算W从最左边开始延伸的情况
			return ans;
		}
};


