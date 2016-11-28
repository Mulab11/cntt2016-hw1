#include <algorithm>
#include <memory.h>
using namespace std;
const int p = 1000000007, inf = 2147483647;
struct Edge
{
	int v, w;
	Edge *next;
};
Edge memory[200000], *edge[100];
int mc, val[100], h[100];
void AddEdge(int u, int v, int w)
{
	Edge *p = &memory[mc++], *q = &memory[mc++];
	p->v = v, p->w = w, p->next = edge[u];
	q->v = u, q->w = w, q->next = edge[v];
	edge[u] = p, edge[v] = q;
}
class EqualSums
{
public:
	int n, mina, minb;
	bool flag;
	void Dfs(int x) //判断当前连通块能否满足约束 
	{
		if(x > 0 && x < n)
			mina = min(mina, h[x]);
		else if(x > n)
			minb = min(minb, h[x]);
		if(h[x] < 0 || (val[x] >= 0 && val[x] != h[x]))
			flag = false;
		for(Edge *next = edge[x]; next; next = next->next)
		{
			if(h[next->v] == inf)
			{
				h[next->v] = next->w - h[x];
				Dfs(next->v);
			}
			else if(h[x] + h[next->v] != next->w)
				flag = false;
		}
	}
	void Clear(int x)
	{
		h[x] = inf;
		for(Edge *next = edge[x]; next; next = next->next)
		{
			if(h[next->v] != inf)
				Clear(next->v);
		}
	}
	int count(vector<string> board)
	{
		n = board.size();
		for(int i = 0; i < n; i++)
			val[i] = board[i][0] == '-' ? -1 : board[i][0] - '0';
		for(int i = 0; i < n; i++)
			val[i + n] = board[0][i] == '-' ? -1 : board[0][i] - '0';
		int ans = 0;
		for(int k = 0; k < 20; k++) //枚举左上角元素 
		{
			if(board[0][0] != '-' && board[0][0] - '0' != k)
				continue;
			val[0] = val[n] = k;
			memset(edge, 0, sizeof(edge));
			mc = 0;
			for(int i = 1; i < n; i++) //转化为第一行与第一列的元素间的限制关系 
			{
				for(int j = 1; j < n; j++)
				{
					if(board[i][j] != '-')
						AddEdge(i, j + n, board[i][j] - '0' + k);
				}
			}
			for(int i = 0; i < n * 2; i++)
				h[i] = inf;
			int f[20][20] = {0};
			f[19][19] = 1;
			for(int i = 0; i < n * 2; i++)
			{
				if(h[i] != inf)
					continue;
				int g[20][20] = {0};
				for(int j = 0; j < 20; j++) //枚举当前连通块的一个数值 
				{
					Clear(i);
					h[i] = j;
					flag = true;
					mina = 19, minb = 19;
					Dfs(i);
					if(!flag)
						continue;
					for(int u = 0; u < 20; u++)
					{
						for(int v = 0; v < 20; v++)
							g[min(mina, u)][min(minb, v)] = (g[min(mina, u)][min(minb, v)] + f[u][v]) % p;
					}
				}
				memcpy(f, g, sizeof(f));
			}
			for(int u = 0; u < 20; u++)
			{
				for(int v = 0; v < 20; v++)
				{
					if(u + v >= k) //为保证非负，两边的最小数值之和应至少为左上角元素 
						ans = (ans + f[u][v]) % p;
				}
			}
		}
		return ans;
	}
};
