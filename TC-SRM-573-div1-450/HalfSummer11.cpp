#line 2 "SkiResorts.cpp"
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
int n, val[maxn], vt; // n是点数，val[]存所有出现过的高度值。可以证明，若修改出一个起初不存在的高度，答案不会更优，所以只考虑修改成出现过的高度。
ll f[maxn][maxn]; // f[i][j]表示走到第i个点，目前第i个点的高度为val[j],所花的最小代价
pii q[maxn * maxn]; // spfa的队列
int qh, qt, qmaxn = maxn * maxn; // 队列
bool inq[maxn][maxn]; // 标记某状态是否在队列里
bool upd(ll &a, ll b) { // a = min(a, b), 成功更新返回1
	if (b < a) return a = b, 1;
	return 0;
}
class SkiResorts {
	public:
		long long minCost(vector <string> road, vector <int> h) {
			n = h.size();
			for (int i = 1; i <= n; ++i) val[i] = h[i - 1];
			sort(val + 1, val + n + 1);
			vt = unique(val + 1, val + n + 1) - val - 1; // 将出现过的高度排序去重
			for (int i = 0; i < n; ++i)
				h[i] = lower_bound(val + 1, val + vt + 1, h[i]) - val; // 离散化
			memset(f, 0x3f, sizeof(f));
			ll inf = f[0][0];
			cl(inq);
			qh = 0; qt = 0; 
			for (int i = 1; i <= vt; ++i) { // 初始状态是各种高度的起点
				q[qt++] = mp(0, i);
				f[0][i] = abs(val[h[0]] - val[i]);
				inq[0][i] = 1;
			}
			while (qh != qt) { // spfa，不断更新
				pii x = q[qh++]; if (qh == qmaxn) qh = 0;
				inq[x.fr][x.sc] = 0;
				for (int i = 0; i < n; ++i)
					if (road[x.fr][i] == 'Y') { // 找一个可达的点
						for (int j = x.sc; j >= 1; --j) { // 找一个可达的海拔
							if (upd(f[i][j], f[x.fr][x.sc] + abs(val[j] - val[h[i]])) && !inq[i][j]) {
								inq[i][j] = 1;
								q[qt++] = mp(i, j); if (qt == qmaxn) qt = 0;
							}
						}
					}
			}
			ll ans = inf;
			for (int i = 1; i <= vt; ++i)
				ans = min(ans, f[n - 1][i]);
			return (ans == inf) ? -1 : ans;
		}
};
