#include <algorithm>
using namespace std;
class HatRack
{
public:
	int n, max_id, sz[51];
	bool e[51][51];
	void AddEdge(int u, int v)
	{
		e[u][v] = e[v][u] = true;
	}
	void Size(int node, int last) //计算子树大小 
	{
		sz[node] = 1;
		for(int v = 0; v < n; v++)
		{
			if(e[node][v] && v != last)
				Size(v, node), sz[node] += sz[v];
		}
	}
	long long Dfs(int node, int last, int id)
	{
		max_id = id; //存储最大节点标号 
		vector<int> child;
		for(int v = 0; v < n; v++)
		{
			if(e[node][v] && v != last)
				child.push_back(v);
		}
		if(child.size() > 2)
			return 0;
		if(child.size() == 0)
			return 1;
		if(child.size() == 2 && sz[child[0]] < sz[child[1]])
			swap(child[0], child[1]);
		long long ret = 1;
		for(int i = 0; i < child.size(); i++)
			ret *= Dfs(child[i], node, id * 2 + i);
		if(sz[child[0]] == sz[child[1]]) //若子树大小相同答案加倍 
			ret *= 2;
		return ret;
	}
	long long countWays(vector<int> edge_u, vector<int> edge_v)
	{
		n = edge_u.size() + 1;
		if(n == 2)
			return 2;
		for(int i = 0; i + 1 < n; i++)
			AddEdge(--edge_u[i], --edge_v[i]);
		long long ans = 0;
		for(int i = 0; i < n; i++) //枚举根节点 
		{
			Size(i, -1);
			max_id = 0;
			long long tmp = Dfs(i, -1, 1);
			if(max_id == n)
				ans += tmp;
		}
		return ans;
	}
};
