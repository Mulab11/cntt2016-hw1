#include<vector>
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#define pii pair<int, int>
#define fr first
#define sc second
#define mp make_pair
#define pb push_back
#define oo 0x3f3f3f3f
#define maxn 5010
#define eps 1e-9
typedef long long ll;
using namespace std;
vector<pii> means[maxn]; // means[a]存放起点在(0, 0)且长度为a的边的所有合法整数终点
int sum, c;
int mul(int x) { 
	return x * x;
}
int dcmp(double x) {
	return fabs(x) < eps ? 0 : x > 0 ? 1 : -1;
}
bool calc(int x0, int y0, int x, int y, int b, int c) {
	return mul(x) + mul(y) == mul(b) && mul(x - x0) + mul(y - y0) == mul(c);
}
bool check(int x0, int y0, int b, int c) { // 验证一条边为(0, 0) - (x0, y0), 另外两条边长度分别为b与c的三角形是否合法
	double d = mul(b) - mul(c) + mul(x0) + mul(y0),
		   aa = mul(x0) / 1.0 / mul(y0) + 1.0,
		   bb = -d * x0 / mul(y0),
		   cc = d * d / mul(y0) / 4.0 - mul(b), // 联立圆的方程得到的方程的系数
		   delta = bb * bb - 4.0 * aa * cc;
	if (dcmp(delta) < 0) return 0;
	double axis = -bb / 2.0 / aa, e = sqrt(delta) / 2.0 / aa;
	double x1 = axis + e, y1 = (d - 2.0 * x0 * x1) / 2.0 / y0; 
	double x2 = axis - e, y2 = (d - 2.0 * x0 * x2) / 2.0 / y0; // 交点坐标
	return calc(x0, y0, int(round(x1)), int(round(y1)), b, c) 
		|| calc(x0, y0, int(round(x2)), int(round(y2)), b, c); // 验证是否为整点
}
class FindPolygons
{
	public:
		double minimumPolygon(int L) {
			int ret = oo;
			for (int i = 0; i <= L / 2; ++i) 
				means[i].clear();
			for (int i = 0; i <= L / 2; ++i)
				for (int j = 0; j <= L / 2; ++j) {
					sum = i * i + j * j;
					c = int(floor(sqrt(sum)));
					if (c * c == sum) 
						means[c].pb(mp(i, j)); // 预处理所有合法的整点坐标
				}
			for (int a = (L + 2) / 3; a <= (L - 1) / 2; ++a) { // 枚举最长边a的长度
				for (int b = 1; b <= a; ++b) { // 枚举剩下某条边的长度
					c = L - a - b;
					if (c > a || c <= 0) continue;
					for (int i = 0; i < means[a].size(); ++i) { // 枚举长度为a的边的终点
						int x = means[a][i].fr, y = means[a][i].sc;
						if (check(x, y, b, c)) // 验证是否合法
							ret = min(ret, a - min(b, c));
					}
				}
			}
			if (ret == oo) { // 若不存在合法的三角形
				if (L < 4 || L & 1) return -1;
				L /= 2;
				if (L & 1) return 1; 
				return 0; // 当L能被4整除时，可以构成正方形，否则构成长宽相差1的矩形
			} else {
				return ret;
			}
		}
};

