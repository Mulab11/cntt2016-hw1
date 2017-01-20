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

const int maxn = 2555;
const int maxm = 55;

int n;
struct edge
{
	int to, next;
	edge() {}
	edge(int _t, int _n):to(_t), next(_n){}
}e[maxn * 2];
int head[maxn], et = -1;
int fa[maxn], deep[maxn], dis[maxn];
bool sec[maxn], inner[maxn];
int num[maxm][maxm], dt = 0;
int A, B;

void Addedge(int fr, int to)
{
	e[++et] = edge(to, head[fr]), head[fr] = et;
	e[++et] = edge(fr, head[to]), head[to] = et;
}

void Dfs(int p)//Dfs搜索无敌点
{
	int cnt3 = 0;
	inner[p] = 0;
	dis[p] = 1;
	for (int i = head[p]; i != -1; i = e[i].next) {
		if (fa[p] == e[i].to) continue;
		fa[e[i].to] = p;
		deep[e[i].to] = deep[p] + 1;
		Dfs(e[i].to);
		inner[p] |= inner[e[i].to];
		if (dis[e[i].to] >= 3) ++cnt3;
		Ckmax(dis[p], dis[e[i].to] + 1);
	}
	int tf = p;
	for (int i = 1; i <= 3; ++i) {
		if (fa[tf] == 0) break;
		for (int j = head[fa[tf]]; j != -1; j = e[j].next) {
			if (fa[fa[tf]] == e[j].to || tf == e[j].to) continue;
			if (dis[e[j].to] + i >= 3) {
				++cnt3;
				goto gate;
			}
		}
		if (i == 3) ++cnt3;
		tf = fa[tf];
	}
 gate:;
	if (cnt3 >= 3) sec[p] = 1;//如果有大于等于3条长度大于等于3的路径
	inner[p] |= sec[p];
}

bool Solve()
{
	//对于一个分岔点，如果他拥有3条长度大于等于3的路径，那么人类就可以一直在这里溜屠夫，将这样的点称为无敌点
	memset(sec, 0, sizeof(sec));
	memset(inner, 0, sizeof(inner));
	deep[A] = 1; fa[A] = 0;	Dfs(A);//Dfs搜索出无敌点
	if (fa[B] == A) return 1;
	int mid = B;
	while (1 + (deep[B] - deep[fa[mid]]) + 1 < deep[fa[mid]]) mid = fa[mid];//考虑屠夫一开始向人类逼近，可以将其限制在一棵子树内，如果子树内有无敌点，则人类获胜
	return (!inner[mid]);
}

class GameInDarknessDiv1 {
    public:
    string check(vector<string> field) {
		memset(head, -1, sizeof(head));
		et = -1;
		for (int i = 0; i < (int)field.size(); ++i) {//建树
			for (int j = 0; j < (int)field[i].length(); ++j) {
				if (field[i][j] != '#') {
					num[i][j] = ++dt;
					if (field[i][j] == 'A') A = dt;
					if (field[i][j] == 'B') B = dt;
					if (i != 0 && field[i - 1][j] != '#') Addedge(num[i - 1][j], num[i][j]);
					if (j != 0 && field[i][j - 1] != '#') Addedge(num[i][j - 1], num[i][j]);
				}
			}
		}
		if (Solve()) return "Alice wins";//返回答案
        else return "Bob wins";
    }
};
