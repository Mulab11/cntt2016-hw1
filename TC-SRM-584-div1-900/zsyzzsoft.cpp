#include <algorithm>
using namespace std;
const int inf = 1000000000;
struct Edge
{
	int v, w;
	Edge *next;
};
int mc, dis[100][100], f[100][1024];
Edge memory[1000], *edge[100];
void AddEdge(int u, int v, int w)
{
	Edge *p = &memory[mc++];
	p->v = v, p->w = w, p->next = edge[u];
	dis[u][v] = min(dis[u][v], w);
	edge[u] = p;
}
class FoxTheLinguist
{
public:
	int Get(char a, char b)
	{
		return b == '0' ? 0 : (a - 'A') * 10 + (b - '0');
	}
	int Num(char *s)
	{
		return (s[0] - '0') * 1000 + (s[1] - '0') * 100 + (s[2] - '0') * 10 + (s[3] - '0');
	}
	int minimalHours(int n, vector<string> course_vec)
	{
		string course;
		for(int i = 0; i < course_vec.size(); i++)
			course += course_vec[i];
		for(int i = 0; i < n * 10; i++)
		{
			for(int j = 0; j < n * 10; j++)
				dis[i][j] = inf;
			dis[i][i] = 0;
		}
		for(int i = 0; i < course.length(); i += 12) //建图 
			AddEdge(Get(course[i], course[i + 1]), Get(course[i + 4], course[i + 5]), Num(&course[i + 7]));
		for(int i = 0; i < n; i++)
		{
			for(int j = 1; j < 10; j++)
				AddEdge(i * 10 + j, i * 10 + j - 1, 0);
		}
		for(int i = 0; i < n * 10; i++)
		{
			for(int j = 0; j < 1 << n; j++)
				f[i][j] = inf;
		}
		for(int i = 0; i < n * 10; i++)
			f[i][0] = 0;
		for(int i = 0; i < n; i++)
			f[i * 10 + 9][1 << i] = 0;
		for(int k = 0; k < n * 10; k++)
		{
			for(int i = 0; i < n * 10; i++)
			{
				for(int j = 0; j < n * 10; j++)
					dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
			}
		}
		for(int s = 1; s < 1 << n; s++) //能到达的终点集合 
		{
			for(int i = 0; i < n * 10; i++)
			{
				for(Edge *next = edge[i]; next; next = next->next) //沿着这条边分裂成两部分 
				{
					for(int j = s; j; j = (j - 1) & s) //枚举子集 
						f[i][s] = min(f[i][s], f[next->v][j] + f[i][s - j] + next->w);
				}
			}
			for(int i = 0; i < n * 10; i++) //用能到达的同级点更新 
			{
				for(int j = 0; j < n * 10; j++)
					f[i][s] = min(f[i][s], f[j][s] + dis[i][j]);
			}
		}
		return f[0][(1 << n) - 1] < inf ? f[0][(1 << n) - 1] : -1;
	}
};