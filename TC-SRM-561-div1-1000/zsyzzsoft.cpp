#include <algorithm>
using namespace std;
struct Edge
{
	int v;
	Edge *next;
};
const int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
double ans, c[301][301];
int n, m, k, mc, id[50][50], dis[300][2500], que[2500], sum[2500];
Edge memory[10000], *edge[2500];
class Orienteering
{
public:
	void AddEdge(int u, int v)
	{
		Edge *p = &memory[mc++];
		p->v = v, p->next = edge[u];
		edge[u] = p;
	}
	void Bfs(int *d, int s)
	{
		for(int i = 0; i < n; i++)
			d[i] = -1;
		d[s] = 0;
		que[0] = s;
		for(int l = 0, r = 1; l < r; l++)
		{
			int cur = que[l];
			for(Edge *next = edge[cur]; next; next = next->next)
			{
				if(d[next->v] < 0)
					d[next->v] = d[cur] + 1, que[r++] = next->v;
			}
		}
	}
	void Dfs(int node)
	{
		sum[node] = node < m;
		for(Edge *next = edge[node]; next; next = next->next)
		{
			if(sum[next->v] < 0)
				Dfs(next->v), sum[node] += sum[next->v];
		}
		ans += 1.0 - (c[sum[node]][k] + c[m - sum[node]][k]) / c[m][k];
	}
	double expectedLength(vector<string> field, int _k)
	{
		k = _k;
		for(int i = 0; i < field.size(); i++)
		{
			for(int j = 0; j < field[i].size(); j++)
				id[i][j] = field[i][j] == '*' ? m++ : -1;
		}
		for(int i = 0; i <= m; i++)
		{
			c[i][0] = c[i][i] = 1.0;
			for(int j = 1; j < i; j++)
				c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
		}
		n = m;
		for(int i = 0; i < field.size(); i++)
		{
			for(int j = 0; j < field[i].size(); j++)
				id[i][j] = field[i][j] == '.' ? n++ : id[i][j];
		}
		for(int i = 0; i < field.size(); i++)
		{
			for(int j = 0; j < field[i].size(); j++)
			{
				if(id[i][j] < 0)
					continue;
				for(int d = 0; d < 4; d++)
				{
					int mi = i + dx[d], mj = j + dy[d];
					if(mi >= 0 && mi < field.size() && mj >= 0 && mj < field[i].size() && id[mi][mj] >= 0)
						AddEdge(id[i][j], id[mi][mj]);
				}
			}
		}
		for(int i = 0; i < m; i++)
			Bfs(dis[i], i); //最短路 
		for(int i = 0; i < n; i++)
			sum[i] = -1;
		Dfs(0); //期望回路长度 
		ans *= 2.0;
		for(int i = 0; i < m; i++) //枚举直径 
		{
			for(int j = i + 1; j < m; j++)
			{
				int d = dis[i][j], cnt = 0;
				for(int x = 0; x < m; x++)
				{
					if(x != i && x != j && dis[i][x] <= d && dis[j][x] <= d)
						cnt++;
				}
				ans -= c[cnt][k - 2] * d / c[m][k];
				dis[i][j]++, dis[j][i]++;
			}
		}
		return ans;
	}
};
