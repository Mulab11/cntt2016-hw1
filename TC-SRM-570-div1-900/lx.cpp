#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second
#define LX_JUDGE

using namespace std;
typedef long long LL;

template<typename T> inline void upmax(T & x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T & x, T y) { x > y ? x = y : 0; }

const int inf = 0x3f3f3f3f;
const int N = 2111;
const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, -1, 0, 1};

struct edge				//费用流的边表
{
	int to, c, w, n;
} e[N * 25];

int head[N], tot;

inline void addEdge(int x, int y, int c, int w)			//加边
{
	e[++tot] = (edge) {y, c, w, head[x]}, head[x] = tot;
	e[++tot] = (edge) {x, 0, -w, head[y]}, head[y] = tot;
}

int d[N], pa[N], S, T;

void augment(int & f, int & w)		//增广
{
	int x = T, a = inf;
	while (x != S)
	{
		upmin(a, e[pa[x]].c);
		x = e[pa[x] ^ 1].to;
	}
	x = T;
	while (x != S)
	{
		e[pa[x]].c -= a;
		e[pa[x] ^ 1].c += a;
		x = e[pa[x] ^ 1].to;
	}
	f += a;
	w += d[T] * a;
}

bool search()				//SPFA寻找最短增广轨
{
	static bool vis[N];
	static int que[N + 10], fir, las;

	memset(d, 0x3f, sizeof(d));
	d[S] = 0;

	fir = las = 0;
	que[++las] = S;

	while (fir != las)
	{
		int u = que[++fir];
		fir == N ? fir = 0 : 0;
		vis[u] = 0;
		for (int p = head[u]; p; p = e[p].n) if (e[p].c)
		{
			int to = e[p].to;
			if (d[to] > d[u] + e[p].w)
			{
				d[to] = d[u] + e[p].w;
				pa[to] = p;
				if (!vis[to])
				{
					vis[to] = 1;
					que[++las] = to;
					las == N ? las = 0 : 0;
				}
			}
		}
	}

	return d[T] < inf;
}

pair<int , int> work()			//计算 <流量, 费用>
{
	pair<int, int> ans(0, 0);
	while (search())
		augment(ans.x, ans.y);
	return ans;
}

int n, m;

inline int id(int x, int y)		// id(i,j), id(i,j)+nm, id(i,j)+2nm 分别对应题解中的点 i, i_r, i_c
{
	return x * m + y;
}

class CurvyonRails
{
public:
	//拆点+费用流，二分图
	int getmin(vector<string> field)
	{
		tot = 1;
		memset(head, 0, sizeof(head));

		n = field.size();
		m = field[0].size();

		S = n * m * 3;
		T = S + 1;

		int nm = n * m;
		int cnt = 0, sum = 0;			// cnt 计算黑点数-白点数, sum 计算需要匹配的边数

		rep (i, 0, n - 1) rep (j, 0, m - 1)
		{
			if (field[i][j] != 'w')
			{
				if ((i + j) & 1)			//黑格
				{
					++cnt;
					sum += 2;
					int o = id(i, j);
					addEdge(S, o, 2, 0);				//代表黑格需要和周围的两个白格匹配
					addEdge(o, o + nm, 1, 0);			//横/纵向各有一点匹配
					addEdge(o, o + nm * 2, 1, 0);
					addEdge(o, o + nm, 1, field[i][j] == 'C');	//根据(i,j)是否为关键点，决定横/纵的额外匹配的费用
					addEdge(o, o + nm * 2, 1, field[i][j] == 'C');
					rep (d, 0, 3)			//黑格向白格连可以匹配的边
					{
						int x = i + dx[d];
						int y = j + dy[d];
						if (x >= 0 && x < n && y >= 0 && y < m && field[x][y] != 'w')
						{
							if (x == i)
								addEdge(o + nm, id(x, y) + nm, 1, 0);
							else 
								addEdge(o + nm * 2, id(x, y) + nm * 2, 1, 0);
						}
					}
				}
				else					//白格
				{
					--cnt;
					int o = id(i, j);
					addEdge(o, T, 2, 0);				//代表白格需要和周围的两个黑格匹配
					addEdge(o + nm, o, 1, 0);			//这里的连边和黑格类似，只是方向反过来
					addEdge(o + nm * 2, o, 1, 0);
					addEdge(o + nm, o, 1, field[i][j] == 'C');
					addEdge(o + nm * 2, o, 1, field[i][j] == 'C');
				}
			}
		}

		if (cnt)			//黑白点数不一致，一定无法匹配
			return -1;

		pair<int , int> u = work();
		return u.x == sum ? u.y : -1;		//流量=sum 代表匹配成功
	}
};
