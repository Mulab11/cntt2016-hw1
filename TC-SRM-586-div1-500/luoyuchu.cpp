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

const int maxn = 29;

int n, m, N, Q;
int kc[maxn];
int king[maxn][maxn];
int war[maxn * maxn][4];
struct Query
{
	int s[2];
	int t[2];
	int l, r;
}ask[maxn * 3];
struct edge
{
	int to, next, val;
	edge() {}
	edge(int _t, int _n, int _v):to(_t), next(_n), val(_v) {}
}e[maxn * maxn];
int head[maxn], et = -1;
int dist[maxn];

void Addedge(int x, int y, int z)
{
	e[++et] = edge(y, head[x], z), head[x] = et;
}

void Spfa_Greater(int St)//最长路
{
	static int line[maxn + 5];
	static bool ever[maxn + 5];
	int h = 0, t = 0;
	memset(dist, -0x3f, sizeof(dist));
	dist[St] = 0;
	ever[St] = 1;
	line[h] = St;
	h = (h == maxn) ? 0 : (h + 1);
	while (h != t) {
		int now = line[t];
		ever[now] = 0;
		t = (t == maxn) ? 0 : (t + 1);
		for (int i = head[now]; i != -1; i = e[i].next) {
			if (dist[now] + e[i].val > dist[e[i].to]) {
				dist[e[i].to] = dist[now] + e[i].val;
				if (ever[e[i].to] == 0) {
					ever[e[i].to] = 1;
					line[h] = e[i].to;
					h = (h == maxn) ? 0 : (h + 1);
				}
			}
		}
	}
}

void Spfa_Less(int St)//最短路
{
	static int line[maxn + 5];
	static bool ever[maxn + 5];
	int h = 0, t = 0;
	memset(dist, 0x3f, sizeof(dist));
	dist[St] = 0;
	ever[St] = 1;
	line[h] = St;
	h = (h == maxn) ? 0 : (h + 1);
	while (h != t) {
		int now = line[t];
		ever[now] = 0;
		t = (t == maxn) ? 0 : (t + 1);
		for (int i = head[now]; i != -1; i = e[i].next) {
			if (dist[now] + e[i].val < dist[e[i].to]) {
				dist[e[i].to] = dist[now] + e[i].val;
				if (ever[e[i].to] == 0) {
					ever[e[i].to] = 1;
					line[h] = e[i].to;
					h = (h == maxn) ? 0 : (h + 1);
				}
			}
		}
	}
}

void Solve_L()//求左边界
{
	memset(head, -1, sizeof(head));
	et = -1;
	for (int i = 1; i <= m; ++i) {//查分约束建边
		int *w = war[i];
		Addedge(w[2], w[0], king[w[2]][w[3]] - (king[w[0]][w[1] + 1] - 1));
		Addedge(w[0], w[2], king[w[0]][w[1]] - (king[w[2]][w[3] + 1] - 1));
	}
	for (int i = 1; i <= Q; ++i) {//求最长路
		Spfa_Greater(ask[i].s[0]);
		ask[i].l = dist[ask[i].t[0]];
	}
}

void Solve_R()//右边界
{
	memset(head, -1, sizeof(head));
	et = -1;
	for (int i = 1; i <= m; ++i) {//建边
		int *w = war[i];
		Addedge(w[2], w[0], king[w[2]][w[3] + 1] - 1 - king[w[0]][w[1]]);
		Addedge(w[0], w[2], king[w[0]][w[1] + 1] - 1 - king[w[2]][w[3]]);
	}
	for (int i = 1; i <= Q; ++i) {//求最短路
		Spfa_Less(ask[i].s[0]);
		ask[i].r = dist[ask[i].t[0]];
	}
}

string Solve()
{
	string ans;
	ans.clear();
	for (int i = 1; i <= Q; ++i) {//根据历法开始时间检查每个询问是否合法
		if (ask[i].r < king[ask[i].s[0]][ask[i].s[1]] - (king[ask[i].t[0]][ask[i].t[1] + 1] - 1) || ask[i].l > king[ask[i].s[0]][ask[i].s[1] + 1] - 1 - king[ask[i].t[0]][ask[i].t[1]]) {
			ans += 'N';
		}
		else {
			ans += 'Y';
		}
	}
	return ans;
}

class History {
    public:
    string verifyClaims(vector<string> dynasties, vector<string> battles, vector<string> queries) {
		n = dynasties.size();
		memset(kc, 0, sizeof(kc));
		stringstream tmp;
		string tp;
		for (int i = 1; i <= n; ++i) {//读入每个君主统治的时间
			tmp.clear();
			tmp << dynasties[i - 1];
			while (tmp >> king[i][kc[i] + 1]) {
				kc[i] += 1;
			}
		}
		tp.clear();
		for (int i = 0; i < (int)battles.size(); ++i) {
			tp += battles[i];
		}
		m = (tp.length() + 1) / 6;
		for (int i = 0; i < m; ++i) {//读入每场战争的信息
			war[i + 1][0] = tp[i * 6] - 'A' + 1;
			war[i + 1][1] = tp[i * 6 + 1] - '0' + 1;
			war[i + 1][2] = tp[i * 6 + 3] - 'A' + 1;
			war[i + 1][3] = tp[i * 6 + 4] - '0' + 1;
		}
		Q = queries.size();
		for (int i = 1; i <= Q; ++i) {//读入询问
			ask[i].s[0] = queries[i - 1][0] - 'A' + 1;
			ask[i].s[1] = queries[i - 1][1] - '0' + 1;
			ask[i].t[0] = queries[i - 1][3] - 'A' + 1;
			ask[i].t[1] = queries[i - 1][4] - '0' + 1;
		}
        //利用查分约束系统分别求出每个询问涉及的两个国家历法的开始时间的差值的左右边界
		Solve_L();//左边界
		Solve_R();//右边界
        return Solve();//统计检查每个询问
    }
};
