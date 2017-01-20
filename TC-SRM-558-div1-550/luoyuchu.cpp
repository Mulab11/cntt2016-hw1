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

const int maxn = 355;

int n, m;
int rx[maxn];
int bx[maxn], by[maxn];
LL Ans;

int dcmp(long double det)//实数比较
{
	if (abs(det) < 7e-6) return 0;
	return (det > 0) ? 1 : -1;
}

void Solve()
{
	long double px;
	int mid, Nmid, L, R;
	int x1, x2, y1, y2;
	sort(rx + 1, rx + 1 + n);//将x轴上的点排序
	for (int i = 1; i <= m; ++i) {
		for (int j = i + 1; j <= m; ++j) {//枚举两个三角形的顶点
			if (by[i] == by[j]) continue;
			x1 = bx[i], x2 = bx[j];
			y1 = by[i], y2 = by[j];
			if (y1 < y2) swap(x1, x2), swap(y1, y2);
			px = x1 + y1 / (long double)(y1 - y2) * (x2 - x1);//大三角形的两个底点必须在其两侧，才能保证包含小三角形
			if (dcmp(rx[n] - px) <= 0 || dcmp(rx[1] - px) >= 0) continue;
			mid = 1; while (dcmp(rx[mid] - px) < 0) ++mid;//找出分开的位置的对应点
			Nmid = lower_bound(rx + 1, rx + 1 + n, x2) - rx;//大三角形的两个底点必须在其两侧，才能保证小三角形为锐角
			L = 0, R = 0;
			for (int k = mid - 1; k >= 1; --k) {//枚举大三角形左边低点，并统计小三角形的左边的方案
				if (rx[k] < x1) {
					L += Nmid - 1 - k;
				}
			}
			if (dcmp(rx[mid] - px) == 0) ++mid;//严格包含
			if (rx[Nmid] == x2) ++Nmid;//锐角三角形
			for (int k = mid; k <= n; ++k) {//枚举大三角形右边低点，并统计小三角形的右边的方案
				if (rx[k] > x1) {
					R += k - Nmid;
				}
			}
			Ans += (LL)L * R;//左右相乘法
		}
	}
}

class Ear {
    public:
    long long getCount(vector<string> redX, vector<string> blueX, vector<string> blueY) {
		int tmp = 0;
		n = 0;
		Ans = 0;
		for (int i = 0; i < redX.size(); ++i) {//读入
			for (int j = 0; j < redX[i].length(); ++j) {
				if (redX[i][j] == ' ') {
					rx[++n] = tmp;
					tmp = 0;
				}
				else {
					tmp = tmp * 10 + redX[i][j] - '0';
				}
			}
		}
		rx[++n] = tmp;
		tmp = 0;
		m = 0;
		for (int i = 0; i < blueX.size(); ++i) {
			for (int j = 0; j < blueX[i].length(); ++j) {
				if (blueX[i][j] == ' ') {
					bx[++m] = tmp;
					tmp = 0;
				}
				else {
					tmp = tmp * 10 + blueX[i][j] - '0';
				}
			}
		}
		bx[++m] = tmp;
		tmp = 0;
		m = 0;
		for (int i = 0; i < blueY.size(); ++i) {
			for (int j = 0; j < blueY[i].length(); ++j) {
				if (blueY[i][j] == ' ') {
					by[++m] = tmp;
					tmp = 0;
				}
				else {
					tmp = tmp * 10 + blueY[i][j] - '0';
				}
			}
		}
		by[++m] = tmp;
		tmp = 0;
		Solve();
        return Ans;
    }
};

