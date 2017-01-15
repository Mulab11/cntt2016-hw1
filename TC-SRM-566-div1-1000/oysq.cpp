#line 2 "FencingPenguins.cpp"  
#include <bits/stdc++.h> 

using namespace std;  

#define ui unsigned
#define ll long long

#define pii std::pair<int,int>
#define mp std::make_pair
#define fi first
#define se second

#define SZ(x) (int)(x).size()
#define pb push_back

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(x > y) x = y;}

const int N = 222;
const int MOD = 100007;
const double pi = acos(-1.0);

int n, m;// n个圆周点，m个内部企鹅
double cx[N + 9], cy[N + 9];// 圆周上的点的坐标
ll mask[N + 9][N + 9];// mask[i][j] 表示向量 i -> j 左边的点集
ll cmask[N + 9][N + 9];// cmask[i][j] 表示向量 i -> j 左边的颜色集
bool vld[N + 9][N + 9];// vld[i][j] = true表示边(i, j)可以选，不会将一种颜色分成两部分

int h[N + 9][N + 9][2];// h[i][j][1] 表示之前已经有企鹅被包括的情况下，(i, j)边必选，区间[i, j]的方案数，0表示没有企鹅被包括
int g[N + 9][N + 9];// g[i][j] 表示点i必须被连边的情况下，区间[i, j]的方案数
int f[N + 9][N + 9];// f[i][[j] 表示区间[i, j]的方案数

int det(double x1, double y1, double x2, double y2, double x3, double y3) {// = 1 表示三个点逆时针，= -1 表示顺时针，否则共线
	double a = x1 - x3, b = y1 - y3, c = x2 - x3, d = y2 - y3, r = a * d - b * c;
	if(r > 0) return 1;
	else if(r < 0) return -1;
	else return 0;
}

int getcolorid(char c) {// 将颜色离散出来
	if(c >= 'a' && c <= 'z') return c - 'a';
	else return c - 'A' + 26;
}

class FencingPenguins {  
public:  
	int countWays(int numPosts, int radius, vector <int> x, vector <int> y, string color) {  
		n = numPosts, m = SZ(x);

		// 算出圆周上每个点的坐标
		for(int i = 0; i < n; ++i)
			cx[i] = radius * cos(2 * pi / n * i), cy[i] = radius * sin(2 * pi / n * i);

		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				for(int k = 0; k < m; ++k)
					if(det(cx[i], cy[i], cx[j], cy[j], x[k], y[k]) == 1) {
						mask[i][j] |= 1ll << k;
						cmask[i][j] |= 1ll << getcolorid(color[k]);
					}

		// 判断是否有点在最大的多边形外
		for(int i = 0; i < n - 1; ++i)
			if(mask[i + 1][i])
				return 0;
		if(mask[0][n - 1])
			return 0;

		// 计算vld
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				vld[i][j] = !(cmask[i][j] & cmask[j][i]);

		for(int i = 0; i < n; ++i)
			h[i][i][1] = 1;
		for(int l = 1; l < n; ++l)
			for(int i = 0; i + l < n; ++i) {
				int j = i + l;

				// 计算h
				for(int d = 0; d < 2; ++d)
					for(int k = i + 1; k <= j; ++k)
						if(vld[i][k]) {// 选的边必须合法
							ll in = mask[i][k] & mask[k][j] & mask[j][i];// 判断三角形ikj内部有没有企鹅
							int p = h[k][j][in ? 1 : d];
							if(!mask[k][i])
								(h[i][j][d] += p) %= MOD;// 如果没有，那么不需要管
							else if(k >= i + 4) {
								if(mask[k][i] & mask[i + 1][k - 1])// 如果有，那么向量i -> k和向量k - 1, i + 1围住的区域不能有企鹅
									continue;
								(h[i][j][d] += (ll)p * f[i + 1][k - 1] % MOD) %= MOD;// 将两个独立的方案乘起来
							}
						}

				// 计算g
				for(int k = i + 2; k <= j; ++k)// 枚举i所在的多边形的最后一条边
					if(vld[i][k]) {// 选的边必须合法
						ll in = mask[i][k] & mask[j][i];// 判断角kij范围内有没有点
						int p = h[i][k][0];
						if(!in)
							(g[i][j] += p) %= MOD;// 没有的话，不需要放多边形
						else if(k + 3 <= j) {
							in &= mask[k + 1][j];
							if(!in)// i -> k, k + 1 -> j, j - > i三条线围住的区域无法覆盖，不能有企鹅
								(g[i][j] += (ll)p * f[k + 1][j] % MOD) %= MOD;
						}
					}

				// 计算f
				for(int k = i; k < j; ++k) {// 枚举第一个被用的点
					if(mask[j][i] & mask[k][j]) continue;// j -> i, k -> j围住的区域无法被覆盖，不能有点
					(f[i][j] += g[k][j]) %= MOD;
				}
			}

		return f[0][n - 1];
	}  
};  
