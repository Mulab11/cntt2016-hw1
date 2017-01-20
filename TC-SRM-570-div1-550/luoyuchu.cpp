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

const int maxn = 41;
const int G = maxn;

int n;
struct edge
{
	int to, next;
	edge() {}
	edge(int _t, int _n):to(_t), next(_n) {}
}e[maxn * 2];
int head[maxn], et = -1;
int fa[maxn], size[maxn];
LL f[maxn][maxn * 3 + 5][2];//f[i][j][0/1]表示一i为根的子树，(选择的联通块个数×2)-选择的点数=j的情况且i点选或不选(0/1)的方案数

void Addedge(int a, int b)//加边
{
	e[++et] = edge(b, head[a]), head[a] = et;
	e[++et] = edge(a, head[b]), head[b] = et;
}

void Dp(int p)
{
	static LL g[maxn * 3 + 5][2];//临时的Dp数组
	size[p] = 1;
	f[p][1 + G][1] = 1;
	f[p][G][0] = 1;
	for (int i = head[p]; i != -1; i = e[i].next) {
		if (fa[p] == e[i].to) continue;
		fa[e[i].to] = p;
		Dp(e[i].to);
		memset(g, 0, sizeof(g));
		for (int j = -size[p]; j <= size[p]; ++j) {//Dp转移，合并两个子树
			for (int k = -size[e[i].to]; k <= size[e[i].to]; ++k) {
				g[j + k + G][0] += f[p][j + G][0] * f[e[i].to][k + G][0];
				g[j + k + G][0] += f[p][j + G][0] * f[e[i].to][k + G][1];
				g[j + k + G][1] += f[p][j + G][1] * f[e[i].to][k + G][0];
				g[j + k + G - 2][1] += f[p][j + G][1] * f[e[i].to][k + G][1];
			}
		}
		memcpy(f[p], g, sizeof(g));
		size[p] += size[e[i].to];
	}
}

class CentaurCompany {
    public:
    double getvalue(vector<int> a, vector<int> b) {
		LL Ans = 0;
		n = a.size() + 1;
		et = -1;
		memset(head, -1, sizeof(head));
		memset(f, 0, sizeof(f));
		for (int i = 0; i < (int)a.size(); ++i) {//建边
			Addedge(a[i], b[i]);
		}
		Dp(1);//Dp
		for (int i = 3; i <= n; ++i) {//统计答案
			for (int j = 0; j < 2; ++j) {
				Ans += f[1][i + G][j] * (i - 2);
			}
		}
        return Ans * 2.0 / (1LL << n);//由于两个公司情况对称，直接乘以2即可
    }
};

