#line 2 "PolygonTraversal.cpp"
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
#define maxn 19
#define maxs 262200
typedef long long ll;
using namespace std;
/*
   一条线与之前的线相交，当且仅当在这条线分出的两个半圆上，都已经有点被选中。于是，状压已经选中的点进行dp即可。
*/
ll f[maxs][maxn]; // f[s][i]表示已经选的点为s，目前在点i，的方案数
class PolygonTraversal {
	public:
		long long count(int n, vector <int> p) {
			cl(f);
			int cur = 0, m = p.size();
			for (int i = 0; i < m; ++i) --p[i];
			for (int i = 0; i < p.size(); ++i)
				cur |= (1 << p[i]); // 初始状态
			f[cur][p[m - 1]] = 1;
			for (int s = cur; s < (1 << n); ++s)
				for (int i = 0; i < n; ++i)
					if (f[s][i]) {
						for (int j = 0; j < n; ++j)
							if (!(s & (1 << j))) { // 枚举下一个连向的点
								bool L = 0, R = 0; // 标记两个半圆上是否有点被选中
								for (int k = 0; k < n; ++k) 
									if (k != i && (s & (1 << k))) { // 对于被选中的点k
										if (((i < j) && (i < k) && (k < j)) || ((i > j) && ((k > i) || (k < j)))) // 判断是否在i -> j的顺时针圆弧上
											L = 1;
										else
											R = 1;
									}
								if (L && R) // i - j与之前的线有交
									f[s | (1 << j)][j] += f[s][i];
							}
					}
			ll ans = 0;
			for (int i = 0; i < n; ++i) {
				if (p[0] - i == 1 || i - p[0] == 1 || (p[0] == 0 && i == n - 1) || (p[0] == n - 1 && i == 0)) // 最后一笔。只要i和p[0]不相邻，就一定能和之前的直线相交
					continue;
				ans += f[(1 << n) - 1][i];
			}
			return ans;
		}
};
