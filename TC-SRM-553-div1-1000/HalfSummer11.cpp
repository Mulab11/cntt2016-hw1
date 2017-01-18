#line 2 "YamanoteLine.cpp"
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
#define maxn 3010
typedef long long ll;
using namespace std;
int g[maxn], ei; 
struct edge {
	int t, w, nxt;
} e[maxn * 4];
void ae(int a, int b, int c) {
	e[++ei].t = b; e[ei].nxt = g[a]; g[a] = ei; e[ei].w = c;
} // 有向图边表
ll dis[maxn]; // spfa中的距离数组
int q[maxn], qh, qt, cnt[maxn]; // q[], qh, qt是队列，cnt[i]标记i点的入队次数
bool inq[maxn]; // inq[i]标记i是否在队中
bool spfa(int s, int n) { // spfa求从s点出发到各点的最长路
	cl(inq); cl(cnt);
	memset(dis, -0x3f, sizeof(dis));
	dis[s] = 0; inq[s] = 1; cnt[s] = 1; q[qh = 0] = s; qt = 1;
	while (qh != qt) {
		int x = q[qh++]; if (qh == maxn) qh = 0;
		for (int i = g[x]; i; i = e[i].nxt)
			if (dis[e[i].t] < dis[x] + e[i].w) {
				dis[e[i].t] = dis[x] + e[i].w;
				if (!inq[e[i].t]) {
					inq[e[i].t] = 1;
					q[qt++] = e[i].t;
					if (qt == maxn) qt = 0;
					if ((++cnt[e[i].t]) >= n) return 0; // 入队超过n次，存在正环，说明条件不合法
				}
			}
		inq[x] = 0;
	}
	return 1;
}
class YamanoteLine {
	public:
		long long howMany(int n, vector <int> s1, vector <int> t1, vector <int> l1, vector <int> s2, vector <int> t2, vector <int> l2) {
			cl(g); ei = 0; int lim = n * n;
			for (int i = 0; i < s1.size(); ++i) { 
				if (t1[i] < s1[i]) t1[i] += n; 
				while (t1[i] < lim) { // 将环切开后复制n份，全都连上边
					ae(s1[i], t1[i], l1[i]); // 一条边(s, t, w)表示x_s + .. + x_{t - 1} >= w
					s1[i] += n; t1[i] += n;
				}
			}
			for (int i = 0; i < s2.size(); ++i) {
				if (t2[i] < s2[i]) t2[i] += n;
				while (t2[i] < lim) { // 如上，连边
					ae(t2[i], s2[i], -l2[i]); // 一条边(t, s, -w)表示-x_s - .. - x_{t - 1} >= -w,即x_s + .. + x_{t - 1} <= w
					s2[i] += n; t2[i] += n;
				}
			}
			for (int i = 0; i + 1 < lim; ++i)
				ae(i, i + 1, 1); // 每条轨道的长度均为正数
			ll r = -0x3f3f3f3f3f3f3f3f, l = r;
			for (int i = 0; i < lim; ++i) {
				if (!spfa(i, n * n)) return 0; // 出现正环，没有符合条件的轨道长度
				for (int j = i + n, cnt = 1; j < lim; j += n, ++cnt) 
					l = max(l, (dis[j] + cnt - 1ll) / (ll)cnt); // (i, i + cnt * n)的最长路L，表示cnt * total >= L, total >= ceil(L / cnt)
				for (int j = i - n, cnt = 1; j >= 0; j -= n, ++cnt) 
					r = max(r, - abs(dis[j]) / (ll)cnt); // (i, i - cnt * n)的最长路L,表示-cnt * total >= L, total <= -L / cnt
			}
			r = -r;
			if (l > r) return 0;
			if (r - l + 1 > 1000000000000ll) return -1; // 有无穷多种选择
			return r - l + 1;
		}
};

