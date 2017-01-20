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

const int maxn = 155;

int n;
int lab[maxn];

namespace Small//对于-1很少的情况，直接枚举每个-1的匹配情况
{
	int tlab[maxn], lst[maxn];
	int tt[maxn], used[maxn];
	int seg[maxn][2];
	int total, FAIL, ANS;
	struct edge
	{
		int to, next;
		edge() {}
		edge(int _t, int _n):to(_t), next(_n) {}
	}e[maxn * maxn];
	int head[maxn], et = -1;
	int color[maxn];
	bool inside(int l, int r, int a, int b)//判断两个半圆弧是否相交
	{
		return (l <= a && a <= r) != (l <= b && b <= r);
	}
	void Coloring(int p)//染色判断二分图
	{
		for (int i = head[p]; i != -1; i = e[i].next) {
			if (color[e[i].to] == -1) {
				color[e[i].to] = color[p] ^ 1;
				Coloring(e[i].to);
				if (FAIL) return;
			}
			else {
				if (color[e[i].to] == color[p]) {
					FAIL = 1;
					return;
				}
			}
		}
	}
	bool Check()//对于枚举的序列建图，然后判断二分图
	{
		memset(seg, -1, sizeof(seg));
		for (int i = 1; i <= n * 2; ++i) {//求出每个圆弧的覆盖区间
			if (seg[tlab[i]][0] == -1) {
				seg[tlab[i]][0] = i;
			}
			else {
				seg[tlab[i]][1] = i;
			}
		}
		memset(head, -1, sizeof(head));
		et = -1;
		for (int i = 1; i <= n; ++i) {//建边
			for (int j = i + 1; j <= n; ++j) {
				if (inside(seg[i][0], seg[i][1], seg[j][0], seg[j][1])) {
					e[++et] = edge(i, head[j]), head[j] = et;
					e[++et] = edge(j, head[i]), head[i] = et;
				}
			}
		}
		memset(color, -1, sizeof(color));
		FAIL = 0;
		for (int i = 1; i <= n; ++i) {//染色
			if (color[i] == -1) {
				color[i] = 0;
				Coloring(i);
			}
		}
		return (FAIL == 0);
	}
	void Dfs(int p, int nxt)//枚举-1位置的序列情况
	{
		if (p == total * 2 + 1) {
			for (int i = n * 2; i >= 1; --i) {
				if (lab[i] == -1) {
					tlab[i] = tt[--p];
				}
			}
			if (Check()) ANS = 1;//检查，得到合法情况
			return;
		}
		for (int i = 1; i < nxt; ++i) {//选择一个作为一段圆弧的结束
			if (used[i] == 0) {
				used[i] = 1;
				tt[p] = lst[i];
				Dfs(p + 1, nxt);
				used[i] = 0;
			}
			if (ANS) return;
		}
		if (nxt <= total) {//新的圆弧的开始
			tt[p] = lst[nxt];
			Dfs(p + 1, nxt + 1);
		}
	}
	int Solve()
	{
		bool has[maxn] = {0};
		total = 0;
		ANS = 0;
		for (int i = 1; i <= n * 2; ++i) {
			has[lab[i]] = 1;
		}
		for (int i = 1; i <= n; ++i) {//找出未定位的标号
			if (has[i] == 0) {
				lst[++total] = i;
			}
		}
		memcpy(tlab, lab, sizeof(lab));
		Dfs(1, 1);
		return ANS;
	}
}

namespace Big
{
	int ys[maxn];
	int ps[maxn], total, Z;
	int seg[maxn][2];
	int tt[maxn];
	int color[maxn];
	bool FAIL, ANS;
	struct edge
	{
		int to, next, val;
		edge() {}
		edge(int _t, int _n, int _v):to(_t), next(_n), val(_v) {}
	}e[maxn * maxn];
	int head[maxn], et = -1;
	bool inside(int x, int y)//判断相交
	{
		return (seg[x][0] <= seg[y][0] && seg[y][0] <= seg[x][1]) != (seg[x][0] <= seg[y][1] && seg[y][1] <= seg[x][1]);
	}
	void Coloring(int p)//对与等于与不等于关系进行判断
	{
		for (int i = head[p]; i != -1; i = e[i].next) {
			if (color[e[i].to] == -1) {
				color[e[i].to] = color[p] ^ e[i].val;
				Coloring(e[i].to);
				if (FAIL) return;
			}
			else {
				if (color[e[i].to] != (color[p] ^ e[i].val)) {
					FAIL = 1;
					return;
				}
			}
		}
	}
	bool Check()//检查这一中定向的方案是否有合法解
	{
		memset(head, -1, sizeof(head));
		et = -1;
		for (int i = 1; i <= total; ++i) {//通过前缀和关系建边
			if (tt[i] == 0) {
				e[++et] = edge(ps[seg[i][0]], head[ps[seg[i][1]]], 0), head[ps[seg[i][1]]] = et;
				e[++et] = edge(ps[seg[i][1]], head[ps[seg[i][0]]], 0), head[ps[seg[i][0]]] = et;
			}
			else {
				e[++et] = edge(ps[seg[i][0]], head[ps[seg[i][1]]], (ps[seg[i][1]] - ps[seg[i][0]]) & 1), head[ps[seg[i][1]]] = et;
				e[++et] = edge(ps[seg[i][1]], head[ps[seg[i][0]]], (ps[seg[i][1]] - ps[seg[i][0]]) & 1), head[ps[seg[i][0]]] = et;
			}
		}
		memset(color, -1, sizeof(color));
		FAIL = 0;
		color[0] = 0;//前0个的数量一定是偶数
		Coloring(0);
		if (color[Z] == -1) {//总数量也一定是偶数
			color[Z] = 0;
			Coloring(Z);
		}
		if (color[Z] != 0) return 0;
		for (int i = 0; i <= Z; ++i) {
			if (color[i] == -1) {
				color[i] = 0;
				Coloring(i);
			}
		}
		return (FAIL == 0);
	}
	void Dfs(int p)//枚举每条已经存在的圆弧的方向
	{
		if (p == total + 1) {
			if (Check()) ANS = 1;
			return;
		}
		bool ok;
		for (int i = 0; i < 2; ++i) {
			ok = 1;
			for (int j = 1; j < p; ++j) {
				if (tt[j] == i) {
					if (inside(j, p)) {
						ok = 0;
						break;
					}
				}
			}
			if (ok) {
				tt[p] = i;
				Dfs(p + 1);
				if (ANS) return;
			}
		}
	}
	bool Solve()
	{
		memset(ps, 0, sizeof(ps));
		for (int i = 1; i <= n * 2; ++i) {
			ps[i] = ps[i - 1] + (lab[i] == -1);
		}
		Z = ps[n * 2];
		memset(ys, -1, sizeof(ys));
		memset(seg, -1, sizeof(seg));
		total = 0;
		for (int i = 1; i <= n * 2; ++i) {//统计确定了的圆弧的数量
			if (lab[i] == -1) continue;
			if (ys[lab[i]] == -1) {
				ys[lab[i]] = ++total;
			}
			if (seg[ys[lab[i]]][0] == -1) seg[ys[lab[i]]][0] = i;
			else seg[ys[lab[i]]][1] = i;
		}
		ANS = 0;
		Dfs(1);
		return ANS;
	}
}

class DisjointSemicircles {
    public:
    string getPossibility(vector<int> labels) {
		int cnt = 0;
		int ans;
		n = labels.size() / 2;
		for (int i = 0; i < n * 2; ++i) {
			lab[i + 1] = labels[i];
			if (lab[i + 1] != -1) lab[i + 1] += 1;
			cnt += (lab[i + 1] == -1);
		}
		if (cnt <= 12) {//对于-1少的情况，枚举未确定的圆弧的两端
			ans = Small::Solve();
		}
		else {//否则，枚举已确定的圆弧的方向
			ans = Big::Solve();
		}
		if (ans) return "POSSIBLE";
        else return "IMPOSSIBLE";
    }
};
