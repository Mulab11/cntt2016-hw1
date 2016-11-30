#include <algorithm>
#include <map>
#include <queue>
using namespace std;
struct Pair
{
	int i, j, u, v;
	Pair() {i = j = u = v = 0; }
	Pair(int _i, int _j, int _u, int _v) {i = _i, j = _j, u = _u, v = _v; }
};
const int p = 1000000009;
const int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
bool vis[40][40];
int col[40][40][40][40], pw[2000];
bool found = false;
class CoinsGame
{
public:
	int n, m, map[40][40];
	int Subset(int x)
	{
		return (pw[x] + p - x - 1) % p;
	}
	bool In(int i, int j)
	{
		return i >= 0 && i < n && j >= 0 && j < m;
	}
	int Dfs(int i, int j) //找出等价点的连通块 
	{
		if(!In(i, j) || !map[i][j] || vis[i][j])
			return 0;
		vis[i][j] = true;
		int sz = 1;
		for(int u = 0; u < n; u++)
		{
			for(int v = 0; v < m; v++)
			{
				if(col[i][j][u][v] == 1)
					sz += Dfs(u, v);
			}
		}
		return sz;
	}
	void Push(queue<Pair> &que, int i, int j, int u, int v)
	{
		if(col[i][j][u][v] != 2)
		{
			col[i][j][u][v] = 2;
			que.push(Pair(i, j, u, v));
		}
	}
	void Color(int i, int j, int u, int v)
	{
		queue<Pair> que;
		Push(que, i, j, u, v);
		while(!que.empty()) //Bfs染色 
		{
			Pair cur = que.front();
			que.pop();
			i = cur.i, j = cur.j, u = cur.u, v = cur.v;
			for(int d = 0; d < 4; d++)
			{
				int ni = i + dx[d], nj = j + dy[d], nu = u + dx[d], nv = v + dy[d];
				if(In(ni, nj) && !map[ni][nj]) //被阻碍 
				{
					nu = u - dx[d], nv = v - dy[d];
					if(In(nu, nv) && map[nu][nv])
						Push(que, i, j, nu, nv);
					nu = u + dx[d], nv = v + dy[d];
				}
				if(In(nu, nv) && !map[nu][nv])
				{
					ni = i - dx[d], nj = j - dy[d];
					if(In(ni, nj) && map[ni][nj])
						Push(que, ni, nj, u, v);
					ni = i + dx[d], nj = j + dy[d];
				}
				if(In(ni, nj) && In(nu, nv) && map[ni][nj] && map[nu][nv]) //未被阻碍 
					Push(que, ni, nj, nu, nv);
			}
		}
	}
	int ways(vector<string> board)
	{
		n = board.size(), m = board[0].size();
		int blank = 0;
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < m; j++)
				blank += map[i][j] = board[i][j] == '.';
		}
		pw[0] = 1;
		for(int i = 1; i <= blank; i++)
			pw[i] = pw[i - 1] * 2 % p;
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				for(int u = 0; u < n; u++)
					for(int v = 0; v < m; v++)
						col[i][j][u][v] = map[i][j] && map[u][v];
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				for(int u = 0; u < n; u++)
					for(int v = 0; v < m; v++)
					{
						bool flag = false;
						for(int d = 0; d < 4; d++)
						{
							int ni = i + dx[d], nj = j + dy[d], nu = u + dx[d], nv = v + dy[d];
							if(In(ni, nj) ^ In(nu, nv)) //找到能移出边界的一对 
								flag = true;
						}
						if(map[i][j] && map[u][v] && flag)
							Color(i, j, u, v); //标记所有能到达这一对的状态 
					}
		int ans = Subset(blank); //计算答案 
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < m; j++)
			{
				if(map[i][j] && !vis[i][j])
					ans = (ans + p - Subset(Dfs(i, j))) % p;
			}
		}
		return ans;
	}
};