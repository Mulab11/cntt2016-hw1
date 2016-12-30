#include <algorithm>
using namespace std;
struct Edge
{
	int v, w;
	Edge *next;
};
int mc;
bool flag = true;
Edge memory[5000], *edge[100];
void AddEdge(int u, int v, int w)
{
	Edge *p = &memory[mc++], *q = &memory[mc++];
	p->v = v, p->w = w, p->next = edge[u];
	q->v = u, q->w = w, q->next = edge[v];
	edge[u] = p, edge[v] = q;
}
class ThreeColorability
{
public:
	int col[100];
	void Color(int node) //异或染色 
	{
		for(Edge *next = edge[node]; next; next = next->next)
		{
			if(col[next->v] < 0)
				col[next->v] = col[node] ^ next->w, Color(next->v);
			else if(col[next->v] != (col[node] ^ next->w))
				flag = false;
		}
	}
	vector<string> lexSmallest(vector<string> cell)
	{
		int n = cell.size(), m = cell[0].size();
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < m; j++)
			{
				if(cell[i][j] != '?') //每个格子由行标与列标的异或决定 
					AddEdge(i + m, j, cell[i][j] == 'Z');
			}
		}
		for(int i = 0; i < n + m; i++)
			col[i] = -1;
		col[m] = 0;
		Color(m);
		for(int i = 0; i < m; i++) //保证第一行字典序最小 
		{
			if(col[i] < 0)
				col[i] = 0, Color(i);
		}
		for(int i = m + 1; i < n + m; i++) //让每一行字典序最小 
		{
			if(col[i] < 0)
				col[i] = col[0], Color(i);
		}
		if(!flag) //无解 
			return vector<string>();
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < m; j++)
				cell[i][j] = col[i + m] ^ col[j] ? 'Z' : 'N';
		}
		return cell;
	}
};