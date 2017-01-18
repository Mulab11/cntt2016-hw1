#line 2 "History.cpp"
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
#define maxn 300
typedef long long ll;
using namespace std;
/*
   设对于国家i的时间t，真实时间为d[i] + t. 
   如果x国的第i个朝代和y国的第j个朝代交战了，说明d[x] + l[x][i] <= d[y] + r[y][j] && d[y] + l[y][j] <= d[x] + r[x][i], 分别按照最短路/最长路建图, 在x和y之间连边。
   对于一个询问，可以在最长路/最短路图上询问出d[x], d[y]之差的最小/最大值，与两个朝代有公共时间所需要满足的限制进行比较，得出结果。
*/
int n, l[maxn][maxn], r[maxn][maxn]; // n是国家个数，l[i][j]表示第i个国家的第j个朝代的开始时间，r[i][j]是结束时间
struct graph {
	int type;
	int g[maxn], ei;
	struct edge {
		int t, w, nxt;
	}e[maxn * maxn * 2];
	void ae(int a, int b, int c) {
		e[++ei].t = b; e[ei].nxt = g[a]; g[a] = ei; e[ei].w = c;
	}
	int dis[maxn], q[maxn], qh, qt; // spfa
	bool inq[maxn];
	int spfa(int s, int t) { // 求s到t的最短路/最长路
		for (int i = 0; i <= 26; ++i) dis[i] = type * oo;
		dis[s] = 0; inq[s] = 1; q[qh = 0] = s; qt = 1; 
		int x;
		while (qh != qt) {
			x = q[qh++]; if (qh == maxn) qh = 0;
			inq[x] = 0;
			for (int i = g[x]; i; i = e[i].nxt)
				if ((dis[e[i].t] - dis[x] - e[i].w) * type > 0) {
					dis[e[i].t] = dis[x] + e[i].w;
					if (!inq[e[i].t]) {
						inq[e[i].t] = 1;
						q[qt++] = e[i].t; if (qt == maxn) qt = 0;
					}
				}
		}
		return dis[t];
	}
} G1, G2; // G1:最短路，G2:最长路
class History {
	public:
		string verifyClaims(vector <string> dyn, vector <string> bat, vector <string> qry) {
			n = dyn.size();
			for (int i = 0; i < n; ++i) {
				int c = 0, len = dyn[i].length();
				for (int j = 0; j < len; ) {
					while (j < len && (dyn[i][j] < '0' || dyn[i][j] > '9')) ++j;
					int x = 0;
					while (j < len && (dyn[i][j] >= '0' && dyn[i][j] <= '9'))
						x = x * 10 + dyn[i][j] - '0', ++j;
					l[i][c] = x;
					if (c) r[i][c - 1] = x - 1; // 处理朝代的起始年份
					++c;
				}
				c -= 2;
			}
			cl(G1.g); cl(G2.g); G1.ei = G2.ei = 0;
			G1.type = 1; G2.type = -1;
			string b = "";
			for (int i = 0; i < bat.size(); ++i) b = b + bat[i];
			for (int i = 0; i < b.length(); i += 6) {
				int tx = b[i] - 'A', ty = b[i + 3] - 'A'; // tx, ty是两个国家
				int sx = b[i + 1] - '0', sy = b[i + 4] - '0'; // sx, sy是朝代
				for (int k = 0; k <= 1; ++k) {
					G1.ae(ty, tx, r[ty][sy] - l[tx][sx]); // 需要满足d[tx] + l[tx][sx] <= d[ty] + r[ty][sy] && d[ty] + l[ty][sy] <= d[tx] + r[tx][sx], 分别在对应最长路、最短路的图中建边表示条件
					G2.ae(tx, ty, l[tx][sx] - r[ty][sy]);
					swap(tx, ty); swap(sx, sy);
				}
			}
			string ans = "";
			for (int i = 0; i < qry.size(); ++i) {
				int tx = qry[i][0] - 'A', ty = qry[i][3] - 'A';
				int sx = qry[i][1] - '0', sy = qry[i][4] - '0';
				int L = l[ty][sy] - r[tx][sx], R = r[ty][sy] - l[tx][sx]; // 两者同时存在，需要L <= d[x] - d[y] <= R
				int rL = G2.spfa(ty, tx), rR = G1.spfa(ty, tx); // 实际上，rL <= d[x] - d[y] <= rR
				if (rL > R || L > rR) // 没有交，不可能同时存在
					ans = ans + "N";
				else
					ans = ans + "Y";
			}
			return ans;
		}
};
