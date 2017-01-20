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
const int walk[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

int n, m;
int mat[maxn][maxn];
int tip[maxn][maxn][2];
int S, T;
struct edge
{
	int to, next, flow;
	edge() {}
	edge(int _t, int _n, int _f):to(_t), next(_n), flow(_f) {}
}e[maxn * maxn * 8];
int head[maxn * maxn * 2], et = -1;
int dist[maxn * maxn * 2];
int cur[maxn * maxn * 2];
int dt = 0;

void Addedge(int fr, int to, int flow)//加边
{
	e[++et] = edge(to, head[fr], flow), head[fr] = et;
	e[++et] = edge(fr, head[to], 0), head[to] = et;
}

void Build()//网络流建图
{
	int tx, ty;
	S = 0;
	T = n * m * 2 + 1;
	memset(head, -1, sizeof(head));
	et = -1;
	dt = 0;
	for (int i = 0; i < n; ++i) {//将每个黑点拆点拆为2个，中间连一条流量为1的边
		for (int j = 0; j < m; ++j) {
			if ((i + j) % 2 == 0 && !mat[i][j]) {
				tip[i][j][0] = ++dt;
				tip[i][j][1] = ++dt;
				Addedge(tip[i][j][0], tip[i][j][1], 1);
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (((i + j) & 1) && !mat[i][j]) {
				if (i & 1) {//将白点按照所在的行的奇偶性分类，我们发现一个合法的形状的两个白点所在的行的奇偶性一定不同
					++dt;
					Addedge(S, dt, 1);//从源点连一条流量为1的边到他
					for (int k = 0; k < 4; ++k) {
						tx = i + walk[k][0];
						ty = j + walk[k][1];
						if (tx >= 0 && ty >= 0 && tx < n && ty < m && !mat[tx][ty]) {//将这个白点连向他所相邻的黑点
							Addedge(dt, tip[tx][ty][0], 1);
						}
					}
				}
				else {
					++dt;
					Addedge(dt, T, 1);//从他连一条流量为1的边到汇点
					for (int k = 0; k < 4; ++k) {
						tx = i + walk[k][0];
						ty = j + walk[k][1];
						if (tx >= 0 && ty >= 0 && tx < n && ty < m && !mat[tx][ty]) {//将他所相邻的黑点连向这个白点
							Addedge(tip[tx][ty][1], dt, 1);
						}
					}
				}
			}
		}
	}
}

void Bfs()//网络流求距离编号
{
	static int line[maxn * maxn * 2];
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
	int flow = 0, ff;
	if (p == T || res == 0) {
		return res;
	}
	for (int &i = cur[p]; i != -1; i = e[i].next) {
		if (dist[e[i].to] + 1 == dist[p] && e[i].flow > 0) {
			ff = Dinic(e[i].to, min(e[i].flow, res));
			res -= ff;
			e[i].flow -= ff;
			e[i ^ 1].flow += ff;
			flow += ff;
			if (res == 0) return flow;
		}
	}
	return flow;
}

int Solve()//求最大流
{
	int FLOW = 0;
	while (1) {
		Bfs();
		if (dist[S] > 1e9) break;
		memcpy(cur, head, sizeof(head));
		FLOW += Dinic(S, 1e8);
	}
	return FLOW;
}

class TheTilesDivOne {
    public:
    int find(vector<string> board) {
		n = board.size();
		m = board[0].length();
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				mat[i][j] = (board[i][j] == 'X');
			}
		}
		Build();//网络流建图
        return Solve();//求出最大流
    }
};
