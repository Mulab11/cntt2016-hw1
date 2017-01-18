#line 2 "TravellingPurchasingMan.cpp"
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
#define maxs 65540
typedef long long ll;
using namespace std;
/*
	m较小，可以状压已经买过东西的商店集合，和目前的位置一起作为状态。对于一个状态，到达它的时间越早越好，因此直接用f[s][i]表示达到这个状态的最短耗时，dp即可。
*/
int n, m, l[maxn], r[maxn], d[maxn], f[maxs][maxn]; // n是点数，m是感兴趣的点数。l[i], r[i], d[i]分别表示第i个点开始营业/结束营业的时间和买东西的耗时。f[s][i]表示已经买过东西的店铺集合为s，目前在点i，此时最早的时间。
int dis[maxn][maxn]; // dis[i][j] 为i, j两点间的最短路长度
int read(string s, int &pos) { // 从s[pos]开始读数
	int len = s.length(), x = 0;
	while (pos < len && (s[pos] < '0' || s[pos] > '9')) ++pos;
	while (pos < len && s[pos] >= '0' && s[pos] <= '9')
		x = x * 10 + s[pos] - '0', ++pos;
	return x;
}
void gmin(int &a, int b) {
	if (b < a) a = b;
}
class TravellingPurchasingMan {
	public:
		int maxStores(int N, vector <string> times, vector <string> roads) {
			n = N; 
			memset(dis, 0x3f, sizeof(dis));
			m = times.size(); 
			for (int i = 0; i < m; ++i) {
				int pos = 0;
				l[i] = read(times[i], pos); r[i] = read(times[i], pos); d[i] = read(times[i], pos);
			}
			for (int i = 0; i < roads.size(); ++i) {
				int pos = 0;
				int u = read(roads[i], pos), v = read(roads[i], pos), w = read(roads[i], pos);
				dis[u][v] = dis[v][u] = min(dis[u][v], w);
			}
			for (int i = 0; i < n; ++i) dis[i][i] = 0;
			for (int k = 0; k < n; ++k) // floyd求出两两点之间的最短路
				for (int i = 0; i < n; ++i)
					for (int j = 0; j < n; ++j)
						if (i != k && j != k && i != j)
							gmin(dis[i][j], dis[i][k] + dis[k][j]);
			memset(f, 0x3f, sizeof(f));
			int inf = f[0][0];
			f[0][n - 1] = 0; // 初始状态
			for (int s = 0; s < (1 << m); ++s) // dp,枚举当前已经访问过的点集
				for (int i = 0; i < n; ++i)  // 枚举当前位置
					for (int j = 0; j < m; ++j) // 枚举下一个位置。由于最短路已经处理好，所以只有走到感兴趣的商店才是有意义的
						if (f[s][i] + dis[i][j] <= r[j]) // 赶得上
							gmin(f[s | (1 << j)][j], max(f[s][i] + dis[i][j], l[j]) + d[j]);
			int ans = 0;
			for (int s = 0; s < (1 << m); ++s)
				for (int i = 0; i < n; ++i)
					if (f[s][i] < inf) // 存在一个访问过s中商店的状态
						ans = max(ans, __builtin_popcount(s));
			return ans;
		}
};

