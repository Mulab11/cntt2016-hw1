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

const int maxn = 255;
const int maxm = 55;
const int mod = 100007;
const double pi = acos(-1.0);

class FencingPenguins {
public:
	int n;
	struct Point
	{
		double x, y;
		Point() {}
		Point(double _x, double _y):x(_x), y(_y) {}
		Point operator - (const Point &b) const
		{
			return Point(x - b.x, y - b.y);
		}
	}c[maxn], pe[maxm];//变量具体解释在出现的对应程序段中标注
	int rep[maxn], rep_count = 0;
	bitset<maxm> mask[maxn][maxn], cmask[maxn][maxn];
	bool ban[maxn][maxn];
	int h[maxn][maxn][2];
	int f[maxn][maxn];
	int g[maxn][maxn];

	double Cross(const Point &a, const Point &b)
	{
		return a.x * b.y - a.y * b.x;
	}

	int Dynamic_programming()
	{
		bool contain;
		bitset<maxm> downres;
		int front;
		for (int i = 0; i + 1 < n; ++i) {
			f[i][i + 1] = 1;
		}
		for (int L = 3; L <= n; ++L) {
			for (int l = 0; l + L - 1 < n; ++l) {
				int r = l + L - 1;
				//calculate h[][][]
				//h[l][r][k]表示标号在[l~r]之间的所有点，要求必须有一个多边形的一条边为l-r，且这个多边形(k=0/1)是否包含至少一个企鹅的方案数
				for (int i = l + 1; i < r; ++i) {//枚举出l之外的最小顶点
					if (ban[l][i]) continue;
					contain = ((mask[l][i] & mask[i][r] & mask[r][l]).any() > 0);//front表示这个顶点之前，即[l+1~i-1]的方案数
					if (i == l + 1) {//什么都没有
						front = 1;
					}
					else if (i == l + 2) {
						if ((mask[l][l + 1] & mask[l + 1][l + 2] & mask[l + 2][l]).any() == 0) {//如果空档地区无企鹅则合法
							front = 1;
						}
						else front = 0;
					}
					else {
						if ((mask[l][l + 1] & mask[l + 1][i - 1] & mask[i - 1][i] & mask[i][l]).any() == 0) {//如果空档地区无企鹅则合法
							front = f[l + 1][i - 1];
						}
						else front = 0;
					}
					if (i == r - 2) {//这里计算顶点之后的方案
						if ((mask[i][i + 1] & mask[i + 1][r] & mask[r][i]).any() == 0 && !ban[i][r]) {//之后不放
							(h[l][r][contain] += front) %= mod;
						}
						(h[l][r][contain] += (LL)h[i][r][0] * front % mod) %= mod;//将本多边形延续出去
						(h[l][r][contain | 1] += (LL)h[i][r][1] * front % mod) %= mod;
					}
					else if (i == r - 1) {
						if (!ban[i][r]) {
							(h[l][r][contain] += front) %= mod;//不放
						}
					}
					else {
						if ((mask[i][i + 1] & mask[i + 1][r - 1] & mask[r - 1][r] & mask[r][i]).any() == 0 && !ban[i][r]) {//结束本多边形，开始新的多边形
							(h[l][r][contain] += (LL)f[i + 1][r - 1] * front % mod) %= mod;
						}
						(h[l][r][contain] += (LL)h[i][r][0] * front % mod) %= mod;//将本多边形延续出去
						(h[l][r][contain | 1] += (LL)h[i][r][1] * front % mod) %= mod;
					}
				}
				//calculate g[][]
				//g[l][r]表示标号在[l~r]之间的所有点，且要求有一个多边形的一个顶点为l的方案数
				for (int i = l + 1; i <= r; ++i) {//枚举l顶点所在的多边形的最后一个顶点
					if (i == r) {
						if (!ban[r][l]) {//一边不放，一边确定了两个顶点
							(g[l][r] += h[l][r][1]) %= mod;
						}
					}
					else if (i == r - 1) {
						if ((mask[l][i] & mask[i][r] & mask[r][l]).any() == 0 && !ban[r - 1][l]) {//一边不放，一边确定了两个顶点
							(g[l][r] += h[l][i][1]) %= mod;
						}
					}
					else {
						if ((mask[l][i] & mask[i][i + 1] & mask[i + 1][r] & mask[r][l]).any() == 0 && !ban[i][l]) {//一边进入子问题，一边确定了两个顶点
							(g[l][r] += (LL)h[l][i][1] * f[i + 1][r] % mod) %= mod;
						}
					}
				}
				//calculate f[][]
				//f[l][r]表示标号在[l~r]之间的所有点，不放任何多边形或者放入任意多边形满足题目要求的方案数，最后答案为f[0][n - 1]
				downres.set();
				for (int i = l; i < r; ++i) downres = downres & mask[i][i + 1];
				downres = downres & mask[r][l];
				if (downres.any() == 0) f[l][r] = 1;//如果这个范围内已经为空，则只有不放任何多边形一种情况
				else {
					downres.set();
					for (int i = l; i < r; ++i) {//枚举标号最小的属于一个多边形的标号
						if (i == l) downres = downres & mask[r][l];
						else downres = downres & mask[i - 1][i];
						if ((downres & mask[i][r]).any()) break;
						if (i == r - 1) {//不放
							(f[l][r] += 1) %= mod;
						}
						else {//确定了一个顶点，进入g[i][r]
							(f[l][r] += g[i][r]) %= mod;
						}
					}
				}
			}
		}
		return f[0][n - 1];//返回答案
	}
	
    int countWays(int numPosts, int radius, vector<int> x, vector<int> y, string color) {
		double ang = 0;
		n = numPosts;
		rep_count = 0;//颜色计数器
		memset(rep, -1, sizeof(rep));
		for (int i = 0; i < color.length(); ++i) {//将字符颜色与标号颜色建立对应关系
			if (rep[color[i]] == -1) {
				rep[color[i]] = rep_count++;
			}
		}
		for (int i = 0; i < numPosts; ++i, ang += pi * 2 / numPosts) {//求出每个围栏的点的坐标
			c[i] = Point(cos(ang) * radius, sin(ang) * radius);
		}
		for (int i = 0; i < x.size(); ++i) {//每只且企鹅的坐标
			pe[i] = Point(x[i], y[i]);
		}
		for (int i = 0; i < numPosts; ++i) {
			for (int j = 0; j < numPosts; ++j) {
				if (i == j) continue;
				mask[i][j].reset();//mask[i][j]表示从i到j的有向直线的左侧有那些点
				cmask[i][j].reset();//cmask[i][j]表示从i到j的有向直线的左侧有那些颜色
				for (int k = 0; k < x.size(); ++k) {
					if (Cross(c[j] - c[i], pe[k] - c[i]) > 0) {//用叉积求出mask和cmask
						mask[i][j][k] = 1;
						cmask[i][j][rep[color[k]]] = 1;
					}
				}
			}
		}
		memset(ban, 0, sizeof(ban));//ban[i][j]如果为1表示从i到j的有向直线将同一种颜色的企鹅分成了两个部分，所以不能选i,j之间的线段
		for (int i = 0; i < numPosts; ++i) ban[i][i] = 1;
		for (int i = 0; i < numPosts; ++i) {
			for (int j = i + 1; j < numPosts; ++j) {
				if ((cmask[i][j] & cmask[j][i]).any()) {//检查两边是否有同种颜色的企鹅
					ban[i][j] = ban[j][i] = 1;
				}
			}
		}
		for (int i = 0; i < n; ++i) {//如果有企鹅在围栏之外，无解
			if (mask[i][(i - 1 + n) % n].any()) {
				return 0;
			}
		}
		return Dynamic_programming();//动态规划求答案
    }
};

