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

int n, Root;
struct Circle
{
	int x, y, r;
	bool operator < (const Circle &b) const
	{
		return r < b.r;
	}
}C[maxn];
int fa[maxn];
struct edge
{
	int to, next;
	edge() {}
	edge(int _t, int _n):to(_t), next(_n) {}
}e[maxn * 2];
int head[maxn], et = -1;
int lst[maxn], lt = 0;
int sg[maxn];

double Dist(double x, double y)//计算圆心的距离
{
	return sqrt(x * x + y * y);
}

void Dfs(int p)//统计一个子树中有那些节点
{
	lst[++lt] = p;
	for (int i = head[p]; i != -1; i = e[i].next) {
		Dfs(e[i].to);
	}
}

void Solve(int p)//求p为根的子树的sg函数
{
	static bool cho[maxn];
	static bool exist[maxn];
	for (int i = head[p]; i != -1; i = e[i].next) {
		Solve(e[i].to);
	}
	lt = 0;
	Dfs(p);
	memset(exist, 0, sizeof(exist));
	for (int i = 1; i <= lt; ++i) {//枚举删去的是那一条到根的路径
		int x = lst[i];
		int s = 0;
		memset(cho, 0, sizeof(cho));
		while (x != p) {
			cho[x] = 1;
			x = fa[x];
		}
		cho[p] = 1;
		for (int j = 1; j <= lt; ++j) {
			if (cho[lst[j]] == 0 && cho[fa[lst[j]]] == 1) {
				s ^= sg[lst[j]];
			}
		}
		exist[s] = 1;
	}
	for (int i = 0; i < maxn; ++i) {//sg[p]为所有他的后继状态的mex
		if (exist[i] == 0) {
			sg[p] = i;
			break;
		}
	}
}

class CirclesGame {
    public:
    string whoCanWin(vector<int> x, vector<int> y, vector<int> r) {
		int ans = 0;
		n = x.size();
		for (int i = 0; i < n; ++i) {
			C[i + 1].x = x[i];
			C[i + 1].y = y[i];
			C[i + 1].r = r[i];
		}
		memset(fa, 0, sizeof(fa));
		sort(C + 1, C + 1 + n);
		for (int i = 1; i <= n; ++i) {//可以根据圆的包含关系建立树的结构
			for (int j = i + 1; j <= n; ++j) {
				if (C[j].r > C[i].r && Dist(C[j].x - C[i].x, C[j].y - C[i].y) <= C[j].r) {
					fa[i] = j;
					break;
				}
			}
		}
		memset(head, -1, sizeof(head));
		et = -1;
		for (int i = 1; i <= n; ++i) {//建边
			if (fa[i] != 0) {
				e[++et] = edge(i, head[fa[i]]), head[fa[i]] = et;
			}
		}
		for (int i = 1; i <= n; ++i) {//由于这是一个平等的两边玩家使用最优策略的零和游戏，所以可以等价为一个nimber游戏，使用sg定理求解
			if (fa[i] == 0) {
				Solve(i);//求以i为根的树的sg函数
				ans ^= sg[i];
			}
		}
		if (ans == 0) return "Bob";//sg函数异或和为0,则先手必败
        else return "Alice";//反之亦然
    }
};

