#line 2 "EnclosingTriangle.cpp"
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
#define maxn 235000
#define ls (p << 1)
#define rs (p << 1) | 1
typedef long long ll;
using namespace std;
/*
   对于每个点i，满足所有点在边i -> j的右侧的j位于i左侧的一段连续区间内，满足所有点在边i -> j的左侧的j位于i右侧的一段连续区间内。可以二分求出区间的端点位置L[i], R[i].
   枚举三角形的一个顶点i，它左侧的顶点j需要在区间[L[i], i)中，右侧的顶点k需要在区间(i, R[i]]与区间[L[j], j)的交集中，对于一个确定的j，它对答案的贡献就是区间(i, R[i]]与区间[L[j], j)的交集的大小。
   现在，问题转化成这样：有一堆线段，每次对于一个区间中的线段，询问它们与给定线段的交的大小之和。可以离线+线段树解决。
*/
vector <int> x, y; // 黑点的坐标
int n, px[maxn], py[maxn], L[maxn]; // n是红点个数，px[], py[]记录红点坐标，L[i]表示区间[L[i], i - 1]中的点和i相连后，所有红点都在这条线段的一侧
ll a[maxn * 4], tag[maxn * 4], size[maxn * 4]; // 线段树
void up(int p) {
	a[p] = a[ls] + a[rs];
}
void ad(int p, int v) {
	tag[p] += v; a[p] += 1ll * size[p] * v;
}
void down(int p) {
	if (tag[p]) {
		ad(ls, tag[p]);
		ad(rs, tag[p]);
		tag[p] = 0;
	}
}
void build(int p, int l, int r) { // 初始化线段树
	size[p] = r - l + 1; a[p] = tag[p] = 0;
	if (l == r) return;
	int mid = (l + r) >> 1;
	build(ls, l, mid); build(rs, mid + 1, r);
}
void add(int p, int l, int r, int s, int t) { // 给[s, t] + 1
	if (l == s && r == t) {
		ad(p, 1); return;
	} 
	int mid = (l + r) >> 1; down(p);
	if (t <= mid) add(ls, l, mid, s, t);
	if (s > mid) add(rs, mid + 1, r, s, t);
	if (s <= mid && t > mid) {
		add(ls, l, mid, s, mid); add(rs, mid + 1, r, mid + 1, t);
	}
	up(p);
}
ll get(int p, int l, int r, int s, int t) { // 询问[s, t]的和
	if (l == s && r == t) return a[p];
	int mid = (l + r) >> 1; down(p);
	if (t <= mid) return get(ls, l, mid, s, t);
	if (s > mid) return get(rs, mid + 1, r, s, t);
	return get(ls, l, mid, s, mid) + get(rs, mid + 1, r, mid + 1, t);
}
struct qry { // 存询问：每次询问编号位于[l, r]区间内的线段与线段[L, R]的交的大小的和。把询问挂到pos = l - 1, pos = r两个位置，询问[L, R]的区间和。rev分别标为1和0，代表从答案中减去还是加上。
	int pos, L, R; bool rev;
	qry(){}
	qry(int p, int l, int r, bool re) { pos = p; L = l; R = r; rev = re; }
	bool operator < (const qry &b) const {
		return pos < b.pos;
	}
}q[maxn * 7];
int qt;
bool check(int s, int t, int rev) { // 验证s -> t这条线段是否合法
	for (int i = 0; i < x.size(); ++i)
		if (1ll * rev * (1ll * (px[t] - px[s]) * (y[i] - py[s]) - 1ll * (x[i] - px[s]) * (py[t] - py[s])) < 0) return 0; // 不在指定侧
	return 1;
}
int mt(int x) { // 把x调整到[1, n]内
	while (x < 1) x += n;
	while (x > n) x -= n;
	return x;
}
int calc(int x, int rev) { // 计算x点的L[x], R[x]
	int l = 0, r = n, mid, ret, pos;
	while (l <= r) { // 由于合法区间连续，二分计算
		mid = (l + r) >> 1;
		pos = mt(x + rev * mid);
		if (check(x, pos, rev)) {
			ret = mid; l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	return ret;
}
class EnclosingTriangle {
	public:
		long long getNumber(int m, vector <int> X, vector <int> Y) {
			x = X; y = Y;
			n = 0;
			for (int i = 0; i <= m; ++i)
				px[++n] = i, py[n] = 0; // 把四周的黑点丢进来
			for (int i = 1; i <= m; ++i)
				px[++n] = m, py[n] = i;
			for (int i = m - 1; i >= 0; --i)
				px[++n] = i, py[n] = m;
			for (int i = m - 1; i >= 1; --i)
				px[++n] = 0, py[n] = i;
			qt = 0;
			int R;
			for (int i = 1; i <= n; ++i) {
				L[i] = calc(i, -1);
				L[i] = mt(i - L[i]);
				R = calc(i, 1);
				R = mt(i + R);
				if (L[i] <= mt(i - 1)) { // 需要询问，j在[L[i], i - 1]之间的[L[j], j - 1]与[i + 1, R[i]]的交的和。对于满足条件的j，在[L[j], j - 1]处+1，最后在[i + 1, R[i]]处询问即可。离线，逐个加入线段[L[j], j - 1],用在i - 1处询问到的答案减去在L[i] - 1处询问到的答案，就是要求的和。由于把边界展成直线后，原本的一个连续区间可能变成两个，需要进行一些讨论。
					if (mt(i + 1) <= R) {
						q[++qt] = qry(L[i] - 1, mt(i + 1), R, 1);
						q[++qt] = qry(mt(i - 1), mt(i + 1), R, 0);
					} else {
						q[++qt] = qry(L[i] - 1, mt(i + 1), n, 1);
						q[++qt] = qry(L[i] - 1, 1, R, 1);
						q[++qt] = qry(mt(i - 1), mt(i + 1), n, 0);
						q[++qt] = qry(mt(i - 1), 1, R, 0);
					}
				} else {
					if (mt(i + 1) <= R) {
						q[++qt] = qry(L[i] - 1, mt(i + 1), R, 1);
						q[++qt] = qry(n, mt(i + 1), R, 0);
						q[++qt] = qry(0, mt(i + 1), R, 1);
						q[++qt] = qry(mt(i - 1), mt(i + 1), R, 0);
					} else {
						q[++qt] = qry(L[i] - 1, mt(i + 1), n, 1);
						q[++qt] = qry(L[i] - 1, 1, R, 1);
						q[++qt] = qry(n, mt(i + 1), n, 0);
						q[++qt] = qry(n, 1, R, 0);
						q[++qt] = qry(0, mt(i + 1), n, 1);
						q[++qt] = qry(0, 1, R, 1);
						q[++qt] = qry(mt(i - 1), mt(i + 1), n, 0);
						q[++qt] = qry(mt(i - 1), 1, R, 0);
					}
				}
			}
			sort(q + 1, q + qt + 1);
			build(1, 1, n);
			ll ret = 0;
			int j = 1;
			for (int i = 1; i <= qt; ++i) { 
				while (j <= n && j <= q[i].pos) { // 加入满足条件的[L[j], j - 1]
					if (L[j] <= mt(j - 1)) 
						add(1, 1, n, L[j], mt(j - 1));
					else {
						add(1, 1, n, L[j], n);
						add(1, 1, n, 1, mt(j - 1));
					}
					++j;
				}
				if (q[i].rev)
					ret -= get(1, 1, n, q[i].L, q[i].R);
				else
					ret += get(1, 1, n, q[i].L, q[i].R);
			}
			return ret / 3ll; // 一个三角形会在三个顶点上被各计算一次
		}
};
