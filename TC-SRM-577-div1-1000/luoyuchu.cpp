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
const int maxd = maxn * maxn * 2;

int n, m;
bool mat[maxn][maxn];
int tip[maxn][maxn][4];
int S, T;
struct edge
{
	int to, next, flow;
	edge() {}
	edge(int _t, int _n, int _f):to(_t), next(_n), flow(_f) {}
}e[maxd * 5];
int head[maxd], et = -1, dt = 0;
int cur[maxd], dist[maxd];
int Ans = 0;

void Addedge(int fr, int to, int flow)//建边
{
	e[++et] = edge(to, head[fr], flow), head[fr] = et;
	e[++et] = edge(fr, head[to], 0), head[to] = et;
}

void Build()//网络流建图
{
	memset(tip, 0, sizeof(tip));
	memset(head, -1, sizeof(head));
	dt = 0;
	et = -1;
	S = 0;
	T = n * m * 2 + 1;
	dt = 0;
	for (int i = 1; i <= n; ++i) {//我们可以看作在格子中间选取一些隔板去掉，Ans=格子数-选择隔板数，但是由于题目要求，所以必须保证不能选取一个格子相邻的两个隔板，所以先将隔板染色，再使用最小割对二元条件的约束即可解决问题
		for (int j = 1; j < m; ++j) {
			if (mat[i][j] && mat[i][j + 1]) {
				tip[i][j][0] = ++dt;
				tip[i][j + 1][2] = dt;
				--Ans;
				Addedge(S, dt, 1);
			}
		}
	}
	for (int i = 1; i < n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (mat[i][j] && mat[i + 1][j]) {
				tip[i][j][1] = ++dt;
				tip[i + 1][j][3] = dt;
				--Ans;
				Addedge(dt, T, 1);
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			for (int k = 0; k < 4; ++k) {
				if (tip[i][j][k] && tip[i][j][(k + 1) % 4]) {//对于相邻的隔板，强制不能同时选择
					if (k & 1) {
						Addedge(tip[i][j][(k + 1) % 4], tip[i][j][k], 1e8);
					}
					else {
						Addedge(tip[i][j][k], tip[i][j][(k + 1) % 4], 1e8);
					}
				}
			}
		}
	}
}

void Bfs()//Bfs求出距离标号
{
	static int line[maxd + 5];
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

int Dinic(int p, int res)//Dinic网络流增广
{
	int flow = 0, ff;
	if (p == T || res == 0) {
		return res;
	}
	for (int &i = cur[p]; i != -1; i = e[i].next) {
		if (dist[e[i].to] + 1 == dist[p] && e[i].flow > 0) {
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

void Solve()//求解最小割=最大流
{
	while (1) {
		Bfs();
		if (dist[S] < 1e9) {
			memcpy(cur, head, sizeof(cur));
			Ans += Dinic(S, 1e9);
		}
		else {
			break;
		}
	}
}

class BoardPainting {
    public:
    int minimalSteps(vector<string> target) {
		n = target.size();
		m = target[0].length();
		Ans = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				mat[i][j] = (target[i - 1][j - 1] == '#');
				Ans += mat[i][j];
			}
		}
		Build();//网络流建图
		Solve();//求解答案
        return Ans;
    }
};

