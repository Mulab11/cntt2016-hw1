#line 2 "TreeUnion.cpp"
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
#define maxn 310
typedef long long ll;
using namespace std;
/*
   K <= 7, 环只能由两条分别位于两棵树上的路径接成。统计每棵树上每种长度路径的条数，枚举两边路径的长度算一算。
*/
int n, f[2][maxn]; // n是树的点数，f[i][j]存第i棵树上长度为j的路径条数
int read(string s, int &pos) { // 从s的pos处开始读数字
	int len = s.length(), x = 0;
	while (pos < len && (s[pos] < '0' || s[pos] > '9')) ++pos;
	while (pos < len && s[pos] >= '0' && s[pos] <= '9')
		x = x * 10 + s[pos] - '0', ++pos;
	return x;
}
int g[maxn], ei, dep[maxn]; // 边表 / 深度数组
struct edge {
	int t, nxt;
}e[maxn * 2];
void ae(int a, int b) {
	e[++ei].t = b; e[ei].nxt = g[a]; g[a] = ei;
}
void dfs(int x, int fa) { // 处理dep[]
	for (int i = g[x]; i; i = e[i].nxt)
		if (e[i].t != fa) {
			dep[e[i].t] = dep[x] + 1;
			dfs(e[i].t, x);
		}
}
void calc(int f[maxn], vector <string> tree) { // 统计tree里存的树中，每种长度的路径条数，存在f[]里
	string all = "";
	for (int i = 0; i < tree.size(); ++i) all = all + tree[i];
	n = 1; int u, pos = 0, len = all.length();
	cl(g); ei = 0;
	while (pos < len) {
		u = read(all, pos) + 1;
		++n;
		ae(n, u); ae(u, n);
	}
	for (int i = 1; i <= n; ++i) {
		dep[i] = 0; dfs(i, -1); // 统计以每个点为一端的路径条数
		for (int j = 1; j <= n; ++j)
			++f[dep[j]];
	}
	for (int i = 1; i <= n; ++i)
		f[i] /= 2; // 每条路径被算了两遍
}
class TreeUnion {
	public:
		double expectedCycles(vector <string> tree1, vector <string> tree2, int K) {
			cl(f);
			calc(f[0], tree1);
			calc(f[1], tree2);
			K -= 2;
			double ans = 0;
			for (int a = 1; a <= K - 1; ++a) { // 枚举Tree1中路径的长度a
				int b = K - a;
				if (a >= n || b >= n) continue;
				ans += 2.0 * f[0][a] * f[1][b] / (n - 1) / n; // 两条路径有两种方法结成环，除了路径端点外的点可以任选P[i],所以这个环在(n - 2)!种排列中出现
			}
			return ans;
		}
};
