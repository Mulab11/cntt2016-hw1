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

const int maxn = 55;
const int maxd = maxn * maxn;
const int maxe = maxd * 6;
const int walk[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

int n, m;
char mat[maxn][maxn];
struct edge
{
	int to, next, flow;
	edge() {}
	edge(int _t, int _n, int _f):to(_t), next(_n), flow(_f) {}
}e[maxe];
int head[maxd], et = -1, dt = 0;
int S, T;
int tip[maxn][maxn];
int dist[maxd], cur[maxd];

void Addedge(int fr, int to, int flow)
{
	e[++et] = edge(to, head[fr], flow), head[fr] = et;
	e[++et] = edge(fr, head[to], 0), head[to] = et;
}

void Build()//建图
{
	//我们可以将放一个黑子看作花费1的代价，如果一颗白子周围只有有一颗黑子没有放，则有花费1的代价
	//这是一个最小割的经典模型，可以用网络流解决
	memset(head, -1, sizeof(head));
	et = -1;
	dt = 0;
	S = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			tip[i][j] = ++dt;
		}
	}
	T = ++dt;
	int tx, ty;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (mat[i][j] == '.') {
				Addedge(tip[i][j], T, 1);
			}
			else if (mat[i][j] == 'x') {
				Addedge(S, tip[i][j], 1e9);
				Addedge(tip[i][j], T, 1);
			}
			else {
				Addedge(S, tip[i][j], 1);
				for (int k = 0; k < 4; ++k) {
					tx = i + walk[k][0];
					ty = j + walk[k][1];
					if (tx >= 1 && tx <= n && ty >= 1 && ty <= m) {
						Addedge(tip[i][j], tip[tx][ty], 1e9);
					}
				}
			}
		}
	}
}

void Bfs()//Bfs求距离标号
{
	static int line[maxd];
	int h = 0, t = 0;
	memset(dist, 0x3f, sizeof(dist));
	dist[T] = 0;
	line[h++] = T;
	while (h != t) {
		int now = line[t++];
		for (int i = head[now]; i != -1; i = e[i].next) {
			if (e[i ^ 1].flow > 0 && dist[e[i].to] > dist[now] + 1) {
				dist[e[i].to] = dist[now] + 1;
				line[h++] = e[i].to;
			}
		}
	}
}

int Dinic(int p, int res)//Dinic增广
{
	int ff, flow = 0;
	if (p == T || res == 0) return res;
	for (int &i = cur[p]; i != -1; i = e[i].next) {
		if (dist[p] - 1 == dist[e[i].to] && e[i].flow > 0) {
			ff = Dinic(e[i].to, min(res, e[i].flow));
			flow += ff;
			res -= ff;
			e[i].flow -= ff;
			e[i ^ 1].flow += ff;
			if (res == 0) return flow;
		}
	}
	return flow;
}

int Solve()//最大流
{
	int Ans = 0;
	while (1) {
		Bfs();
		if (dist[S] > 1e9) break;
		memcpy(cur, head, sizeof(cur));
		Ans += Dinic(S, 1e9);
	}
	return Ans;
}

class FoxAndGo3 {
    public:
    int maxEmptyCells(vector<string> board) {
		n = board.size();
		m = board[0].length();
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				mat[i + 1][j + 1] = board[i][j];
			}
		}
		Build();//利用最小割等于最大流解决问题
		return n * m - Solve();
    }
};
