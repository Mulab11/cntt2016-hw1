#include <algorithm>
using namespace std;
const int inf = 2147483647;
class YetAnotherBoardGame
{
public:
	int n, m, ans, op[14][15];
	bool col[15][15];
	void Op1(int x, int y)
	{
		col[x - 1][y] ^= 1;
		col[x + 1][y] ^= 1;
		col[x][y - 1] ^= 1;
		col[x][y + 1] ^= 1;
	}
	void Op2(int x, int y)
	{
		col[x][y] ^= 1;
		Op1(x, y);
	}
	void Dfs(int depth, int cnt)
	{
		int st = 0;
		bool op1 = false, op2 = false;
		for(int i = 1; i <= m; i++)
		{
			if(!col[depth][i]) //每个没有被涂黑的格子都必须在下一行被操作 
			{
				st += 1 << i;
				cnt++;
				if(op[depth][i] == 1)
					op1 = true;
				else if(op[depth][i] == 2)
					op2 = true;
			}
		}
		if(depth == n)
		{
			if(st == 0)
				ans = min(ans, cnt);
		}
		else
		{
			if(!op2) //在不与之前操作过的列矛盾的情况下，枚举当前行执行操作1或操作2 
			{
				for(int i = 1; i <= m; i++)
					op[depth + 1][i] = st >> i & 1 ? 1 : op[depth][i];
				for(int i = 1; i <= m; i++)
				{
					if(st >> i & 1)
						Op1(depth + 1, i);
				}
				Dfs(depth + 1, cnt);
				for(int i = 1; i <= m; i++)
				{
					if(st >> i & 1)
						Op1(depth + 1, i);
				}
			}
			if(!op1)
			{
				for(int i = 1; i <= m; i++)
					op[depth + 1][i] = st >> i & 1 ? 2 : op[depth][i];
				for(int i = 1; i <= m; i++)
				{
					if(st >> i & 1)
						Op2(depth + 1, i);
				}
				Dfs(depth + 1, cnt);
				for(int i = 1; i <= m; i++)
				{
					if(st >> i & 1)
						Op2(depth + 1, i);
				}
			}
		}
	}
	int minimumMoves(vector<string> board)
	{
		n = board.size(), m = board[0].size();
		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j <= m; j++)
				col[i][j] = board[i - 1][j - 1] == 'B';
		}
		ans = inf;
		for(int st = 0; st < 1 << m; st++) //枚举第一行的操作情况 
		{
			int cnt = 0;
			for(int i = 0; i < m; i++)
				cnt += st >> i & 1;
			for(int i = 0; i < m; i++)
				op[1][i + 1] = st >> i & 1 ? 1 : 0;
			for(int i = 0; i < m; i++)
			{
				if(st >> i & 1)
					Op1(1, i + 1);
			}
			Dfs(1, cnt);
			for(int i = 0; i < m; i++)
			{
				if(st >> i & 1)
					Op1(1, i + 1);
			}
			for(int i = 0; i < m; i++)
				op[1][i + 1] = st >> i & 1 ? 2 : 0;
			for(int i = 0; i < m; i++)
			{
				if(st >> i & 1)
					Op2(1, i + 1);
			}
			Dfs(1, cnt);
			for(int i = 0; i < m; i++)
			{
				if(st >> i & 1)
					Op2(1, i + 1);
			}
		}
		return ans < inf ? ans : -1;
	}
};