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

const int maxn = 4e3+115;
const int maxm = 12e3+115;
const int maxc = 26;

int n, m;
struct edge
{
	int to, flow, cost, next;
	edge() {}
	edge(int _t, int _f, int _c, int _n):to(_t), flow(_f), cost(_c), next(_n) {}
}e[maxm];//边
int head[maxn], et = -1;//头指针
int cur[maxn];//当前弧优化
char mat[maxc][maxc];//地图
int gb[maxc][maxc][2];//地图中每条边在网络流图中的编号
int dt = 0;//点的个数
int S, T;//源点，汇点
int dist[maxn];//距离
bool insta[maxn] = {0};//是否在Dfs增广

void Addedge(int fr, int to, int flow, int cost)//加边
{
	e[++et] = edge(to, flow, cost, head[fr]), head[fr] = et;
	e[++et] = edge(fr, 0, -cost, head[to]), head[to] = et;
}

void Build()//建图
{
	S = 0;
	T = maxn - 1;
	memset(head, -1, sizeof(head));
	dt = 0;
	et = -1;
	for (int i = 1; i <= n; ++i) {//给地图中的边分配标号
		for (int j = 1; j < m; ++j) {
			gb[i][j][0] = ++dt;
		}
	}
	for (int i = 1; i < n; ++i) {
		for (int j = 1; j <= m; ++j) {
			gb[i][j][1] = ++dt;
		}
	}
	for (int i = 1; i <= n; ++i) {//建图时先黑白染色，同一种颜色放在一边
		for (int j = 1; j <= m; ++j) {
			if (mat[i][j] == 'w') continue;
			if (mat[i][j] == 'C') {//建图
			//对于一个有Curvies的地方，将上下，左右分为两组，没一组给一条容量为1,费用为0的边和一条容量为1,费用为1的边
			//这样就可以实现如果这里是一个弯曲的折，费用为0,否则费用为1
				if ((i + j) & 1) {
					++dt;
					Addedge(S, dt, 2, 0);
					Addedge(dt, dt + 1, 1, 0);
					Addedge(dt, dt + 1, 1, 1);
					Addedge(dt, dt + 2, 1, 0);
					Addedge(dt, dt + 2, 1, 1);
					if (i > 1) Addedge(dt + 1, gb[i - 1][j][1], 1, 0);
					if (j < m) Addedge(dt + 2, gb[i][j][0], 1, 0);
					if (i < n) Addedge(dt + 1, gb[i][j][1], 1, 0);
					if (j > 1) Addedge(dt + 2, gb[i][j - 1][0], 1, 0);
					dt += 2;
				}
				else {
					++dt;
					Addedge(dt, T, 2, 0);
					Addedge(dt + 1, dt, 1, 0);
					Addedge(dt + 1, dt, 1, 1);
					Addedge(dt + 2, dt, 1, 0);
					Addedge(dt + 2, dt, 1, 1);
					if (i > 1) Addedge(gb[i - 1][j][1], dt + 1, 1, 0);
					if (j < m) Addedge(gb[i][j][0], dt + 2, 1, 0);
					if (i < n) Addedge(gb[i][j][1], dt + 1, 1, 0);
					if (j > 1) Addedge(gb[i][j - 1][0], dt + 2, 1, 0);
					dt += 2;
				}
			}
			else {
			//对于没有curvies的地方，则直接建费用为0的边即可
				if ((i + j) & 1) {
					++dt;
					Addedge(S, dt, 2, 0);
					if (i > 1) Addedge(dt, gb[i - 1][j][1], 1, 0);
					if (j < m) Addedge(dt, gb[i][j][0], 1, 0);
					if (i < n) Addedge(dt, gb[i][j][1], 1, 0);
					if (j > 1) Addedge(dt, gb[i][j - 1][0], 1, 0);
				}
				else {
					++dt;
					Addedge(dt, T, 2, 0);
					if (i > 1) Addedge(gb[i - 1][j][1], dt, 1, 0);
					if (j < m) Addedge(gb[i][j][0], dt, 1, 0);
					if (i < n) Addedge(gb[i][j][1], dt, 1, 0);
					if (j > 1) Addedge(gb[i][j - 1][0], dt, 1, 0);
				}
			}
		}
	}
}

int Dinic(int p, int res)//Dfs增广
{
	int ff, flow = 0;
	if (p == T || res == 0) {
		return res;
	}
	insta[p] = 1;//记录是否在栈中，防止死循环
	for (int &i = cur[p]; i != -1; i = e[i].next) {
		if (insta[e[i].to] == 0 && dist[e[i].to] == dist[p] - e[i].cost && e[i].flow > 0) {
			ff = Dinic(e[i].to, min(res, e[i].flow));
			e[i].flow -= ff;
			e[i ^ 1].flow += ff;
			flow += ff;
			res -= ff;
			if (res == 0) {
				insta[p] = 0;
				return flow;
			}
		}
	}
	insta[p] = 0;
	return flow;
}

void Spfa()
{
	static int line[maxn + 5];
	static bool ever[maxn + 5];
	int h = 0, t = 0, now;
	memset(dist, 0x3f, sizeof(dist));
	memset(ever, 0, sizeof(ever));
	dist[T] = 0;
	line[h++] = T;
	ever[T] = 1;
	while (h != t) {//spfa求出每个点到汇点的最短距离，增广时只走最短路
		now = line[t];
		ever[now] = 0;
		t = (t == maxn) ? 0 : (t + 1);
		for (int i = head[now]; i != -1; i = e[i].next) {
			if (e[i ^ 1].flow > 0 && dist[e[i].to] > dist[now] + e[i ^ 1].cost) {
				dist[e[i].to] = dist[now] + e[i ^ 1].cost;
				if (ever[e[i].to] == 0) {
					ever[e[i].to] = 1;
					line[h] = e[i].to;
					if (dist[line[h]] < dist[line[t]]) swap(line[h], line[t]);
					h = (h == maxn) ? 0 : (h + 1);
				}
			}
		}
	}
}

int Solve()
{
	int FLOW = 0, ANS = 0, flow;
	while (1) {//求最小费用最大流
		Spfa();
		if (dist[S] < 1e9) {
			memcpy(cur, head, sizeof(head));
			flow = Dinic(S, 1e8);
			FLOW += flow;
			ANS += flow * dist[S];
		}
		else {
			break;
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (mat[i][j] != 'w') {
				--FLOW;
			}
		}
	}
	if (FLOW != 0) return -1;//如果不满流，则无解
	else return ANS;
}

class CurvyonRails {
    public:
    int getmin(vector<string> field) {
		n = field.size();
		m = field[0].length();
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				mat[i][j] = field[i - 1][j - 1];
			}
		}
		Build();//网络流建图
		return Solve();//求最小费用最大流
    }
};

