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

const int maxn = 15;

int n, N;
int tip[maxn][10];//每个点的表号
struct edge
{
	int to, next, val;
	edge() {}
	edge(int _t, int _n, int _v):to(_t), next(_n), val(_v) {}
}e[maxn * maxn * 5];//边集
int head[maxn * maxn], et = -1, dt;
int fa[maxn * maxn];//并查集
int In[maxn * maxn], from[maxn * maxn];//每个点的最小的前驱边权及点

void Addedge(int x, int y, int val)//加边
{
	e[++et] = edge(y, head[x], val), head[x] = et;
}

void Init(vector<string> courseInfo)//建边
{
	stringstream tmp;
	string s;
	tmp.clear();
	for (int i = 0; i < (int)courseInfo.size(); ++i) {
		tmp << courseInfo[i];
	}
	while (tmp >> s) {
		int num = 0;
		for (int i = 7; i <= 10; ++i) {
			num = num * 10 + s[i] - '0';
		}
		if (tip[s[0] - 'A'][s[1] - '0'] != tip[s[4] - 'A'][s[5] - '0']) {
			Addedge(tip[s[0] - 'A'][s[1] - '0'], tip[s[4] - 'A'][s[5] - '0'], num);
		}
	}
}

int Getfa(int x)//并查集找父亲
{
	if (fa[x] == x) return x;
	return fa[x] = Getfa(fa[x]);
}

int Solve()
{
	int Ans = 0, res = N;
	static bool vis[maxn * maxn], insta[maxn * maxn], incir[maxn * maxn];//各种访问标记
	static int sta[maxn * maxn], st = 0;//栈
	static int circle[maxn * maxn], ct = 0;//是否在环中
	for (int i = 1; i <= N; ++i) fa[i] = i;
	while (res > 1) {
		for (int i = 1; i <= N; ++i) fa[i] = Getfa(i);//路径压缩
		memset(from, 0, sizeof(from));//初始化
		for (int i = 1; i <= N; ++i) {
			In[i] = 2e6+5;
		}
		for (int i = 1; i <= N; ++i) {//更新前驱信息
			for (int j = head[i]; j != -1; j = e[j].next) {
				if (fa[i] != fa[e[j].to]) {
					if (In[fa[e[j].to]] > e[j].val) {
						In[fa[e[j].to]] = e[j].val;
						from[fa[e[j].to]] = fa[i];
					}
				}
			}
		}
		bool ok = 1;//是否有环
		memset(vis, 0, sizeof(vis));
		vis[0] = vis[1] = 1;
		for (int i = 2; i <= N; ++i) {//找环
			if (fa[i] == i) {
				int p = i;
				st = 0;
				ct = 0;
				memset(insta, 0, sizeof(insta));
				while (1) {
					if (insta[p] == 0 && vis[p] == 1) break;
					if (insta[p] == 1) {
						while (sta[st] != p) {
							circle[++ct] = sta[st];
							--st;
						}
						--st;
						circle[++ct] = p;
						break;
					}
					vis[p] = 1;
					insta[p] = 1;
					sta[++st] = p;
					p = from[p];
				}
				if (ct != 0) {//发现了环
					ok = 0;
					memset(incir, 0, sizeof(incir));
					for (int j = 1; j <= ct; ++j) {
						Ans += In[circle[j]];
						incir[circle[j]] = 1;
					}
					for (int j = 1; j <= N; ++j) {//更新边权
						for (int k = head[j]; k != -1; k = e[k].next) {
							if (incir[fa[e[k].to]] == 1) {
								e[k].val -= In[fa[e[k].to]];
							}
						}
					}
					for (int j = 2; j <= ct; ++j) {
						fa[fa[circle[j]]] = fa[circle[1]];
					}
					res -= (ct - 1);
				}
			}
		}
		if (ok) {
			for (int i = 2; i <= N; ++i) {//如果没有环，统计答案
				if (fa[i] == i) {
					Ans += In[fa[i]];
				}
			}
			break;
		}
	}
	if (Ans > 2e6) return -1;//无解
	else return Ans;
}

class FoxTheLinguist {
    public:
    int minimalHours(int _n, vector<string> courseInfo) {
		n = _n;
		dt = 1;
		et = -1;
		memset(head, -1, sizeof(head));
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < 10; ++j) {
				tip[i][j] = ++dt;
			}
			Addedge(1, tip[i][0], 0);
			for (int j = 0; j < 9; ++j) {
				Addedge(tip[i][j + 1], tip[i][j], 0);
			}
		}
		N = dt;
		Init(courseInfo);
		return Solve();//返回答案
    }
};
