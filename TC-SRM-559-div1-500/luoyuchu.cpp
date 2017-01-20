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

int n, Ans;
struct edge
{
	int to, next;
	edge() {}
	edge(int _t, int _n):to(_t), next(_n) {}
}e[maxn * 2];//边集
int head[maxn], et = -1;
int du[maxn], fa[maxn], type[maxn], down[maxn];

void Dfs(int p)//Dfs整颗树
{
	int son[2], st = 0;
	type[p] = 1;//type表示这一棵树是满二叉树还是非满二叉树的完全二叉树
	down[p] = 1;//表示这棵子树的最深的点的深度
	for (int i = head[p]; i != -1; i = e[i].next) {
		if (fa[p] == e[i].to) continue;
		fa[e[i].to] = p;
		Dfs(e[i].to);
		son[st++] = e[i].to;
	}
	if (st == 2) {
		down[p] = max(down[son[0]], down[son[1]]) + 1;
		if (type[son[0]] + type[son[1]] == 2) {//两边都树完全二叉树
			if (down[son[0]] == down[son[1]]) {//深度一样
				type[p] = 1;
				++Ans;
			}
			else if (abs(down[son[0]] - down[son[1]]) == 1) {//深度差1
				type[p] = 0;
			}
			else {
				Ans = -1e9;
			}
		}
		else if (type[son[0]] + type[son[1]] == 1) {//有一边不是
			if (type[son[0]] == 1) swap(son[0], son[1]);
			if (down[son[0]] >= down[son[1]] && abs(down[son[0]] - down[son[1]]) <= 1) {
				type[p] = 0;
			}
			else {
				Ans = -1e9;
			}
		}
		else {
			Ans = -1e9;
		}
	}
	else if (st == 1) {//只有一棵子树
		down[p] = down[son[0]] + 1;
		if (down[son[0]] == 1) {
			type[p] = 0;
		}
		else {
			Ans = -1e9;
		}
	}
}

class HatRack {
    public:
    long long countWays(vector<int> knob1, vector<int> knob2) {
		LL S = 0;
		n = knob1.size() + 1;
		memset(head, -1, sizeof(head));
		memset(du, 0, sizeof(du));
		et = -1;
		for (int i = 0; i < n - 1; ++i) {
			e[++et] = edge(knob1[i], head[knob2[i]]), head[knob2[i]] = et;
			e[++et] = edge(knob2[i], head[knob1[i]]), head[knob1[i]] = et;
			++du[knob1[i]];
			++du[knob2[i]];
		}
		if (n == 1) return 1;
		else if (n == 2) return 2;
		else {
			for (int i = 1; i <= n; ++i) {
				if (du[i] == 2) {//除去只有1个和2个点的情况，只有度数为2的点才能成为根
					Ans = 0;
					memset(fa, 0, sizeof(fa));
					Dfs(i);
					if (Ans >= 0) {
						S += (1LL << Ans);
					}
				}
			}
		}
        return S;
    }
};
