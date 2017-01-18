#line 2 "FoxTheLinguist.cpp"
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
#define maxn 110
#define maxs 1100
typedef long long ll;
using namespace std;
/*
   可以把题目给的条件转化成一张带权有向图，有一个起点s，n个终点ti，要选择一个权值和最小的边集，使得从s可以达到t1 ~ tn.
   可以用斯坦纳树来做。
   TAT也可以用最小树形图来做，需要在同种语言的上下级别之间连边
*/
int f[maxn][maxs]; // f[i][sta]表示从i出发，能够master sta中的语言，至少需要花多少代价
int g[maxn], ei; // 边表
struct edge {
	int t, w, nxt;
}e[maxn * maxn * 2];
void ae(int a, int b, int c) {
	e[++ei].t = b; e[ei].w = c; e[ei].nxt = g[a]; g[a] = ei;
}
bool upd(int x, int s, int v) { // f[x][s] = min(f[x][s], v)
	if (f[x][s] > v) {
		f[x][s] = v; return 1;
	} else
		return 0;
}
int q[maxn], qh, qt; // spfa的队列
bool inq[maxn];
void spfa(int sta) { // 对于f[][sta], 用spfa转移
	int x;
	while (qh != qt) {
		x = q[qh++]; if (qh == maxn) qh = 0;
		inq[x] = 0;
		for (int i = g[x]; i; i = e[i].nxt)
			if (upd(e[i].t, sta, f[x][sta] + e[i].w) && !inq[e[i].t]) {
				inq[e[i].t] = 1;
				q[qt++] = e[i].t; if (qt == maxn) qt = 0;
			}
	}
}
class FoxTheLinguist {
	public:
		int minimalHours(int n, vector <string> Info) {
			cl(g); ei = 0;
			string s = "";
			for (int i = 0; i < Info.size(); ++i)
				s = s + Info[i];
			for (int i = 0; i < s.size(); i += 12) {
				int stype = s[i] - 'A', slevel = s[i + 1] - '0';
				int ttype = s[i + 4] - 'A', tlevel = s[i + 5] - '0';
				int w = (s[i + 7] - '0') * 1000 + (s[i + 8] - '0') * 100 + (s[i + 9] - '0') * 10 + s[i + 10] - '0';
				for (int i = slevel; i <= 9; ++i)  // 逆向连边，从终点转移到起点
					ae(ttype * 10 + tlevel, stype * 10 + i, w);
			}
			for (int i = 0; i < n; ++i)
				ae(i * 10, n * 10, 0);
			memset(f, 0x3f, sizeof(f));
			for (int i = 0; i < n; ++i) {
				f[i * 10 + 9][1 << i] = 0; // n个终点处为初始状态
			}
			for (int i = 0; i <= 10 * n; ++i)
				f[i][0] = 0;
			for (int sta = 0; sta < (1 << n); ++sta) { 
				qh = 0; qt = 0; cl(inq);
				for (int i = 0; i <= 10 * n; ++i)
					for (int t = sta; t; t = (t - 1) & sta) 
						upd(i, sta, f[i][t] + f[i][sta - t]); // 同一个点上的转移
				for (int i = 0; i <= 10 * n; ++i)
					if (f[i][sta] < oo) {
						q[qt++] = i, inq[i] = 1; 
					} 
				spfa(sta); // 不同点之间spfa转移
			}
			int ans = f[n * 10][(1 << n) - 1];
			return ans == oo ? -1 : ans;
		}
};
