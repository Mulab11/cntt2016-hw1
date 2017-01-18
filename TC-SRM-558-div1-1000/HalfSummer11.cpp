#line 2 "SurroundingGame.cpp"
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
#define maxn 1010
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};
typedef long long ll;
using namespace std;
int n, m; // board的大小
// 以下为dinic
int s, t, g[maxn], cur[maxn], ei; 
struct edge {
	int t, c, nxt;
}e[maxn * 10];
void ae(int a, int b, int c) {
	e[++ei].t = b; e[ei].nxt = g[a]; g[a] = ei; e[ei].c = c;
	e[++ei].t = a; e[ei].nxt = g[b]; g[b] = ei; e[ei].c = 0;
}
int dis[maxn], q[maxn], qh, qt;
bool bfs() {
	memset(dis, -1, sizeof(dis));
	q[qh = qt = 1] = s; dis[s] = 0; int x;
	while (qh <= qt) {
		x = q[qh++];
		for (int i = g[x]; i; i = e[i].nxt)
			if (e[i].c && dis[e[i].t] == -1) {
				dis[e[i].t] = dis[x] + 1;
				q[++qt] = e[i].t;
			}
	}
	return dis[t] != -1;
}
int dfs(int x, int f) {
	if (x == t) return f;
	int d, u = 0;
	for (int &i = cur[x]; i; i = e[i].nxt)
		if (e[i].c && dis[e[i].t] == dis[x] + 1) {
			d = dfs(e[i].t, min(e[i].c, f - u));
			u += d; e[i].c -= d; e[i ^ 1].c += d;
			if (u == f) return u;
		}
	if (!u) dis[x] = -42;
	return u;
}
int dinic() {
	int ret = 0;
	while (bfs()) {
		memcpy(cur, g, sizeof(cur));
		ret += dfs(s, oo);
	}
	return ret;
}
//------------------------------------
int trans(char c) { // 从题目给的字符串里读数字
	if (c >= '0' && c <= '9') return c - '0';
	if (c >= 'a' && c <= 'z') return c - 'a' + 10;
	if (c >= 'A' && c <= 'Z') return c - 'A' + 36;
}
class SurroundingGame {
	public:
		int maxScore(vector <string> cost, vector <string> benefit) {
			n = cost.size(); m = cost[0].size();
			s = 2 * n * m + 1; t = s + 1;
			cl(g); ei = 1; int sum = 0;
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < m; ++j) {
					int num = i * m + j + 1, opo = num + n * m; // 每个点x拆出一个点x'
					sum += trans(benefit[i][j]);
					if ((i + j) & 1) { // 若是黑点，S表示选，T表示不选
						ae(num, t, trans(cost[i][j])); // 若选，就需要割掉这条边，付出cost的代价
						ae(opo, num, trans(benefit[i][j])); // 若它不选，且opo与S连通，那么就会付出benefit的代价，这对应它不选，它四周的格子也没有都被选的情况
					} else {
						ae(s, num, trans(cost[i][j]));
						ae(num, opo, trans(benefit[i][j]));
					}
					for (int d = 0; d < 4; ++d) {
						int nx = i + dx[d], ny = j + dy[d];
						if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
						if ((i + j) & 1)
							ae(nx * m + ny + 1, opo, oo); // 它四周的白格子，只要有一个与S连通，表示不选，opo就与S连通，若此时x点再与T连通表示不选，就损失benefit
						else
							ae(opo, nx * m + ny + 1, oo);
					}
				}
			return sum - dinic();
		}
};
