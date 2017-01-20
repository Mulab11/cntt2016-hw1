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

int n, m;
struct edge
{
	int to, next, val;
	edge() {}
	edge(int _t, int _n, int _v):to(_t), next(_n), val(_v) {}
}e[maxn * maxn];
int head[maxn], et = -1;

void Addedge(int fr, int to, int val)//加边操作
{
	e[++et] = edge(to, head[fr], val), head[fr] = et;
}

int Spfa()//Spfa找最短路
{
	static int dist[maxn];//距离
	static int line[maxn + 3];//队列
	static bool ever[maxn];
	int h = 0, t = 0;
	memset(ever, 0, sizeof(ever));
	memset(dist, 0x3f, sizeof(dist));
	h = t = 0;
	dist[0] = 0;
	ever[0] = 1;
	line[h++] = 0;
	while (h != t) {
		int cur = line[t];
		ever[cur] = 0;
		t = (t == maxn) ? 0 : (t + 1);
		for (int j = head[cur]; j != -1; j = e[j].next) {
			if (dist[e[j].to] > dist[cur] + e[j].val) {
				dist[e[j].to] = dist[cur] + e[j].val;
				if (ever[e[j].to] == 0) {
					ever[e[j].to] = 1;
					line[h] = e[j].to;
					h = (h == maxn) ? 0 : (h + 1);
				}
			}
		}
	}
	if (dist[n - 1] > 1e9) return -1;
	else return dist[n - 1];
}

class ColorfulWolves {
    public:
    int getmin(vector<string> colormap) {
		n = colormap.size();
		m = colormap[0].length();
		memset(head, -1, sizeof(head));
		et = -1;
		for (int i = 0; i < n; ++i) {//建边，每条边的边权为要使用他必须删除的边的条数
			int cnt = 0;
			for (int j = 0; j < m; ++j) {
				if (colormap[i][j] == 'Y') {
					Addedge(i, j, cnt);
					++cnt;
				}
			}
		}
        return Spfa();//返回答案
    }
};
