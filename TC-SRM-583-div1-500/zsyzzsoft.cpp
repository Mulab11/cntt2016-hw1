#include <algorithm>
using namespace std;
int e[50][50];
bool del[50];
class TurnOnLamps
{
public:
	int n, que[50], pre[50], id[50];
	bool col[50], key[50];
	int Leaf(int x) //返回叶子边的编号 
	{
		int ret = 0;
		for(int i = 0; i < n; i++)
		{
			if(!del[i] && e[x][i])
			{
				if(ret)
					return 0;
				ret = e[x][i];
			}
		}
		return ret;
	}
	void Cover(int u, int v) //路径取反 
	{
		for(int i = 0; i < n; i++)
			pre[i] = -2;
		pre[u] = -1;
		que[0] = u;
		for(int l = 0, r = 1; l < r; l++)
		{
			int cur = que[l];
			for(int i = 0; i < n; i++)
			{
				if(!del[i] && pre[i] == -2 && e[cur][i])
				{
					pre[i] = cur;
					id[i] = e[cur][i];
					que[r++] = i;
				}
			}
		}
		for(int i = v; i != u; i = pre[i])
			col[id[i]] ^= 1;
	}
	int minimize(vector<int> roads, string state, string imp)
	{
		n = roads.size() + 1;
		for(int i = 1; i < n; i++)
			col[i] = state[i - 1] == '1', key[i] = imp[i - 1] == '1';
		for(int i = 0; i < roads.size(); i++)
			e[roads[i]][i + 1] = e[i + 1][roads[i]] = i + 1;
		int ans = 0;
		for(int rest = n, cnt = 0; rest > 1; rest -= cnt, cnt = 0) //循环找极远的路径 
		{
			vector<int> leaf;
			for(int i = 0; i < n; i++)
			{
				if(!del[i])
				{
					int p = Leaf(i);
					if(!p)
						continue;
					if(key[p] && !col[p])
						leaf.push_back(i);
					else //无用的叶子 
						del[i] = true, cnt++;
				}
			}
			if(!cnt) //没有无用的叶子 
			{
				Cover(leaf[0], leaf[1]); //操作任意两个叶子间的路径 
				ans++;
				del[leaf[0]] = del[leaf[1]] = true;
				cnt = 2;
			}
		}
		return ans;
	}
};