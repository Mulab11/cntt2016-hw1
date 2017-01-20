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

const int maxn = 105;

int n;
struct edge
{
	int to, next;
	bool del;
	edge() {}
	edge(int _t, int _n):to(_t), next(_n) {del = 0;}
}e[maxn * 2];
int head[maxn], et = -1;
int fa[maxn];
bool vis[maxn];
vector<pair<int, int> > lst, A, B;
map<pair<int, int>, int> Ha, Hb;
int f[maxn * 2][maxn * 2];
int N;
int mat[maxn][maxn];
int X[maxn], Y[maxn], slack[maxn], Link[maxn], aLink[maxn], from[maxn];
int line[maxn], h, t;
bool x[maxn], y[maxn];
void Augment(int p)//更新增广路上的状态
{
    static int tp;
    while (p != 0) {
        tp = Link[from[p]];
        Link[from[p]] = p;
        aLink[p] = from[p];
        p = tp;
    }
}
void Bfs(int st)//Bfs增广
{
    h = t = 0;
    line[h++] = st;
    memset(vis, 0, sizeof(vis));
    memset(from, 0, sizeof(from));
    memset(slack, 0x3f, sizeof(slack));
    memset(x, 0, sizeof(x));
    memset(y, 0, sizeof(y));
    while (1) {
        while (h != t) {
            int now = line[t++];
            x[now] = 1;
            for (int i = 1; i <= N; ++i) {
                if (y[i] == 1) continue;
                if (X[now] + Y[i] == mat[now][i]) {
                    y[i] = 1;
                    from[i] = now;
                    if (aLink[i] == 0) {
                        Augment(i);
                        return;
                    }
                    else {
                        line[h++] = aLink[i];
                    }
                }
                else {
                    if (slack[i] > X[now] + Y[i] - mat[now][i]) {
                        slack[i] = X[now] + Y[i] - mat[now][i];
                        from[i] = now;
                    }
                }
            }
        }
        int det = 2e9;
        for (int i = 1; i <= N; ++i) {
            if (!y[i]) {
                Ckmin(det, slack[i]);
            }
        }
        for (int i = 1; i <= N; ++i) {
            if (x[i]) X[i] -= det;
            if (y[i]) Y[i] += det;
            else slack[i] -= det;
        }
        for (int i = 1; i <= N; ++i) {
            if (!y[i] && slack[i] == 0) {
                y[i] = 1;
                if (aLink[i] == 0) {
                    Augment(i);
                    return;
                }
                else {
                    line[h++] = aLink[i];
                }
            }
        }
    }
}
void Reset()//清空临界矩阵
{
    memset(mat, 0, sizeof(mat));
}
int Solve_KM()//KM
{
    int Sum = 0;
    for (int i = 1; i <= N; ++i) X[i] = -2e9, Y[i] = 0;
    for (int i = 1; i <= N; ++i) Link[i] = 0, aLink[i] = 0;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            Ckmax(X[i], mat[i][j]);
        }
    }
    for (int i = 1; i <= N; ++i) {
        Bfs(i);
    }
    for (int i = 1; i <= N; ++i) {
        Sum += mat[i][Link[i]];
    }
    return Sum;
}

void Addedge(int a, int b)//加边操作
{
	e[++et] = edge(a, head[b]), head[b] = et;
	e[++et] = edge(b, head[a]), head[a] = et;
}

void Dfs1(int p)//搜索后继状态
{
	vis[p] = 1;
	for (int i = head[p]; i != -1; i = e[i].next) {
		if (e[i].del || fa[p] == e[i].to) continue;
		fa[e[i].to] = p;
		Dfs1(e[i].to);
		lst.push_back(make_pair(e[i].to, p));
	}
}

void Dfs2(int p)//搜索后继状态
{
	lst.push_back(make_pair(p, 0));
	for (int i = head[p]; i != -1; i = e[i].next) {
		if (e[i].del || fa[p] == e[i].to) continue;
		fa[e[i].to] = p;
		lst.push_back(make_pair(p, e[i].to));
		Dfs2(e[i].to);
	}
}

int Dp()
{
	int Ans = 0;
	Ha.clear();
	Hb.clear();
	for (int i = 0, _ed = A.size(); i < _ed; ++i) {
		Ha[A[i]] = i;
	}
	for (int i = 0, _ed = B.size(); i < _ed; ++i) {
		Hb[B[i]] = i;
	}
	memset(f, 0, sizeof(f));
	static int a[maxn], b[maxn];
	int at = 0, bt = 0;
	for (int i = 0, _ed = A.size(); i < _ed; ++i) {
		for (int j = 0, _ed = B.size(); j < _ed; ++j) {
			Reset();
			at = 0;
			for (int k = head[A[i].first]; k != -1; k = e[k].next) {//枚举出后继状态
				if (!e[k].del && A[i].second != e[k].to) {
                    assert(Ha.count(make_pair(e[k].to, A[i].first)));
					a[++at] = Ha[make_pair(e[k].to, A[i].first)];
				}
			}
			bt = 0;
			for (int k = head[B[j].first]; k != -1; k = e[k].next) {
				if (!e[k].del && B[j].second != e[k].to) {
                    assert(Hb.count(make_pair(e[k].to, B[j].first)));
					b[++bt] = Hb[make_pair(e[k].to, B[j].first)];
				}
			}
			N = max(at, bt);
			for (int k = 1; k <= at; ++k) {//对于两边的后继状态，求出之间匹配的大小
				for (int q = 1; q <= bt; ++q) {
					mat[k][q] = f[a[k]][b[q]];
				}
			}
            f[i][j] = Solve_KM() + 1;//求出最大权匹配
			Ckmax(Ans, f[i][j]);//更新答案
		}
	}
	return Ans;
}

int Solve()
{
	int Ans = 0;
	for (int i = 0; i <= et; i += 2) {
		e[i].del = 1;//枚举一条边，将一棵树分成两棵树
		e[i ^ 1].del = 1;
		memset(vis, 0, sizeof(vis));
		fa[1] = 0;
		lst.clear();
		Dfs1(1);
		Dfs2(1);//搜索出无根树Dp的拓扑序
		A = lst;
		for (int j = 1; j <= n; ++j) {
			if (vis[j] == 0) {
				fa[j] = 0;
				lst.clear();
				Dfs1(j);
				Dfs2(j);
				B = lst;
				break;
			}
		}
		Ckmax(Ans, Dp());//进行Dp
		e[i].del = 0;
		e[i ^ 1].del = 0;
	}
	return Ans;
}

class DeerInZooDivOne {
    public:
    int getmax(vector<int> a, vector<int> b) {
		n = a.size() + 1;
		memset(head, -1, sizeof(head));
		et = -1;
		for (int i = 0; i < (int)a.size(); ++i) {//建边
			Addedge(a[i] + 1, b[i] + 1);
		}
		return Solve();//解决问题
    }
};
