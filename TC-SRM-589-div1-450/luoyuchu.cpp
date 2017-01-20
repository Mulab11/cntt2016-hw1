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
const int co[3] = {'R', 'G', 'B'};

int n;
struct edge
{
	int to, next;
	edge() {}
	edge(int _t, int _n):to(_t), next(_n) {}
}e[maxn * maxn];
int head[maxn], et = -1;
int lnk[maxn];
bool vis[maxn];

void Addedge(int x, int y)
{
	e[++et] = edge(y, head[x]), head[x] = et;
}

bool Dfs(int p)//Dfs求增广路
{
	for (int i = head[p]; i != -1; i = e[i].next) {
		if (vis[e[i].to] == 0) {
			vis[e[i].to] = 1;
			if (lnk[e[i].to] == -1) {
				lnk[e[i].to] = p;
				return 1;
			}
			else if (Dfs(lnk[e[i].to])) {
				lnk[e[i].to] = p;
				return 1;
			}
		}
	}
	return 0;
}

int Solve()//二分图匹配
{
	int sum = 0;
	memset(lnk, -1, sizeof(lnk));
	for (int i = 0; i < n; ++i) {
		memset(vis, 0, sizeof(vis));
		sum += Dfs(i);
	}
	return sum;
}

class GearsDiv1 {
    public:
    int getmin(string color, vector<string> graph) {
		int Ans = 2e9;
		n = color.length();
		for (int a = 0; a < 3; ++a) {
			for (int b = a + 1; b < 3; ++b) {//枚举那两种颜色使用相同的方向，由于相同方向的齿轮不能在一起，所以就变为了二分图的最大独立集
				memset(head, -1, sizeof(head));
				et = -1;
				for (int i = 0; i < n; ++i) {
					if (color[i] == co[a]) {
						for (int j = 0; j < n; ++j) {
							if (color[j] == co[b]) {
								if (graph[i][j] == 'Y') {
									Addedge(i, j);//建图
								}
							}
						}
					}
				}
				Ckmin(Ans, Solve());//二分图匹配求最大独立集
			}
		}
        return Ans;
    }
};
