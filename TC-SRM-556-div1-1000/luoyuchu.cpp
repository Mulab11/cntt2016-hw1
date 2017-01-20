#include <bits/stdc++.h>

#define dig(...) fprintf(stderr, __VA_ARGS__)

using namespace std;

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

const int maxn = 55;

int n;
int S, T;
struct edge
{
	int to, next, flow;
	edge() {}
	edge(int _t, int _n, int _f):to(_t), next(_n), flow(_f) {}
}e[maxn * maxn * 3];//边
int head[maxn], et = -1;
int dist[maxn];//距离标号
int cur[maxn];//当前弧

void Addedge(int x, int y, int f)//加边操作
{
	e[++et] = edge(y, head[x], f), head[x] = et;
	e[++et] = edge(x, head[y], f), head[y] = et;
}

void Bfs()//Bfs获取距离标号
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

int Dinic(int p, int res)//Dinic增广算法
{
	int flow = 0, ff;
	if (res == 0 || p == T) {
		return res;
	}
	for (int &i = cur[p]; i != -1; i = e[i].next) {
		if (e[i].flow > 0 && dist[p] == dist[e[i].to] + 1) {
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

int Maxflow()
{
	int FLOW = 0;//网络流
	while (1) {
		Bfs();
		if (dist[S] > 1e9) break;
		memcpy(cur, head, sizeof(head));
		FLOW += Dinic(S, 1e8);
	}
	return FLOW;
}

class OldBridges {
    public:
    string isPossible(vector<string> bridges, int a1, int a2, int an, int b1, int b2, int bn) {
		bool Ans;
		n = bridges.size();
		++a1, ++a2, ++b1, ++b2, an *= 2, bn *= 2;
		S = 0, T = n + 1;
		Ans = 1;
		for (int Ti = 0; Ti < 2; ++Ti) {
			memset(head, -1, sizeof(head));
			et = -1;
			for (int i = 0; i < n; ++i) {
				for (int j = i + 1; j < n; ++j) {
					if (bridges[i][j] != 'X') {
						Addedge(i + 1, j + 1, (bridges[i][j] == 'O') ? 2 : 1e8);
					}
				}
			}
			//可以证明如果将a1,b1作为源和a1,b2作为源两次网络流均可以满流，则一定有解，因为两次的流一定可以合成合法的路径
			if (Ti == 0) {
				Addedge(S, a1, an);
				Addedge(S, b1, bn);
				Addedge(a2, T, an);
				Addedge(b2, T, bn);
			}
			else {
				Addedge(S, a1, an);
				Addedge(S, b2, bn);
				Addedge(a2, T, an);
				Addedge(b1, T, bn);
			}
			Ans &= (Maxflow() == an + bn);
		}
		if (Ans) return "Yes";
        else return "No";
    }
};
