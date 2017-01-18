#line 2 "FencingPenguins.cpp"
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
#define maxn 230
#define maxm 60
#define pi M_PI
#define eps 1e-9
#define mo 100007
typedef long long ll;
using namespace std;
int n, m, num[maxn][maxn], sum[maxn][maxn]; // n是点数，m是企鹅数，num[i][j]表示三角形0ij中的企鹅个数，sum[i][j]表示\sum_{k = i}^{j - 1} num[k][k + 1]
int numc[maxn][maxn][maxm], sumc[maxn][maxn][maxm]; // numc[i][j][c], sumc[i][j][c]是只考虑颜色为c的企鹅时的num与sum
bool cut[maxn][maxn], empty[maxn][maxn]; // cut[i][j]表示线段ij作为围栏的一部分，是否会把同种颜色的企鹅分开。empty[i][j]表示线段ij与弧ij之间的部分是否没有企鹅
int g[maxn][maxn][2], piece[maxn][maxn]; // g[s][t][0/1]表示从s开始围多边形，一路围到t，目前围住的面积里没有/有企鹅，点s到t之间设置围栏的方案数。piece[i][j]表示线段ij与弧ij之间的部分设置围栏的方案数
double px[maxn], py[maxn]; // px[i], py[i]是i号点的坐标
void add(int &a, int b) {
	a += b; a %= mo;
}
int dcmp(double x) { // 实数的符号
	return fabs(x) < eps ? 0 : x > 0 ? 1 : -1;
}
int cross(double x1, double y1, double x2, double y2) { // 叉积的符号
	return dcmp(x1 * y2 - x2 * y1);
}
int trans(char c) { // 处理颜色
	if (c >= 'a' && c <= 'z') return c - 'a';
	return c - 'A' + 26;
}
class FencingPenguins {
	public:
		int countWays(int numPosts, int r, vector <int> x, vector <int> y, string color) {
			cl(num); cl(sum); cl(cut); cl(empty); cl(g); cl(piece); cl(numc); cl(sumc);
			n = numPosts; m = x.size();
			for (int i = 0; i < n; ++i) { // 计算点的位置
				double ang = 2.0 * pi / n * i;
				px[i] = 1.0 * r * cos(ang);
				py[i] = 1.0 * r * sin(ang);
			}
			for (int i = 0; i < n; ++i) 
				for (int j = i + 1; j < n; ++j) {
					for (int k = 0; k < m; ++k) {
						if ((cross(px[j] - px[i], py[j] - py[i], x[k] - px[i], y[k] - py[i]) > 0) && 
								cross(px[i] - px[0], py[i] - py[0], x[k] - px[0], y[k] - py[0]) > 0 && 
								cross(x[k] - px[0], y[k] - py[0], px[j] - px[0], py[j] - py[0]) > 0)
							++numc[i][j][trans(color[k])], --numc[j][i][trans(color[k])]; // 计算第k只企鹅是否被这个三角形包含
					}
				}
			for (int i = 0; i < n; ++i)
				for (int j = (i + 1) % n; j != i; j = (j + 1) % n)
					for (int k = 0; k < 52; ++k)
						sumc[i][j][k] = sumc[i][(j + n - 1) % n][k] + numc[(j + n - 1) % n][j][k]; // 求sum
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < n; ++j)
					for (int k = 0; k < 52; ++k)
						num[i][j] += numc[i][j][k], sum[i][j] += sumc[i][j][k];
			if (sum[0][n - 1] + num[n - 1][0] < m) return 0; // 有些企鹅永远围不住
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < n; ++j) {
					if (i == j) continue;
					empty[i][j] = (sum[i][j] + num[j][i] == 0); // 弓形内的企鹅数是否为0
				}
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < n; ++j) {
					if (i == j) continue;
					cut[i][j] = 1;
					for (int k = 0; k < 52; ++k)
						if (sumc[i][j][k] + numc[j][i][k] > 0 && sumc[j][i][k] + numc[i][j][k] > 0) {
							cut[i][j] = 0; break; // 存在一种颜色的企鹅两边都有，这种围栏就是不合法的
						}
				}
			for (int len = 1; len < n; ++len) { // 枚举两点距离len
				for (int i = 0; i < n; ++i) { // 起点i
					int j = (i + len) % n;
					if (empty[i][j]) 
						piece[i][j] = 1; // 一种方案:不设置围栏
					else {
						if (num[i][(i + 1) % n] + num[(i + 1) % n][j] + num[j][i] == 0) // (i + 1) % n这个点不用，这个三角形内必须是空的
							add(piece[i][j], piece[(i + 1) % n][j]);
						for (int mid = (i + 2) % n; mid != j; mid = (mid + 1) % n) { // (i + 1) % n这个点用，并且所在多边形里最靠近j的点为mid
							if (num[mid][j] + num[j][i] + num[i][(i + 1) % n] + num[(i + 1) % n][mid] == 0) // 这部分永远不能被围住了，需要是空的
								add(piece[i][j], 1ll * cut[mid][(i + 1) % n] * g[(i + 1) % n][mid][1] * piece[mid][j] % mo); // g确定(i + 1) % n的多边形。piece确定剩下的部分
						}
					}
				}
				for (int s = 0; s < n; ++s) { // 起点s
					int t = (s + len) % n; // 终点t
					g[s][t][0] = 1ll * piece[s][t] * cut[s][t] % mo; // 直接来一刀s->t
					for (int mid = (s + 1) % n; mid != t; mid = (mid + 1) % n) { // 枚举t之前的点mid
						if (!cut[mid][t]) continue; // 砍mid -> t需要是合法的
						int delta = (num[s][mid] + num[mid][t] + num[t][s] > 0); // 新围住的三角形内是否有企鹅
						for (int k = 0; k < 2; ++k)
							add(g[s][t][min(1, k + delta)], 1ll * g[s][mid][k] * piece[mid][t] % mo);
					}
				}
			}
			int ans = 0;
			ans = 0;
			for (int s = 1; s < n; ++s) // 不使用顶点0，枚举被用到的编号最小的点s
				for (int t = s + 1; t < n; ++t) { // 枚举它所在的多边形中编号最大的点t
					add(ans, 1ll * cut[s][t] * g[s][t][1] * empty[t][s] % mo); // 一种情况：s -> t左侧是空的
					if (!empty[t][s] && num[s][t] + num[t][0] + sum[0][s] == 0) // 否则，由于s是被用到的最小的点，这一块区域都不能被围到了，需要是空的
						add(ans, 1ll * cut[s][t] * g[s][t][1] * piece[t][0] % mo); // 剩下可能被使用的点局限在piece[t][0]内
				}
			for (int t = 1; t < n; ++t) // 使用顶点0，枚举所在多边形里编号最大的点t
				add(ans, 1ll * cut[0][t] * g[t][0][1] * piece[0][t] % mo);
			return ans;
		}
};

