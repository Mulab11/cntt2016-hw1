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

const int maxn = 855;

int n, m;
struct edge
{
	int to, next, flow;
	edge() {}
	edge(int _t, int _n, int _f):to(_t), next(_n), flow(_f) {}
}e[maxn * 27];//边
int head[maxn], et = -1;
int cor[maxn], S, T;//cor[i]表示字符i对应的数字，S,T为源和汇
int cur[maxn], dist[maxn];//当前弧，距离编号

/*
先黑白染色成棋盘状，我们对每个白色格子建两个点为Wi和_Wi，黑色同理
1) S->_Bi benefit
2) _Wi->T benefit
3) S->Bi max(0, cost-benefit)
4) Bi->T max(0, benefit-cost)
5) S->Wi max(0, benefit-cost)
6) Wi->T max(0, cost-benefit)
7) _Bi->Bi infinite
8) Wi->_Wi infinite
9) for each pair cells adjacent _Bi->Wi Bi->_Wi infinite
*/
void Addedge(int fr, int to, int val)//加边操作
{
	e[++et] = edge(to, head[fr], val), head[fr] = et;
	e[++et] = edge(fr, head[to], 0), head[to] = et;
}

int gt(int x, int y, bool flag)//得到这个点的编号
{
	return x * m + y + 1 + ((flag) ? (n * m) : 0);
}

void Bfs()//Bfs求距离编号
{
	static int line[maxn];
	int h = 0, t = 0;
	memset(dist, 0x3f, sizeof(dist));
	dist[T] = 0;
	line[h++] = T;
	while (h != t) {
		int x = line[t++];
		for (int i = head[x]; i != -1; i = e[i].next) {
			if (e[i ^ 1].flow > 0 && dist[e[i].to] > dist[x] + 1) {
				dist[e[i].to] = dist[x] + 1;
				line[h++] = e[i].to;
			}
		}
	}
}

int Dinic(int p, int res)//Dinic增广
{
	if (p == T || res == 0) return res;
	int flow = 0, ff;
	for (int &i = cur[p]; i != -1; i = e[i].next) {
		if (dist[e[i].to] + 1 == dist[p] && e[i].flow > 0) {
			ff = Dinic(e[i].to, min(res, e[i].flow));
			e[i].flow -= ff;
			e[i ^ 1].flow += ff;
			flow += ff;
			res -= ff;
			if (res == 0) return flow;
		}
	}
	dist[p] = 1e9;
	return flow;
}

void Prepare()//初始化cor数组
{
	for (char i = '0'; i <= '9'; i += 1) {
		cor[i] = i - '0';
	}
	for (char i = 'a'; i <= 'z'; i += 1) {
		cor[i] = i - 'a' + 10;
	}
	for (char i = 'A'; i <= 'Z'; i += 1) {
		cor[i] = i - 'A' + 36;
	}
}

int Build(vector<string> c, vector<string> b)//建边，顺便返回减去最小割之前的总和
{
	const int wk[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
	int Sum = 0;
	n = c.size();
	m = c[0].length();
	S = 0; T = gt(n - 1, m - 1, 1) + 1;
	memset(head, -1, sizeof(head));
	et = -1;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if ((i + j) & 1) {
				Addedge(S, gt(i, j, 1), cor[b[i][j]]);
				Addedge(gt(i, j, 1), gt(i, j, 0), 1e9);
				Addedge(S, gt(i, j, 0), max(0, cor[c[i][j]] - cor[b[i][j]]));
				Addedge(gt(i, j, 0), T, max(0, cor[b[i][j]] - cor[c[i][j]]));
				for (int k = 0; k < 4; ++k) {
					if (i + wk[k][0] >= 0 && i + wk[k][0] < n && j + wk[k][1] >= 0 && j + wk[k][1] < m) {
						Addedge(gt(i, j, 1), gt(i + wk[k][0], j + wk[k][1], 0), 1e9);
						Addedge(gt(i, j, 0), gt(i + wk[k][0], j + wk[k][1], 1), 1e9);
					}
				}
			}
			else {
				Addedge(gt(i, j, 1), T, cor[b[i][j]]);
				Addedge(gt(i, j, 0), gt(i, j, 1), 1e9);
				Addedge(S, gt(i, j, 0), max(0, cor[b[i][j]] - cor[c[i][j]]));
				Addedge(gt(i, j, 0), T, max(0, cor[c[i][j]] - cor[b[i][j]]));
			}
			Sum += cor[b[i][j]] + max(0, cor[b[i][j]] - cor[c[i][j]]);
		}
	}
	return Sum;
}

int Maxflow()//最大流=最小割
{
	int FLOW = 0;
	while (1) {
		Bfs();
		if (dist[S] > 1e9) break;
		memcpy(cur, head, sizeof(cur));
		FLOW += Dinic(S, 1e9);
	}
	return FLOW;
}

class SurroundingGame {
    public:
    int maxScore(vector<string> cost, vector<string> benefit) {
		int Ans;
		Prepare();
		Ans = Build(cost, benefit);//总和减去最小割为答案
		Ans -= Maxflow();
        return Ans;
    }
};
