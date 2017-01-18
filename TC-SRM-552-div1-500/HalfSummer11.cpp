#line 2 "FoxAndFlowerShopDivOne.cpp"
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
#define maxn 35
typedef long long ll;
using namespace std;
int F[2][maxn * maxn * 2], *f[2]; // f[i][d]存，对于i侧，所有两种花的个数之差为d的子矩阵中，包含花的总数最多的一个所包含的花的总数
int w, h, a[maxn][maxn], det[maxn][maxn], sum[maxn][maxn]; // w,h是矩阵的尺寸，a存放矩阵中花的存在情况，det存两种花个数之差的二维前缀和，sum存两种花个数之和的二维前缀和
void rev() { // 将矩阵a沿着直线x + y = 0翻转
	int tmp[maxn][maxn];
	memcpy(tmp, a, sizeof(a)); cl(a);
	for (int i = 1; i <= w; ++i)
		for (int j = 1; j <= h; ++j)
			a[i][j] = tmp[j][i];
	swap(w, h);
}
void sumup(int sum[maxn][maxn]) { // 对数组sum求二维前缀和
	for (int i = 1; i <= h; ++i) 
		for (int j = 1; j <= w; ++j)
			sum[i][j] += sum[i][j - 1];
	for (int j = 1; j <= w; ++j)
		for (int i = 1; i <= h; ++i)
			sum[i][j] += sum[i - 1][j];
}
class FoxAndFlowerShopDivOne {
	public:
		int theMaxFlowers(vector <string> flowers, int maxDiff) {
			int ans = -1;
			for (int i = 0; i < 2; ++i) f[i] = F[i] + maxn * maxn;
			h = flowers.size(); w = flowers[0].size();
			for (int i = 0; i < h; ++i)
				for (int j = 0; j < w; ++j)
					a[i + 1][j + 1] = flowers[i][j] == 'L' ? 1 : flowers[i][j] == 'P' ? -1 : 0; // 把花的信息存到a中
			for (int o = 0; o < 2; ++o) { // 两个子矩阵必然可以用一条直线劈开，这条直线可能水平也可能竖直，所以做两遍
				for (int i = 1; i <= h; ++i)
					for (int j = 1; j <= w; ++j)
						sum[i][j] = abs(a[i][j]), det[i][j] = a[i][j];
				sumup(sum); sumup(det); // 处理好sum和det
				for (int mid = 1; mid < h; ++mid) { // 枚举分界线的位置
					memset(F, -0x3f, sizeof(F));
					int l[2], r[2];
					l[0] = 1; r[0] = mid;
					l[1] = mid + 1; r[1] = h; // 分别记录两个部分的上下边界
					for (int i = 0; i < 2; ++i) {
						for (int x1 = l[i]; x1 <= r[i]; ++x1)
							for (int y1 = 1; y1 <= w; ++y1)
								for (int x2 = x1; x2 <= r[i]; ++x2)
									for (int y2 = y1; y2 <= w; ++y2) {
										int s = sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1 - 1];
										int d = det[x2][y2] - det[x1 - 1][y2] - det[x2][y1 - 1] + det[x1 - 1][y1 - 1];
										f[i][d] = max(f[i][d], s); // 枚举每侧的所有子矩阵来更新f
									}
					}
					for (int i = -mid * w; i <= mid * w; ++i)
						for (int j = -(h - mid) * w; j <= (h - mid) * w; ++j) // 枚举选中子矩阵中两种花的个数差，用个数和更新答案
							if (abs(i + j) <= maxDiff) ans = max(ans, f[0][i] + f[1][j]);
				}
				rev(); // 将矩阵行列交换，讨论直线沿着另一种方向的情况
			}
			return ans;
		}
};
