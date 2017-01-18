#line 2 "DisjointSemicircles.cpp"
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
typedef long long ll;
using namespace std;
pii a[maxn];
int n, m, tot, l[maxn], r[maxn]; // n是数字对数，m是-1对数，tot是已经确定的数字对数。l[i],r[i]分别为数字i出现的左边位置和右边位置
bool used[maxn]; // used[i]标记第i个-1是否被配对
int aval[maxn], at, sum[maxn]; // aval[i]表示第i个-1的位置, at是-1个数。sum[i]表示0 - i这些位置里-1的个数
int fa[maxn * 2]; // 并查集
int find(int x) {
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}
void merge(int a, int b) {
	a = find(a); b = find(b);
	if (a != b) fa[a] = b;
}
bool cross(int i, int j) { // 判断第i对数字和第j对数字的半圆若在同侧是否相交
	return (a[i].fr < a[j].fr && a[j].fr < a[i].sc && a[i].sc < a[j].sc);
}
bool check() { // 对于一种-1的配对方案，检验是否合法
	for (int i = 0; i < 2 * n; ++i) fa[i] = i;
	for (int i = 0; i < n; ++i)
		for (int j = i + 1; j < n; ++j) 
			if (cross(i + 1, j + 1) || cross(j + 1, i + 1)) // 此时，两对半圆需要被放在不同的方向 
				merge(i, j + n), merge(j, i + n);
	for (int i = 0; i < n; ++i)
		if (find(i) == find(i + n)) // 出现矛盾
			return 0;
	return 1;
}
bool dfs(int x) {
	while (x <= at && used[x]) ++x; // 找到第一个没有被配对的-1
	if (x > at) return check();
	for (int i = x + 1; i <= at; ++i) // 枚举与它配对的-1
		if (!used[i]) {
			used[i] = 1;
			a[++tot] = mp(aval[x], aval[i]);
			if (dfs(x + 1)) return 1;
			--tot; used[i] = 0;
		}
	return 0;
}
class DisjointSemicircles {
	public:
		string getPossibility(vector <int> labels) {
			n = labels.size() / 2; tot = 0;
			for (int i = 0; i < n; ++i) l[i] = r[i] = -1;
			for (int i = 0; i < 2 * n; ++i)
				if (labels[i] != -1) {
					if (l[labels[i]] == -1) 
						l[labels[i]] = i;
					else {
						r[labels[i]] = i;
						a[++tot] = mp(l[labels[i]], r[labels[i]]);
					}
				}
			m = n - tot;
			if (m <= 6) { // 未被配对的-1较少，可以枚举它们的配对情况
				cl(used); at = 0;
				for (int i = 0; i < 2 * n; ++i)
					if (labels[i] == -1) aval[++at] = i;
				return dfs(1) ? "POSSIBLE" : "IMPOSSIBLE"; // dfs所有的配对情况，进行判断
			} else {
				for (int sta = 0; sta < (1 << (tot)); ++sta) { // 已经确定的数字对较少，可以枚举它们的方向
					bool flag = 1;
					for (int i = 0; i < tot; ++i) {
						for (int j = i + 1; j < tot; ++j)
							if (!(bool(sta & (1 << j)) ^ bool(sta & (1 << i)))) { // 同向的不能相交
									if (cross(i + 1, j + 1) || cross(j + 1, i + 1)) {
										flag = 0; break;
									}
								}
					}
					if (!flag) continue;
					for (int i = 0; i <= 4 * n + 2; ++i) fa[i] = i;
					sum[0] = (labels[0] == -1);
					for (int i = 1; i < 2 * n; ++i)
						sum[i] = sum[i - 1] + (labels[i] == -1); // 处理-1个数的前缀和
					for (int i = 1; i <= tot; ++i)
						if (!(sta & (1 << (i - 1))) && ((sum[a[i].sc - 1] - sum[a[i].fr]) & 1)) { // 对于一个弧，它里面需要有偶数个-1与它同向。令xi为前i个位置里朝上的-1的个数。当弧朝下，且它包含了奇数个-1时，它包含的区域里需要有奇数个-1朝上，xl ^ xr = 1
							merge(a[i].fr + 1, a[i].sc - 1 + 2 * n + 2);
							merge(a[i].fr + 2 * n + 2, a[i].sc - 1 + 1);
						} else { // 否则，它包含的区域里需要有偶数个-1朝上，xl ^ xr = 0
							merge(a[i].fr + 1, a[i].sc - 1 + 1);
							merge(a[i].fr + 2 * n + 2, a[i].sc - 1 + 2 * n + 2);
						}
					for (int i = 0; i < 2 * n; ++i)
						if (labels[i] != -1) { // 若i位置上不是-1，xi = xi+1, xi ^ xi+1 = 0
							merge(i - 1 + 1, i + 1);
							merge(i - 1 + 2 * n + 2, i + 2 * n + 2);
						}
					merge(0, 2 * n); // 整段里需要有偶数个-1朝上
					merge(2 * n + 1, 4 * n + 1);
					bool ok = 1;
					for (int i = 0; i <= 2 * n; ++i)
						if (find(i + 2 * n + 1) == find(i)) { // 出现矛盾
							ok = 0;
						}
					if (ok) return "POSSIBLE";
				}
				return "IMPOSSIBLE";
			}
		}
};
