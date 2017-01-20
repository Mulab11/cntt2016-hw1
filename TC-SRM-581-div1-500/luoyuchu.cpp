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

const int maxn = 355;

int n;
struct edge
{
	int to, next;
	edge() {}
	edge(int _t, int _n):to(_t), next(_n) {}
}e[maxn * 2];
int head[maxn], et = -1;
int fa[maxn], deep[maxn];
int cnt[maxn], A[maxn], B[maxn];

void Reset()
{
	memset(head, -1, sizeof(head));
	et = -1;
}

void Addedge(int a, int b)//加边
{
	e[++et] = edge(b, head[a]), head[a] = et;
	e[++et] = edge(a, head[b]), head[b] = et;
}

void Dfs(int p)//Dfs
{
	for (int i = head[p]; i != -1; i = e[i].next) {
		if (fa[p] == e[i].to) continue;
		fa[e[i].to] = p;
		deep[e[i].to] = deep[p] + 1;
		Dfs(e[i].to);
	}
}

void Prepare()//求树中不同长度的路径的条数
{
	memset(cnt, 0, sizeof(cnt));
	for (int i = 0; i < n; ++i) {
		fa[i] = -1;
		deep[i] = 1;
		Dfs(i);
		for (int j = 0; j < n; ++j) {
			if (i != j) {
				++cnt[deep[j] - deep[i]];
			}
		}
	}
}

double Solve(int K)
{
	K -= 2;
	double Ans = 0;
	double C = n * (n - 1);
	for (int i = 1; i <= n; ++i) {
		A[i] /= 2;
		B[i] /= 2;
	}
	for (int i = 1; i < K; ++i) {//对于每一对路径，求出他对期望的贡献
		Ans += (double)B[K - i] * A[i] * 2 / C;
	}
	return Ans;
}

class TreeUnion {
    public:
    double expectedCycles(vector<string> tree1, vector<string> tree2, int K) {
		string tmp;
		stringstream tp;
		int a;
		tmp.clear();
		tp.clear();
		for (int i = 0; i < (int)tree1.size(); ++i) tmp = tmp + tree1[i];
		tp << tmp;
		n = 1;
		Reset();
		while (tp >> a) {
			Addedge(n++, a);
		}
		Prepare();//求出第一棵树中不同长度的路径的条数
		memcpy(A, cnt, sizeof(A));
		tmp.clear();
		tp.clear();
		for (int i = 0; i < (int)tree2.size(); ++i) tmp = tmp + tree2[i];
		tp << tmp;
		n = 1;
		Reset();
		while (tp >> a) {
			Addedge(n++, a);
		}
		Prepare();//求出第二棵树中不同长度的路径的条数
		memcpy(B, cnt, sizeof(B));
		return Solve(K);//求期望
    }
};
