#line 2 "Orienteering.cpp"
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
#define maxn 2510
#define maxc 310
#define maxm 60
typedef long long ll;
using namespace std;
const int dx[] = {0, 1, 0, -1}; // 向四个方向移动
const int dy[] = {1, 0, -1, 0};
int n, m, r, c, num[maxm][maxm]; // n是总结点数，m是*节点数，r/c是棋盘的尺寸，num[i][j]表示棋盘上(i, j)位置的点的编号
int w[maxn], sum[maxn]; // w[i]为1，表示第i个点是*点，sum[i]是dfs序在1 - i范围内的点的w之和，即这些点中*点的个数
int g[maxn], ei, dfn[maxn], dcnt, pre[maxn]; // g,ei是边表部分，dfn[i]是以1为根时，i点的dfs序，dcnt是目前dfs过的节点个数，pre[i]是i点在树上的父亲
double C[maxc][maxc]; // 组合数
int seq[maxn], tot; // seq存枚举的两点l, r间的所有点，tot是这条直径上的点的个数
bool vis[maxn]; // 标记一个点是否被访问过
struct edge {
	int t, nxt;
}e[maxn * 4];
void ae(int a, int b) {
	e[++ei].t = b; e[ei].nxt = g[a]; g[a] = ei;
}
void dfs(int x, bool d) { // dfs整棵树，处理dfn和pre。d表示这次dfs是否需要处理dfn
	if (d) { dfn[x] = ++dcnt; sum[dcnt] = w[x]; }
	for (int i = g[x]; i; i = e[i].nxt)
		if (e[i].t != pre[x]) {
			pre[e[i].t] = x;
			dfs(e[i].t, d);
		}
}
int count(int x, int lim, bool sidea, int a, int b) { // 计算以x为根的子树里，到x距离不超过lim的*点的个数，其中，若某个*点y距离x恰为lim，还要根据这个点的编号与a，b的关系，以及sidea的值来确定是否计入答案
	if (lim < 0) return 0;
	int ret = 0;
	if (w[x]) {
		if (x < a) ret = (lim > 0); // 根据x与a/b编号的大小关系来判断是否计入答案
		if (a < x && x < b) {
			if (sidea) ret = 1; else ret = (lim > 0);
		}
		if (x > b) ret = 1;
	}
	for (int i = g[x]; i; i = e[i].nxt)
		if (!vis[e[i].t]) {
			vis[e[i].t] = 1;
			ret += count(e[i].t, lim - 1, sidea, a, b); // 累加子树中的点数
		}
	return ret;
}
class Orienteering {
	public:
		double expectedLength(vector <string> field, int K) {
			n = m = 0; r = field.size(); c = field[0].size();
			cl(w); cl(num);
			for (int i = 0; i < r; ++i)
				for (int j = 0; j < c; ++j) // 将树上的点找出来
					if (field[i][j] != '#') {
						num[i][j] = ++n;
						if (field[i][j] == '*')
							w[n] = 1, ++m;
					}
			cl(g); ei = 0;
			for (int i = 0; i < r; ++i)
				for (int j = 0; j < c; ++j)
					if (num[i][j])
						for (int d = 0; d < 4; ++d) {
							int nx = i + dx[d], ny = j + dy[d];
							if (nx < 0 || ny < 0 || nx >= r || ny >= c || !num[nx][ny]) continue;
							ae(num[i][j], num[nx][ny]); // 连树边
						}
			dcnt = 0; cl(dfn); cl(pre); cl(sum);
			dfs(1, 1); // 处理dfs序
			for (int i = 1; i <= n; ++i)
				sum[i] += sum[i - 1]; // 做前缀和，用于查询某个dfs序区间里*点的个数
			for (int i = 0; i <= m; ++i) { // 处理组合数
				C[i][0] = 1.0;
				for (int j = 1; j <= i; ++j)
					C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
			}
			double ans = 0;
			for (int l = 1; l <= n; ++l) {
				if (!w[l]) continue;
				cl(pre); dfs(l, 0);
				for (int r = l + 1; r <= n; ++r) { // 枚举一对*点l, r对答案的贡献 : 对于一些选出的点，遍历的最小步数 = dfs序相邻点之间的距离+dfs序头尾两个点之间的距离 - 两个距离最远的点之间的距离. 考虑这对点出现在三种情况中的次数。
					if (!w[r]) continue;
					int mid; double k = 0; // mid是dfs序位于它们之间的点的个数
					if (dfn[l] < dfn[r]) 
						mid = sum[dfn[r] - 1] - sum[dfn[l]];
					else
						mid = sum[dfn[l] - 1] - sum[dfn[r]];
					if (mid >= K - 2)
						k += C[mid][K - 2]; // 当这两个点在选出的点中，分别是dfs序最大/最小的点时，其它点的选择方案数。
					if (m - mid - 2 >= K - 2)
						k += C[m - mid - 2][K - 2]; // 当这两个点在选出的点中，是dfs序相邻的点时，其他点的选择方案数。
					cl(vis); tot = 0;
					int now = r; // 接下来数这对点作为字典序最小的直径时，其它点的选择方案数。实际上不需要遍历整棵树去找合法点，直接枚举所有的*点逐个判断合法性就可以了QAQ这里写蠢了……
					while (now) { // 把l - r作为直径时，直径上的点放到seq里
						seq[++tot] = now;
						vis[now] = 1;
						now = pre[now];
					}
					reverse(seq + 1, seq + tot + 1);
					int cnt = 0;
					for (int i = 1; i <= tot; ++i) {
						int disl = i - 1, disr = tot - i;
						cnt += count(seq[i], min(disl, disr), disl < disr, l, r); // 把直径上的点长出的子树中，合法的*点个数计算出来
					}
					if (cnt >= K - 2) k -= C[cnt][K - 2];
					ans += k / C[m][K] * (tot - 1);
				}
			}
			return ans;
		}
};

